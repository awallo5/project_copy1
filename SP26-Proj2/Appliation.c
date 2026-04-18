/*
 * Appliation.c
 *
 *  Created on: Apr 3, 2026
 *      Author: Andy W
 */


#include <Application.h>

/* ================================================================
   APPLICATION CONSTRUCT / LOOP
   ================================================================ */

Application Application_construct(HAL* hal_p) {
    Application app;

    app.baudChoice = BAUD_9600;
    app.type = INIT;
    app.cursor_loc = cursor_OnPlay;

    /* ===============================
       Start Screen Logic
       =============================== */
    app.start_screen_on = false; // screen does not start on

    return app;
}

void Application_loop(Application* app_p, HAL* hal_p){

    switch(app_p->type){

    case INIT:
         runInitFSM(app_p, hal_p);
        break;

    case MENU:
         runMenuFSM(app_p, hal_p);
        break;

    case GAMEPLAY:
        // runGamePlayFSM();
        break;

    case LOSE:
        // runLoseFSM();
        break;

    case WIN:
        // runWinFSM();
        break;

    case HIGHSCORE:
        break;
    case INSTRUCTIONS:
        break;

    case GAME:
        break;

    }

}

void runInitFSM(Application *app_p, HAL* hal_p){
    if(!app_p->start_screen_on){

        // Start Timer
        app_p->StartScreen_Timer = SWTimer_construct(2000);
        SWTimer_start(&app_p->StartScreen_Timer);

        // Start Graphics
        initialize_Starting_Screen_Graphics(hal_p);
        app_p->start_screen_on = true;
    }

    if(SWTimer_expired(&app_p->StartScreen_Timer)){
        GFX_clear(&hal_p->gfx);

        // When Timer Expires Transition to Menu Screen
        app_p->type = MENU;
        app_p->state = MENU_onPlay;

        // Execute Menu_onPlay Graphics
        initialize_Menu_Screen_Graphics(app_p, hal_p);
    }
}

void runMenuFSM(Application *app_p, HAL*hal_p){
    switch(app_p->state){

    case MENU_onPlay:
        if(hal_p->joystick.tappedUp){
            app_p->state = MENU_onHighScore;
            drawCursor(app_p, hal_p);
        } else if(hal_p->joystick.tappedDown){
            app_p->state = MENU_onInstructions;
            drawCursor(app_p, hal_p);
        } else if(Button_isTapped(&hal_p->boosterpackJS)){
            app_p->type = GAMEPLAY;
        }
        break;

    case MENU_onInstructions:
        if(hal_p->joystick.tappedUp){
            app_p->state = MENU_onPlay;
            drawCursor(app_p, hal_p);
        } else if(hal_p->joystick.tappedDown){
            app_p->state = MENU_onHighScore;
            drawCursor(app_p, hal_p);
        } else if(Button_isTapped(&hal_p->boosterpackJS)){
            app_p->type = INSTRUCTIONS;
            initialize_Instructions_Screen_Graphics(app_p, hal_p);
        }
        break;

    case MENU_onHighScore:
       if(hal_p->joystick.tappedUp){
           app_p->state = MENU_onInstructions;
           drawCursor(app_p, hal_p);
       } else if(hal_p->joystick.tappedDown){
           app_p->state = MENU_onPlay;
           drawCursor(app_p, hal_p);
       } else if(Button_isTapped(&hal_p->boosterpackJS)){
           app_p->type = HIGHSCORE;
           initialize_HighScore_Screen_Graphics(app_p, hal_p);
       }
        break;
    }
}


void runGamePlayFSM(Application *app_p, HAL *hal_p){

}
void runLoseFSM(Application *app_p, HAL *hal_p){

}
void runWinFSM(Application *app_p, HAL *hal_p){

}

