/*
 * UART.h
 *
 *  Created on: Dec 31, 2019
 *      Author: Matthew Zhong
 *  Supervisor: Leyla Nazhand-Ali
 */

#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <string.h>

// Ever since the new API update in mid 2019, the UART configuration struct's
// name changed from [eUSCI_UART_Config] to [eUSCI_UART_ConfigV1]. If your code
// does not compile, uncomment the alternate #define and comment the original
// one. This should not really matter anymore
// -----------------------------------------------------------------------------
// #define UART_Config eUSCI_UART_Config
#define UART_Config eUSCI_UART_ConfigV1

// TODO: define these macros based on the UART module that is connected to USB
// on Launchpad via XDS110

#define USB_UART_PORT GPIO_PORT_P1
#define USB_UART_PINS (GPIO_PIN2 | GPIO_PIN3)
#define USB_UART_INSTANCE EUSCI_A0_BASE

// An enum outlining what baud rates the UART_construct() function can use in
// its initialization.
enum _UART_Baudrate {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  NUM_BAUD_CHOICES
};
typedef enum _UART_Baudrate UART_Baudrate;

// TODO: Write an overview explanation of what this UART struct does, and how it
//       interacts with the functions below. Consult <HAL/Button.h> and
//       <HAL/LED.h> for examples on how to do this.
//
// UART_Config holds configuration information for the UART.
// This will be used for sending and receiving information over the UART.
//
//
//
//
struct _UART {
  UART_Config config;

  uint32_t moduleInstance;
  uint32_t port;
  uint32_t pins;
};
typedef struct _UART UART;

// Constructs a uart using the moduleInstance at the given port and pin
UART UART_construct(uint32_t moduleInstance, uint32_t port, uint32_t pins);

// Sets the baudrate and enables a UART based on the given baudrate enum
void UART_SetBaud_Enable(UART*, UART_Baudrate baudrate);

// TODO: Write a comment which explains what each of these functions do. In
// the header, prefer explaining WHAT the function does, as opposed to HOW it
// is implemented.

// UART_hasChar Determines if the UART has sent a character.
// UART_getChar stores the char the UART has available into memory located at a pointer called uart_p.
// UART_canSend determines if the UART can send information, and the computer is ready to recieve
// UART_sendChar sends a character via UART -> UART-to-USB via XDS110 chip -> USB connection on computer -> internal computer solutions
bool UART_hasChar(UART* uart_p);
char UART_getChar(UART* uart_p);
bool UART_canSend(UART* uart_p);
void UART_sendChar(UART* uart_p, char c);
void UART_sendString(UART* uart_p, char* char_arr);

// Updates the UART baudrate to use the new baud choice.
void UART_updateBaud(UART* uart_p, UART_Baudrate baudChoice);

#endif /* HAL_UART_H_ */
