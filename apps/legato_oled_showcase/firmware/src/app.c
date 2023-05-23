/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

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
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/
#ifndef CUSTOM_CONTOLLER_CODE_ENABLED
//Custom controller code was not generated, 
#define DRV_SSD1309_VerticalScroll()
#define DRV_SSD1309_StopScroll();
#define DRV_SSD1309_SetDisplayStartLine(x);
#define DRV_SSD1309_RightScroll();
#define DRV_SSD1309_LeftScroll();
#define DRV_SSD1309_InverseDisplay(x);
#endif

void APP_Scroll(bool start);

APP_DATA appData;

volatile unsigned int tickCount = 0;
volatile unsigned int tickSec = 0;
volatile unsigned int idleSecs = 0;

static SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void APP_SendEvent(APP_EVENTS event)
{
    appData.event = event;
}

static void Timer_Callback ( uintptr_t context)
{
    tickCount++;
    
    if (tickCount % NUM_COUNT_SEC_TICK == 0)
    {
        tickSec++;
        idleSecs++;
        
        if (idleSecs > IDLE_TIMEOUT_SECS)
        {
            APP_SendEvent(APP_EVENT_IDLE_TIMEOUT);
        }        
    }
    

}

static void EIC_User_Handler(uintptr_t context)
{
    if (SW_CENTER_Get() == 0)
    {
        APP_SendEvent(APP_EVENT_BTN_CENTER);
    }
    else if (SW_UP_Get() == 0)
    {
        APP_SendEvent(APP_EVENT_BTN_UP);
    }
    else if (SW_DOWN_Get() == 0)
    {
        APP_SendEvent(APP_EVENT_BTN_DOWN);
    }
    else if (SW_LEFT_Get() == 0)
    {
        APP_SendEvent(APP_EVENT_BTN_LEFT);
    }
    else if (SW_RIGHT_Get() == 0)
    {
        APP_SendEvent(APP_EVENT_BTN_RIGHT);
    }
    
    idleSecs = 0;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    appData.event = APP_EVENT_NONE;
    appData.activeScreenId = 0;
    appData.isScrolling = false;
    appData.isDisplayInverse = true;

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Scroll(bool start)
{
    if (start == true && appData.isScrolling == false)
    {
        appData.isScrolling = true;        
        Screen0_SendEvent(APP_EVENT_START_SCROLL);
        DRV_SSD1309_VerticalScroll();
    }
    else if (start == false && appData.isScrolling == true)
    {
        appData.isScrolling = false; 
        appData.activeScreenId = 0;
        Screen0_SendEvent(APP_EVENT_STOP_SCROLL);
        DRV_SSD1309_StopScroll();
    }
}

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            timer = SYS_TIME_CallbackRegisterMS(Timer_Callback, 1, CLOCK_TICK_TIMER_PERIOD_MS, SYS_TIME_PERIODIC);   
            EIC_CallbackRegister(EIC_PIN_0,EIC_User_Handler, 0);
            EIC_CallbackRegister(EIC_PIN_2,EIC_User_Handler, 0);
            EIC_CallbackRegister(EIC_PIN_3,EIC_User_Handler, 0);
            EIC_CallbackRegister(EIC_PIN_10,EIC_User_Handler, 0);
            EIC_NMICallbackRegister(EIC_User_Handler, 0);

            appData.state = APP_STATE_SERVICE_TASKS;                               
            
            break;
        }
        case APP_STATE_SERVICE_TASKS:
        {
            switch(appData.event)
            {
                case APP_EVENT_IDLE_TIMEOUT:
                {
                    APP_Scroll(true);
                    Screen0_SendEvent(APP_EVENT_SCRN_START_DEMO);
                    
                    break;
                }
                case APP_EVENT_BTN_LEFT:
                {
                    if (appData.isScrolling == true)
                    {
                        APP_Scroll(false);
                    }
                    else
                    {
                        Screen0_SendEvent(APP_EVENT_SCRN_SUB_TIME);
                    }                    

                    break;
                }
                case APP_EVENT_BTN_RIGHT:
                {
                    if (appData.isScrolling == true)
                    {
                        APP_Scroll(false);
                    }
                    else
                    {
                        Screen0_SendEvent(APP_EVENT_SCRN_ADD_TIME);
                    }                    

                    break;
                }
                case APP_EVENT_BTN_UP:
                {
                    if (appData.isScrolling == true)
                    {
                        APP_Scroll(false);
                    }
                    else
                    {
                        APP_Scroll(true);
                    }
                    
                    DRV_SSD1309_SetDisplayStartLine(0);
                    
                    break;
                }
                case APP_EVENT_BTN_DOWN:
                {
                    APP_Scroll(false);
                    
                    if (appData.activeScreenId == 0)
                    {
                        appData.activeScreenId = 1;
                        DRV_SSD1309_SetDisplayStartLine(32);
                    }
                    else
                    {
                        appData.activeScreenId = 0;
                        DRV_SSD1309_SetDisplayStartLine(0);
                    }
                    break;
                }
                case APP_EVENT_BTN_CENTER:
                {
                    if (appData.isScrolling == true)
                    {
                        APP_Scroll(false);
                    }
                    else
                    {
                        appData.isDisplayInverse = !appData.isDisplayInverse;
                        DRV_SSD1309_InverseDisplay(appData.isDisplayInverse);
                        Screen0_SendEvent(APP_EVENT_BTN_CENTER);
                    }                    
                    
                    break;
                }
                default:
                {
                    break;
                }
            }
            
            appData.event = APP_EVENT_NONE;
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
