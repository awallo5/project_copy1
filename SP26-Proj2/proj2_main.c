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
    GFX_print(&hal_p->gfx, "SPRING 2026 PROJECT", 1, 1);
    GFX_print(&hal_p->gfx, "Brick Breaker", 2, 1);
    GFX_print(&hal_p->gfx, " Andrew Wallo V", 3, 1);

}
void initialize_Menu_Screen_Graphics(Application *app_p, HAL* hal_p){

        GFX_clear(&hal_p->gfx);
        Graphics_drawStringCentered(&hal_p->gfx.context,
                                    (int8_t *)"Menu",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    12, false);
        Graphics_drawStringCentered(&hal_p->gfx.context,
                                    (int8_t *)"-------------------",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    20, false);
        Graphics_drawString(&hal_p->gfx.context,
                            (int8_t *)"Play",
                            AUTO_STRING_LENGTH,
                            44,
                            50, false);
        Graphics_drawString(&hal_p->gfx.context,
                            (int8_t *)"Instructions",
                            AUTO_STRING_LENGTH,
                            44,
                            60, false);
        Graphics_drawString(&hal_p->gfx.context,
                            (int8_t *)"Highscores",
                            AUTO_STRING_LENGTH,
                            44,
                            70, false);

        drawCursor(app_p, hal_p);
}


void initialize_Instructions_Screen_Graphics(Application *app_p, HAL* hal_p){

}
void initialize_HighScore_Screen_Graphics(Application *app_p, HAL* hal_p){

}

/* ================================================================
   CURSOR GRAPHICS
   ================================================================ */

 void drawCursor(Application *app_p, HAL* hal_p){

     int temp_color = hal_p->gfx.foreground;   // stores any current foreground
     const Graphics_Font* temp_font = hal_p->gfx.context.font; // stores any current font

     GFX_setForeground(&hal_p->gfx, GRAPHICS_COLOR_BLACK);
     GFX_setFont(&hal_p->gfx.context, &g_sFontFixed6x8);


     Graphics_drawString(&hal_p->gfx.context,
                         (int8_t *)">",
                         AUTO_STRING_LENGTH,
                         36,
                         50, false);
     Graphics_drawString(&hal_p->gfx.context,
                         (int8_t *)">",
                         AUTO_STRING_LENGTH,
                         36,
                         60, false);
     Graphics_drawString(&hal_p->gfx.context,
                         (int8_t *)">",
                         AUTO_STRING_LENGTH,
                         36,
                         70, false);
     GFX_setForeground(&hal_p->gfx, GRAPHICS_COLOR_WHITE);

     Graphics_drawString(&hal_p->gfx.context,
                              (int8_t *)">",
                              AUTO_STRING_LENGTH,
                              36,
                              getCursorYpos(app_p), false);

     // return to whatever it was before
     GFX_setForeground(&hal_p->gfx, temp_color);
     GFX_setFont(&hal_p->gfx, temp_font);
 }

 /* ================================================================
    INT CHECKERS
    ================================================================ */

 int getCursorYpos(Application *app_p){
     if(app_p->state == MENU_onPlay)
         return 50;
     if(app_p->state == MENU_onInstructions)
         return 60;
     if(app_p->state == MENU_onHighScore)
         return 70;

     // else return 80 to show something is wrong
     return 80;
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
