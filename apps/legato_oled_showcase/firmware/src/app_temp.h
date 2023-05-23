/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_temp.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_TEMP_Initialize" and "APP_TEMP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_TEMP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_TEMP_H
#define _APP_TEMP_H

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
    /* Application's state machine's initial state. */
    APP_TEMP_STATE_INIT=0,
    APP_TEMP_STATE_SERVICE_TASKS,
    APP_TEMP_STATE_CHECK_TEMP_SENSOR_READY,
    APP_TEMP_STATE_WAIT_TEMP_SENSOR_READY,
    APP_TEMP_STATE_READ_TEMPERATURE,
    APP_TEMP_STATE_UPDATE_TEMPERATURE,
    APP_TEMP_STATE_XFER_ERROR,               
    /* TODO: Define states used by the application state machine. */

} APP_TEMP_STATES;

typedef enum
{
    APP_I2C_TRANSFER_STATUS_IN_PROGRESS,
    APP_I2C_TRANSFER_STATUS_SUCCESS,
    APP_I2C_TRANSFER_STATUS_ERROR,
    APP_I2C_TRANSFER_STATUS_IDLE,

} APP_I2C_TRANSFER_STATUS;


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
    APP_TEMP_STATES state;
    DRV_HANDLE                  drvI2CHandle;
    DRV_I2C_TRANSFER_HANDLE     transferHandle;
    APP_I2C_TRANSFER_STATUS     transferStatus;
    uint8_t                     ackData;
    uint16_t                    tempC;      

    /* TODO: Define any additional data used by the application. */

} APP_TEMP_DATA;

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
    void APP_TEMP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_TEMP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_TEMP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_TEMP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_TEMP_Tasks ( void )

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
    APP_TEMP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_TEMP_Tasks( void );

extern APP_TEMP_DATA app_tempData;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_TEMP_H */

/*******************************************************************************
 End of File
 */

