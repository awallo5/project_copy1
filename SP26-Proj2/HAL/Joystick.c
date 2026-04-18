#include<HAL/Joystick.h>



Joystick Joystick_construct(){

    Joystick joystick;

    initADC();
    initJoystick();
    startADC();

    joystick.x = 0;
    joystick.y = 0;

    return joystick;
}

void initADC(){
    ADC14_enableModule();

    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    // This configures the ADC to store output results
    // in ADC_MEM0 for joystick X.
    // Todo: if we want to add joystick Y, then, we have to use more memory locations
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // This configures the ADC in manual conversion mode
    // Software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void startADC() {
   // Starts the ADC with the first conversion
   // in repeat-mode, subsequent conversions run automatically
   ADC14_enableConversion();
   ADC14_toggleConversionTrigger();
}

void initJoystick() {

    // This configures ADC_MEM0/ADC_MEM1 to store the result from
       // input channel A15/A9 (X/Y), in non-differential input mode
       // (non-differential means: only a single input pin)
       // The reference for Vref- and Vref+ are VSS and VCC respectively
       ADC14_configureConversionMemory(ADC_MEM0,
                                     ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                     ADC_INPUT_A15,                 // joystick X
                                     ADC_NONDIFFERENTIAL_INPUTS);

       ADC14_configureConversionMemory(ADC_MEM1,
                                     ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                     ADC_INPUT_A9,                  // joystick Y
                                     ADC_NONDIFFERENTIAL_INPUTS);

       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                                  GPIO_PIN0,
                                                  GPIO_TERTIARY_MODULE_FUNCTION);
       GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                                  GPIO_PIN4,
                                                  GPIO_TERTIARY_MODULE_FUNCTION);

}

void Joystick_refresh(Joystick* joystick){
    joystick->x = ADC14_getResult(ADC_MEM0);
    joystick->y = ADC14_getResult(ADC_MEM1);

    bool checkCenterred = (joystick->x > CENTER_LOW && joystick->x < CENTER_HIGH) && (joystick->y > CENTER_LOW && joystick->y < CENTER_HIGH);
    joystick->tappedUp = (joystick->isCenter && joystick->y > UP_THRESHOLD);
    joystick->tappedDown = (joystick->isCenter &&joystick->y < DOWN_THRESHOLD);
    joystick->tappedLeft = (joystick->isCenter &&joystick->x < LEFT_THRESHOLD);
    joystick->tappedRight = (joystick->isCenter &&joystick->x > RIGHT_THRESHOLD);

    joystick->isCenter = checkCenterred;
}

bool Joystick_HeldUp(Joystick* joystick){
    return joystick->y > UP_THRESHOLD;
}
bool Joystick_HeldDown(Joystick *joystick){
    return joystick->y < DOWN_THRESHOLD;
}
bool Joystick_HeldLeft(Joystick *joystick){
    return joystick->x < LEFT_THRESHOLD;
}
bool Joystick_HeldRight(Joystick *joystick){
    return joystick->y > RIGHT_THRESHOLD;
}

