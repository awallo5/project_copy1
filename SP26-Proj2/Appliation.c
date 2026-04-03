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

typedef struct _Application Application;

Application Application_construct(HAL* hal_p) {
    Application app;

    app.baudChoice = BAUD_9600;

    return app;
}

void Application_loop(Application* app, HAL* hal_p){


}
