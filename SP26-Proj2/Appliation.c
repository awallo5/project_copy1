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
        // runMenuFSM();
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
        initialize_Menu_Screen_Graphics(hal_p);
    }
}

void runMenuFSM(Application *app_p, HAL*hal_p){
    switch(app_p->state){

    case MENU_onPlay:
        break;

    case MENU_onInstructions:
        break;

    case MENU_onHighScore:
        break;

    case INSTRUCTIONS:
        break;

    case HIGHSCORE:
        break;

    case GAME:
        break;

    }
}
void runGamePlayFSM(Application *app_p, HAL *hal_p){

}
void runLoseFSM(Application *app_p, HAL *hal_p){

}
void runWinFSM(Application *app_p, HAL *hal_p){

}

