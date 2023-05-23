/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

#define CLOCK_TICK_TIMER_PERIOD_MS 50
#define NUM_COUNT_SEC_TICK (1000/CLOCK_TICK_TIMER_PERIOD_MS)
    
#define IDLE_TIMEOUT_SECS 20

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    APP_EVENT_NONE,
    APP_EVENT_BTN_LEFT,
    APP_EVENT_BTN_RIGHT,
    APP_EVENT_BTN_UP,
    APP_EVENT_BTN_DOWN,
    APP_EVENT_BTN_CENTER,
            
    APP_EVENT_IDLE_TIMEOUT,

    APP_EVENT_START_SCROLL,
    APP_EVENT_STOP_SCROLL,
    APP_EVENT_SHOW_SCREEN1,
    APP_EVENT_SHOW_SCREEN2,
            
    APP_EVENT_SCRN_ADD_TIME,
    APP_EVENT_SCRN_SUB_TIME,
    APP_EVENT_SCRN_START_DEMO,
} APP_EVENTS;

typedef enum
{
    APP_BTN_RELEASED,
    APP_BTN_LEFT,
    APP_BTN_RIGHT,
    APP_BTN_UP,
    APP_BTN_DOWN,
    APP_BTN_CENTER,
} APP_BTN_STATE;
    
typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_STATE_SERVICE_TASKS,
             
    /* TODO: Define states used by the application state machine. */

} APP_STATES;

typedef enum
{
    APP_TEMP_UNIT_F,
    APP_TEMP_UNIT_C,
} APP_TEMP_UNITS;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    APP_EVENTS event;
    APP_BTN_STATE btnState;
    uint32_t activeScreenId;
    bool isScrolling;
    bool isDisplayInverse;
} APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

void Screen0_SendEvent(APP_EVENTS event);

extern volatile unsigned int tickSec;
extern volatile unsigned int tickCount;
extern APP_DATA appData;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_H */

/*******************************************************************************
 End of File
 */

