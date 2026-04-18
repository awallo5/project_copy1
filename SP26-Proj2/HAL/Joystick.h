#ifndef HAL_JOYSTICK_H_
#define HAL_JOYSTICK_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define LEFT_THRESHOLD 4000
#define RIGHT_THRESHOLD 12000
#define UP_THRESHOLD 12000
#define DOWN_THRESHOLD 4000
#define CENTER_LOW 6000
#define CENTER_HIGH 10000

struct _Joystick {
    int x;
    int y;

    bool isCenter;
    bool tappedUp;
    bool tappedDown;
    bool tappedLeft;
    bool tappedRight;
};

typedef struct _Joystick Joystick;

Joystick Joystick_construct();
void initADC();
void startADC();
void initJoystick();
void Joystick_refresh(Joystick *joystick);

// boolean checks

bool Joystick_HeldUp(Joystick *joystick);
bool Joystick_HeldDown(Joystick *joystick);
bool Joystick_HeldLeft(Joystick *joystick);
bool Joystick_HeldRight(Joystick *joystick);


#endif /* HAL_JOYSTICK_H_ */
