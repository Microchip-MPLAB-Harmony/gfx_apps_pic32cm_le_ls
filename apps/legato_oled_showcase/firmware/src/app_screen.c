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

#include "definitions.h"
#include "app_temp.h"

#define MAX_STR_BUFF_SIZE 16
#define BAR_DEFAULT_Y_POS 7
#define PROGBAR_DEFAULT_X_POS 35

static unsigned int clockSec;
static unsigned int lastSecTick = 0;
static unsigned int clockMin = 0;
static unsigned int clockHr = 12;
static unsigned int lastTick = 0;

static leFixedString hrStr, minStr, tempStr;
static leChar hrStrBuff[MAX_STR_BUFF_SIZE] = {0};
static leChar minStrBuff[MAX_STR_BUFF_SIZE] = {0};
static leChar tempStrBuff[MAX_STR_BUFF_SIZE] = {0};

static APP_TEMP_UNITS tempUnit = APP_TEMP_UNIT_F;
bool isPlaying = false;

APP_EVENTS screenEvents;
extern APP_TEMP_DATA app_tempData;

uint32_t barAnimSizes[10][5] = 
{
    {10, 15, 5, 8, 20},
    {12, 10, 8, 4, 18},  
    {15, 5, 10, 2, 15},  
    {18, 8, 12, 4, 14},  
    {20, 10, 14, 6, 13},  
    {18, 12, 16, 8, 12},  
    {15, 14, 14, 10, 14},  
    {12, 10, 12, 12, 16},  
    {8, 18, 10, 10, 17},
    {6, 20, 8, 14, 18},
};

void Screen0_SendEvent(APP_EVENTS event)
{
    screenEvents = event;
}

void Screen0_OnShow(void)
{
    isPlaying = true;
    
    Screen0_LineWidget2->fn->setVisible(Screen0_LineWidget2, LE_FALSE);
    Screen0_LineWidget3->fn->setVisible(Screen0_LineWidget3, LE_FALSE);
            
    leFixedString_Constructor(&hrStr, hrStrBuff, MAX_STR_BUFF_SIZE);
    hrStr.fn->setFont(&hrStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_TimeDefault,
                                                              0));    
    
    leFixedString_Constructor(&minStr, minStrBuff, MAX_STR_BUFF_SIZE);
    minStr.fn->setFont(&minStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_TimeDefault,
                                                              0));
    
    leFixedString_Constructor(&tempStr, tempStrBuff, MAX_STR_BUFF_SIZE);
    tempStr.fn->setFont(&tempStr, leStringTable_GetStringFont(leGetState()->stringTable,
                                                              stringID_TempLabel,
                                                              0));   
}

void Screen0_OnHide(void)
{
    hrStr.fn->destructor(&hrStr);
    minStr.fn->destructor(&minStr);
}

void Screen0_UpdateMusicBars(uint32_t bar0, uint32_t bar1, uint32_t bar2, uint32_t bar3, uint32_t bar4)
{
    Screen0_MusicBar0->fn->setHeight(Screen0_MusicBar0, bar0);
    Screen0_MusicBar1->fn->setHeight(Screen0_MusicBar1, bar1);
    Screen0_MusicBar2->fn->setHeight(Screen0_MusicBar2, bar2);
    Screen0_MusicBar3->fn->setHeight(Screen0_MusicBar3, bar3);
    Screen0_MusicBar4->fn->setHeight(Screen0_MusicBar4, bar4);

    Screen0_MusicBar0->fn->setPosition(Screen0_MusicBar0, 
                                       Screen0_MusicBar0->fn->getX(Screen0_MusicBar0),
                                       BAR_DEFAULT_Y_POS + 20 - bar0);
    Screen0_MusicBar1->fn->setPosition(Screen0_MusicBar1,
                                       Screen0_MusicBar1->fn->getX(Screen0_MusicBar1),
                                       BAR_DEFAULT_Y_POS + 20 - bar1);
    Screen0_MusicBar2->fn->setPosition(Screen0_MusicBar2, 
                                       Screen0_MusicBar2->fn->getX(Screen0_MusicBar2),
                                       BAR_DEFAULT_Y_POS + 20 - bar2);
    Screen0_MusicBar3->fn->setPosition(Screen0_MusicBar3,
                                       Screen0_MusicBar3->fn->getX(Screen0_MusicBar3),
                                       BAR_DEFAULT_Y_POS + 20 - bar3);
    Screen0_MusicBar4->fn->setPosition(Screen0_MusicBar4,
                                       Screen0_MusicBar4->fn->getX(Screen0_MusicBar4),
                                       BAR_DEFAULT_Y_POS + 20 - bar4);
}

void Screen0_UpdateClockLabels(unsigned int hr, unsigned min)
{
    char charBuff[MAX_STR_BUFF_SIZE] = {0};
    
    hr = (hr >= 12) ? 12 : hr;
    min = (min >= 60) ? 0 : min;
    
    sprintf(charBuff, "%02u", hr); 
    hrStr.fn->setFromCStr(&hrStr, charBuff);    
    Screen0_HourLabelWidget->fn->setString(Screen0_HourLabelWidget, (leString*)&hrStr);   

    sprintf(charBuff, "%02u", min); 
    minStr.fn->setFromCStr(&minStr, charBuff);    
    Screen0_MinLabelWidget->fn->setString(Screen0_MinLabelWidget, (leString*)&minStr);    
}

void Screen0_UpdateTempLabels(unsigned int tempC)
{
    char charBuff[MAX_STR_BUFF_SIZE] = {0};
    unsigned int temp;
    
    if (tempUnit == APP_TEMP_UNIT_F)
    {
        Screen0_TempUnitLabelWidget->fn->setString(Screen0_TempUnitLabelWidget, (leString*)&string_TempUnitF);
        temp = (tempC * 9) / 5 + 32;
    }
    else
    {
        Screen0_TempUnitLabelWidget->fn->setString(Screen0_TempUnitLabelWidget, (leString*)&string_TempUnitC);
        temp = tempC;
    }

    sprintf(charBuff, "%02u", temp); 
    tempStr.fn->setFromCStr(&tempStr, charBuff);    
    Screen0_TempLabelWidget->fn->setString(Screen0_TempLabelWidget, (leString*)&tempStr);
}

void Screen0_ProcessClockTemp(void)
{
    static uint16_t lastTempC = 0;
    if (lastSecTick != tickSec)
    {
        clockSec++;
        if (clockSec == 60)
        {
            clockSec = 0;
            clockMin++;
            if (clockMin == 60)
            {
                clockMin = 0;
                clockHr++;
                if (clockHr == 13)
                {
                    clockHr = 1;
                }
            }
        }
        
        Screen0_UpdateClockLabels(clockHr, clockMin);
        
        Screen0_ColonLabelWidget->fn->setVisible(
                    Screen0_ColonLabelWidget,
                    !Screen0_ColonLabelWidget->fn->getVisible(Screen0_ColonLabelWidget));
        
        lastSecTick = tickSec;
        
        if (app_tempData.tempC != lastTempC)
        {
            Screen0_UpdateTempLabels(app_tempData.tempC);

            lastTempC = app_tempData.tempC;
        }

        //Switch units every 5 seconds
        if (tickSec % 5 == 0)
        {
            tempUnit = (tempUnit == APP_TEMP_UNIT_F) ? APP_TEMP_UNIT_C : APP_TEMP_UNIT_F; 
            Screen0_UpdateTempLabels(app_tempData.tempC);
        } 
    }
}

void Screen0_ProcessEvents(void)
{
    switch(screenEvents)
    {
        case APP_EVENT_BTN_CENTER:
        {
            if (appData.isScrolling == false)
            {
                switch (appData.activeScreenId)
                {
                    case 0:
                    {
                        tempUnit = (tempUnit == APP_TEMP_UNIT_F) ? APP_TEMP_UNIT_C : APP_TEMP_UNIT_F; 
                        Screen0_UpdateTempLabels(app_tempData.tempC);
                        break;
                    }
                    case 1:
                    {
                        isPlaying = (isPlaying == true) ? false : true;
                        
                        Screen0_UpdateMusicBars(2, 2, 2, 2, 2);
                        Screen0_PlayPauseButton->fn->setPressed(Screen0_PlayPauseButton, isPlaying);
                        break;
                    }
                    default:
                        break;
                }
            }

            break;
        }
        case APP_EVENT_SCRN_SUB_TIME:
        {
            if (clockMin > 0)
            {
                clockMin -= 1;
            }
            else
            {
                clockMin = 59;
                clockHr = (clockHr > 1) ? clockHr - 1 : 12;
            }
            
            Screen0_UpdateClockLabels(clockHr, clockMin);
            break;
        }
        case APP_EVENT_SCRN_ADD_TIME:
        {
            if (clockMin < 59)
            {
                clockMin += 1;
            }
            else
            {
                clockMin = 0;
                clockHr = (clockHr < 12) ? clockHr + 1 : 1;
            }
            
            Screen0_UpdateClockLabels(clockHr, clockMin);
            break;
        }
        case APP_EVENT_STOP_SCROLL:
        {
            Screen0_LineWidget2->fn->setVisible(Screen0_LineWidget2, LE_FALSE);
            Screen0_LineWidget3->fn->setVisible(Screen0_LineWidget3, LE_FALSE);
            
            break;
        }
        case APP_EVENT_START_SCROLL:
        {
            Screen0_LineWidget2->fn->setVisible(Screen0_LineWidget2, LE_TRUE);
            Screen0_LineWidget3->fn->setVisible(Screen0_LineWidget3, LE_TRUE);            
            break;
        }
        case APP_EVENT_SCRN_START_DEMO:
        {
            isPlaying = true;

            Screen0_LineWidget2->fn->setVisible(Screen0_LineWidget2, LE_TRUE);
            Screen0_LineWidget3->fn->setVisible(Screen0_LineWidget3, LE_TRUE);            
            
            break;
        }
        default:
        {
            break;
        }
    }
    
    if (appData.isScrolling == true ||
        appData.activeScreenId == 1)
    {
        if (lastTick != tickCount && isPlaying == true)
        {
            static unsigned int i = 0;
            i = (i < 9) ? i + 1 : 0;

            Screen0_UpdateMusicBars(barAnimSizes[i][0],
                                    barAnimSizes[i][1],
                                    barAnimSizes[i][2],
                                    barAnimSizes[i][3],
                                    barAnimSizes[i][4]);
            Screen0_PanelWidget0->fn->setPosition(Screen0_PanelWidget0,
                                          PROGBAR_DEFAULT_X_POS + tickSec % 50,
                                          Screen0_MusicBar4->fn->getY(Screen0_PanelWidget0));
            
            lastTick = tickCount;
        }
    }
    screenEvents = APP_EVENT_NONE;    
}

void Screen0_OnUpdate(void)
{
    Screen0_ProcessEvents();
    Screen0_ProcessClockTemp();  
}
