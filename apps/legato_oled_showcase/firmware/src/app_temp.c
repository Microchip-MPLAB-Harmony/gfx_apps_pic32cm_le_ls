/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_temp.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "definitions.h"
#include "app_temp.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define APP_TEMP_SENSOR_SLAVE_ADDR              0x0018
#define APP_TEMPERATURE_MEM_ADDR                0x05
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_TEMP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_TEMP_DATA app_tempData;
static uint8_t wrData;
static uint8_t rdData[2];
static unsigned int lastTickSec = 0;

static void APP_I2CEventHandler (
    DRV_I2C_TRANSFER_EVENT event,
    DRV_I2C_TRANSFER_HANDLE transferHandle,
    uintptr_t context
)
{
    APP_I2C_TRANSFER_STATUS* transferStatus = (APP_I2C_TRANSFER_STATUS*)context;

    if (event == DRV_I2C_TRANSFER_EVENT_COMPLETE)
    {
        if (transferStatus)
        {
            *transferStatus = APP_I2C_TRANSFER_STATUS_SUCCESS;
        }
    }
    else
    {
        if (transferStatus)
        {
            *transferStatus = APP_I2C_TRANSFER_STATUS_ERROR;
        }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
static uint16_t APP_CalculateTemperature(uint16_t rawTemperature)
{
    uint16_t temperature;
    uint8_t upperByte = (uint8_t)rawTemperature;
    uint8_t lowerByte = ((uint8_t*)&rawTemperature)[1];
        
    upperByte = upperByte & 0x1F;
    
    if ((upperByte & 0x10) == 0x10)         // Ta < 0 degC
    {
        upperByte = upperByte & 0x0F;       // Clear sign bit
        temperature = 256 - ((upperByte * 16) + lowerByte/16);
    }
    else
    {
        temperature = ((upperByte * 16) + lowerByte/16);
    }
    
    return temperature;
    
}
/*******************************************************************************
  Function:
    void APP_TEMP_Initialize ( void )

  Remarks:
    See prototype in app_temp.h.
 */

void APP_TEMP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_tempData.state = APP_TEMP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_TEMP_Tasks ( void )

  Remarks:
    See prototype in app_temp.h.
 */

void APP_TEMP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( app_tempData.state )
    {
        /* Application's initial state. */
        case APP_TEMP_STATE_INIT:
        {
            app_tempData.drvI2CHandle = DRV_I2C_Open( DRV_I2C_INDEX_0, DRV_IO_INTENT_READWRITE );
            if(app_tempData.drvI2CHandle == DRV_HANDLE_INVALID)
            {
                app_tempData.state = APP_TEMP_STATE_XFER_ERROR;
            }
            else
            {
                /* Register the I2C Driver event Handler */
                DRV_I2C_TransferEventHandlerSet(
                    app_tempData.drvI2CHandle,
                    APP_I2CEventHandler,
                    (uintptr_t)&app_tempData.transferStatus
                );
                
                app_tempData.state = APP_TEMP_STATE_CHECK_TEMP_SENSOR_READY;                               
            }

            break;
        }
        case APP_TEMP_STATE_CHECK_TEMP_SENSOR_READY:
        {
            /* Add a dummy write transfer to verify if Temperature Sensor is ready */
            app_tempData.transferStatus = APP_I2C_TRANSFER_STATUS_IN_PROGRESS;

            DRV_I2C_WriteTransferAdd(
                app_tempData.drvI2CHandle,
                APP_TEMP_SENSOR_SLAVE_ADDR,
                (void *)&app_tempData.ackData,
                1,
                &app_tempData.transferHandle
            );

            if( app_tempData.transferHandle == DRV_I2C_TRANSFER_HANDLE_INVALID )
            {
                app_tempData.state = APP_TEMP_STATE_XFER_ERROR;
            }
            else
            {
                app_tempData.state = APP_TEMP_STATE_WAIT_TEMP_SENSOR_READY;
            }
                
            break;
        }
        case APP_TEMP_STATE_WAIT_TEMP_SENSOR_READY:
        {
            if (app_tempData.transferStatus == APP_I2C_TRANSFER_STATUS_SUCCESS)
            {
                //Sensor is ready, start processing

                app_tempData.state = APP_TEMP_STATE_SERVICE_TASKS;
            }
            else if (app_tempData.transferStatus == APP_I2C_TRANSFER_STATUS_ERROR)
            {
                /* Temperature sensor is not ready. 
                 * Keep checking until it is ready. */
                app_tempData.state = APP_TEMP_STATE_CHECK_TEMP_SENSOR_READY;
            }
            break;
        }   

        case APP_TEMP_STATE_SERVICE_TASKS:
        {
            //Read temperature every second
            if (lastTickSec != tickSec)
            {
                app_tempData.state = APP_TEMP_STATE_READ_TEMPERATURE;
                
                lastTickSec = tickSec;
            }
            break;
        }        
        case APP_TEMP_STATE_READ_TEMPERATURE:
        {    
            app_tempData.transferStatus = APP_I2C_TRANSFER_STATUS_IN_PROGRESS;

            wrData = APP_TEMPERATURE_MEM_ADDR;
            
            DRV_I2C_WriteReadTransferAdd(
                app_tempData.drvI2CHandle,
                APP_TEMP_SENSOR_SLAVE_ADDR,
                (void *)&wrData,
                1,
                (void *)&rdData[0],
                2,
                &app_tempData.transferHandle
            );

            if( app_tempData.transferHandle == DRV_I2C_TRANSFER_HANDLE_INVALID )
            {
                app_tempData.state = APP_TEMP_STATE_XFER_ERROR;
            }
            else
            {
                app_tempData.state = APP_TEMP_STATE_UPDATE_TEMPERATURE;
            }
                                
            break;            
        }
        case APP_TEMP_STATE_UPDATE_TEMPERATURE:
        {
            if (app_tempData.transferStatus == APP_I2C_TRANSFER_STATUS_SUCCESS)
            {
                app_tempData.tempC = APP_CalculateTemperature(*((uint16_t*)rdData));

                app_tempData.state = APP_TEMP_STATE_SERVICE_TASKS;
            }
            else if (app_tempData.transferStatus == APP_I2C_TRANSFER_STATUS_ERROR)
            {
                app_tempData.state = APP_TEMP_STATE_XFER_ERROR;
            }
            
            break;
        }
        case APP_TEMP_STATE_XFER_ERROR:
        {
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
