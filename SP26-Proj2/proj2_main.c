/**
 * Starter code for Project 2. Good luck!
 *
 * We recommending copy/pasting your HAL folder from Project 1
 * into this project.
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <Application.h>
#include "HAL/HAL.h"

static void InitNonBlockingLED();
static void PollNonBlockingLED();

int main() {
  WDT_A_holdTimer();
  InitSystemTiming(); // Clock Initialization: 48MHz + Timer32

  HAL hal = HAL_construct();
  Application app = Application_construct(&hal);

  // Do not remove this line. This is your non-blocking check.
  InitNonBlockingLED();
  while (1) {
    // Do not remove this line. This is your non-blocking check.
    PollNonBlockingLED();


    HAL_refresh(&hal);
    Application_loop(&app, &hal);
  }
}

/* ================================================================
   MACRO GRAPHICS CALLS
   ================================================================ */

// Starting Screen Graphics Macro Function
void initialize_Starting_Screen_Graphics(HAL* hal_p){

    GFX_print(&hal_p->gfx, "Brick Breaker", 1, 1);
    GFX_print(&hal_p->gfx, " Andrew Wallo V", 2, 1);

}
void initialize_Menu_Screen_Graphics(HAL* hal_p){

}

void initialize_Instructions_Screen_Graphics(HAL* hal_p){

}
void initialize_HighScore_Screen_Graphics(HAL* hal_p){

}



/* ================================================================
   POLLING CHECKS
   ================================================================ */


// Non-blocking check. Whenever Launchpad S1 is pressed, LED1 turns on.
static void InitNonBlockingLED() {
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
}

// Non-blocking check. Whenever Launchpad S1 is pressed, LED1 turns on.
static void PollNonBlockingLED() {
  GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
  if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0) {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
  }
}
