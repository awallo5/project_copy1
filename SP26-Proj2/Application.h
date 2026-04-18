/*
 * Application.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Matthew Zhong
 *  Supervisor: Leyla Nazhand-Ali
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <HAL/HAL.h>



/* ================================================================
   FSM STATE DEFINITIONS
   ================================================================ */

typedef enum {
    START,
    MENU_onPlay,
    MENU_onInstructions,
    MENU_onHighScore,
    HIGHSCORE,
    INSTRUCTIONS,
    GAME
} FSM_state;


typedef enum {
    INIT,
    MENU,
    GAMEPLAY,
    LOSE,
    WIN
} FSM_type;

typedef enum {
    cursor_OnPlay,
    cursor_OnInstructions,
    cursor_OnHighscore
} Cursor_loc;


/* ================================================================
   MAIN APPLICATION STRUCTURE
   ================================================================ */

struct _Application {


    /* ===============================
       Starting Screen Logic
       =============================== */

    bool start_screen_on;

    /* ===============================
       Communications
       =============================== */

    UART_Baudrate baudChoice;


    /* ===============================
       FSM State Control
       =============================== */

    FSM_state state;
    FSM_type type;
    Cursor_loc cursor_loc;

    /* ===============================
       TIMERS
       =============================== */

    SWTimer StartScreen_Timer; // 2 second timer goes from StartScreen -> Menu

};


typedef struct _Application Application;

/* ================================================================
   CORE APPLICATION FUNCTIONS
   ================================================================ */

// Constructed once in main()
Application Application_construct(HAL* hal_p);

// Called every super-loop
void Application_loop(Application* app, HAL* hal);

// UART / Communications update
void Application_updateCommunications(Application* app, HAL* hal);

// Character interpreter
char Application_interpretIncomingChar(char rxChar);

// Circular increment helper
uint32_t CircularIncrement(uint32_t value, uint32_t maximum);



/* ================================================================
   STATE FSM EXECUTION
   ================================================================ */
void runMenuFSM(Application *app_p, HAL*hal_p);
void runGamePlayFSM(Application *app_p, HAL *hal_p);
void runLoseFSM(Application *app_p, HAL *hal_p);
void runWinFSM(Application *app_p, HAL *hal_p);

/* ================================================================
   TYPE FSM EXECUTION
   ================================================================ */
void runInitFSM(Application *app_p, HAL* hal_p);

/* ================================================================
   INT CHECKERS
   ================================================================ */
int getCursorYpos(Application *app_p);

/* ================================================================
   TIMER CONSTRUCTION FUNCTIONS
   ================================================================ */

void createStartScreenTimerInApplication(Application *app_p);


/* ================================================================
   UART / COMMUNICATION FUNCTIONS
   ================================================================ */


/* ================================================================
    DRAWING
   ================================================================ */


/* ================================================================
   MACRO GRAPHICS CALLS
   ================================================================ */
void initialize_Starting_Screen_Graphics(HAL* hal_p);
void initialize_Menu_Screen_Graphics(Application *app_p, HAL* hal_p);
void initialize_Instructions_Screen_Graphics(Application *app_p, HAL* hal_p);
void initialize_HighScore_Screen_Graphics(Application *app_p, HAL* hal_p);


void drawCursor(Application *app_p, HAL* hal_p);



/* ================================================================
   GAMEPLAY LOGIC
   ================================================================ */




#endif /* APPLICATION_H_ */
