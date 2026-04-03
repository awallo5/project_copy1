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
    INSTRUCTIONS,
    GAME
} FSM_state;


typedef enum {
    INIT,
    GAMEPLAY,
    LOSE,
    WIN
} FSM_type;


/* ================================================================
   MAIN APPLICATION STRUCTURE
   ================================================================ */

struct _Application {

    /* ===============================
       Communications
       =============================== */
    UART_Baudrate baudChoice;


    /* ===============================
       FSM State Control
       =============================== */
    FSM_state state;
    FSM_type type;

};





/* ================================================================
   CORE APPLICATION FUNCTIONS
   ================================================================ */

// Constructed once in main()
Application Application_construct();

// Called every super-loop
void Application_loop(Application* app, HAL* hal);

// UART / Communications update
void Application_updateCommunications(Application* app, HAL* hal);

// Character interpreter
char Application_interpretIncomingChar(char rxChar);

// Circular increment helper
uint32_t CircularIncrement(uint32_t value, uint32_t maximum);



/* ================================================================
   FSM EXECUTION
   ================================================================ */


/* ================================================================
   TIMER CONSTRUCTION FUNCTIONS
   ================================================================ */

void createStartScreenTimerInApplication(Application *app_p);
SWTimer startScreenTime = SWTimer_construct(2000);


/* ================================================================
   UART / COMMUNICATION FUNCTIONS
   ================================================================ */


/* ================================================================
    DRAWING
   ================================================================ */


/* ================================================================
   GAMEPLAY LOGIC
   ================================================================ */




#endif /* APPLICATION_H_ */
