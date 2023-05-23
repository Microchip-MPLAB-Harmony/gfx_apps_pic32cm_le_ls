/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  Custom SSD1309Display Top-Level Driver Source File

  File Name:
    drv_gfx_custom_external.c

  Summary:
    Top level driver for SSD1309.

  Description:
    Build-time generated implementation for the SSD1309Driver.

    Created with MPLAB Harmony Version 3.0
*******************************************************************************/




#include "definitions.h"

#include "gfx/interface/drv_gfx_disp_intf.h"
#include "drv_gfx_external_controller.h"

#include "system/time/sys_time.h"

// Default max width/height of SSD1309frame
#define DISPLAY_DEFAULT_WIDTH   480
#define DISPLAY_DEFAULT_HEIGHT  800

#define DISPLAY_WIDTH   128
#define DISPLAY_HEIGHT  64

#define PIXEL_BUFFER_COLOR_MODE GFX_COLOR_MODE_RGB_565
#define SCREEN_WIDTH DISPLAY_WIDTH
#define SCREEN_HEIGHT DISPLAY_HEIGHT

#ifdef GFX_DISP_INTF_PIN_RESET_Clear
#define DRV_SSD1309_Reset_Assert()      GFX_DISP_INTF_PIN_RESET_Clear()
#define DRV_SSD1309_Reset_Deassert()    GFX_DISP_INTF_PIN_RESET_Set()
#else
#error "ERROR: GFX_DISP_INTF_PIN_RESET not defined. Please define in Pin Manager."
#define DRV_SSD1309_Reset_Assert()
#define DRV_SSD1309_Reset_Deassert()
#endif

#define DRV_SSD1309_NCSAssert(intf)   GFX_Disp_Intf_PinControl(intf, \
                                    GFX_DISP_INTF_PIN_CS, \
                                    GFX_DISP_INTF_PIN_CLEAR)

#define DRV_SSD1309_NCSDeassert(intf) GFX_Disp_Intf_PinControl(intf, \
                                    GFX_DISP_INTF_PIN_CS, \
                                    GFX_DISP_INTF_PIN_SET)
									

#define PIXELS_PER_BYTE 8
#define LCD_FRAMEBUFFER_SIZE ((128 * 64) / PIXELS_PER_BYTE)

static uint8_t framebuffer[LCD_FRAMEBUFFER_SIZE] = {0};
									

typedef enum
{
    INIT = 0,
    RUN,
    ERROR,
} DRV_STATE;

typedef struct ILI9488_DRV 
{   
    /* Driver state */
    DRV_STATE state;
        
    /* Port-specific private data */
    void *port_priv;
} SSD1309_DRV;

SSD1309_DRV drv;

static uint32_t swapCount = 0;


/* ************************************************************************** */

/**
  Function:
    static void DRV_SSD1309_DelayMS(int ms)

  Summary:
    Delay helper function.

  Description:
    This is a helper function for delay using the system tick timer.

  Parameters:
    ms      - Delay in milliseconds

  Returns:
    None.

*/

static inline void DRV_SSD1309_DelayMS(int ms)
{
    SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

    if (SYS_TIME_DelayMS(ms, &timer) != SYS_TIME_SUCCESS)
        return;
    while (SYS_TIME_DelayIsComplete(timer) == false);
}

/**
  Function:
    static void DRV_SSD1309_Reset(void)

  Summary:
    Toggles the hardware reset to the SSD1309.

  Description:
    This function toggles the GPIO pin for asserting reset to the SSD1309.

  Parameters:
    None

  Returns:
    None

*/
static void DRV_SSD1309_Reset(void)
{
    DRV_SSD1309_Reset_Assert();
    DRV_SSD1309_DelayMS(10);
    DRV_SSD1309_Reset_Deassert();
    DRV_SSD1309_DelayMS(30);
}

int DRV_SSD1309_Initialize(void)
{
    drv.state = INIT;

    return 0;
}

static int DRV_SSD1309_Configure(SSD1309_DRV *drvPtr)
{
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drvPtr->port_priv;
    uint8_t cmd;
    uint8_t parms[16];

    DRV_SSD1309_NCSAssert(intf);

    //Set Command Lock
    cmd = 0xfd;
    parms[0] = 0x12;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Display Off
    cmd = 0xae;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    //Set Display Clock Dvide Ratio
    cmd = 0xd5;
    parms[0] = 0xa1;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Multiplex Ratio
    cmd = 0xa8;
    parms[0] = 0x1f;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Display Offset = 0
    cmd = 0xd3;
    parms[0] = 0x0;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Display Start Line = 0
    cmd = 0x40;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    // Set Segment Remap Col127
    cmd = 0xa1;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    //Output Scan Down
    cmd = 0xc8;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    //Set Com Pins
    cmd = 0xda;
    parms[0] = 0x12;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Contrast Control Bank0
    cmd = 0x81;
    parms[0] = 0xef;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set PreCharge Period
    cmd = 0xd9;
    parms[0] = 0x15;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set VCOMH Deselect Level
    cmd = 0xdb;
    parms[0] = 0x8;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //GDRAM and Display On
    cmd = 0xa4;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    //Set Addressing Mode = Horizontal
    cmd = 0x20;
    parms[0] = 0x0;
    GFX_Disp_Intf_WriteCommand(intf, cmd);
    GFX_Disp_Intf_Write(intf, parms, 1);

    //Set Normal Display
    cmd = 0xa6;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    //Set Display On
    cmd = 0xaf;
    GFX_Disp_Intf_WriteCommand(intf, cmd);

    DRV_SSD1309_NCSDeassert(intf);

    return 0;
}


/**
  Function:
    static void DRV_SSD1309_Update(void)

  Summary:
    Driver-specific implementation of GFX HAL update function.

  Description:
    On GFX update, this function flushes any pending pixels to the SSD1309.

  Parameters:
    None.

  Returns:
    * GFX_SUCCESS       - Operation successful
    * GFX_FAILURE       - Operation failed

*/
void DRV_SSD1309_Update(void)
{
    uint32_t openVal;
    
    if(drv.state == INIT)
    {
        openVal = GFX_Disp_Intf_Open();
        
        drv.port_priv = (void *)openVal;
        
        if (drv.port_priv == 0)
        {
            drv.state = ERROR;
            return;
        }

        DRV_SSD1309_Reset();

        DRV_SSD1309_Configure(&drv);

        drv.state = RUN;
    }
}

static inline uint8_t DRV_SSD1309_FB_Get_Byte(uint8_t * fb,
                                         uint8_t page,
                                         uint8_t column)
{
	return *(fb + (page * DISPLAY_WIDTH) + column);
}

static inline void DRV_SSD1309_FB_Set_Byte(uint8_t * fb,
                                      uint8_t page,
                                      uint8_t column,
                                      uint8_t data)
{
	*(fb + (page * DISPLAY_WIDTH) + column) = data;
}

static void DRV_SSD1309_WriteFrame(void)
{
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    uint8_t cmd[16];
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_PinControl(intf, GFX_DISP_INTF_PIN_RSDC, GFX_DISP_INTF_PIN_CLEAR);
    
    //Set Column Address
    cmd[0] = 0x21;
    cmd[1] = 0;
    cmd[2] = DISPLAY_WIDTH - 1;
    GFX_Disp_Intf_Write(intf, cmd, 3);
    
    //Set Page Address
    cmd[0] = 0x22;
    cmd[1] = 0;
    cmd[2] = (DISPLAY_HEIGHT / 8) - 1;
    GFX_Disp_Intf_Write(intf, cmd, 3);
    
    
    GFX_Disp_Intf_WriteData(intf, framebuffer, DISPLAY_WIDTH * DISPLAY_HEIGHT / 8);
    
    DRV_SSD1309_NCSDeassert(intf);    
}


gfxResult DRV_SSD1309_BlitBuffer(int32_t x,
                                           int32_t y,
                                           gfxPixelBuffer* buf)
{

    uint8_t page, pixel_mask, pixel_value, lx, ly;
	
	if (drv.state != RUN)
        return GFX_FAILURE;

    if (buf == NULL ||
        x > DISPLAY_WIDTH - 1 ||
        y > DISPLAY_HEIGHT - 1)
        return GFX_FAILURE;

    for (ly = 0; ly < buf->size.height; ly++)
    {
        for (lx = 0; lx < buf->size.width; lx++)
        {
            gfxColor color = gfxPixelBufferGet(buf, lx, ly);

            //determine the page and column based on pixel coordinates
            page = (y + ly) / PIXELS_PER_BYTE;

            pixel_mask = (1 << ((y + ly) - (page * 8)));

            //Read the pixel data from frame buffer memory
            pixel_value = DRV_SSD1309_FB_Get_Byte(framebuffer, page, x + lx);

            if (color == 0)
            {
                pixel_value &= ~pixel_mask;
            }
            else
            {
                pixel_value |= pixel_mask;
            }

            DRV_SSD1309_FB_Set_Byte(framebuffer, page, x + lx, pixel_value);
        }
    }
    
    return GFX_SUCCESS;

    return GFX_SUCCESS;
}

gfxDriverIOCTLResponse DRV_SSD1309_IOCTL(gfxDriverIOCTLRequest request,
                                     void* arg)
{
    gfxIOCTLArg_Value* val;
    gfxIOCTLArg_DisplaySize* disp;
    gfxIOCTLArg_LayerRect* rect;
    
    switch(request)
    {
        case GFX_IOCTL_FRAME_END:
        {
            DRV_SSD1309_WriteFrame();
			
            return GFX_IOCTL_OK;
        }	
        case GFX_IOCTL_GET_COLOR_MODE:
        {
            val = (gfxIOCTLArg_Value*)arg;
            
            val->value.v_colormode = PIXEL_BUFFER_COLOR_MODE;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_BUFFER_COUNT:
        {
            val = (gfxIOCTLArg_Value*)arg;
            
            val->value.v_uint = 1;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_DISPLAY_SIZE:
        {
            disp = (gfxIOCTLArg_DisplaySize*)arg;            
            
            disp->width = DISPLAY_WIDTH;
            disp->height = DISPLAY_HEIGHT;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_LAYER_COUNT:
        {
            val = (gfxIOCTLArg_Value*)arg;
            
            val->value.v_uint = 1;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_ACTIVE_LAYER:
        {
            val = (gfxIOCTLArg_Value*)arg;
            
            val->value.v_uint = 0;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_LAYER_RECT:
        {
            rect = (gfxIOCTLArg_LayerRect*)arg;
            
            rect->base.id = 0;
            rect->x = 0;
            rect->y = 0;
            rect->width = DISPLAY_WIDTH;
            rect->height = DISPLAY_HEIGHT;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_VSYNC_COUNT:
        {
            val = (gfxIOCTLArg_Value*)arg;
            
            val->value.v_uint = swapCount;
            
            return GFX_IOCTL_OK;
        }
        case GFX_IOCTL_GET_STATUS:
		{
            val = (gfxIOCTLArg_Value*)arg;
            
            if (drv.state == RUN)
                val->value.v_uint = 0;
            else
                val->value.v_uint = 1;
            
            return GFX_IOCTL_OK;
	    }
        default:
        { }
    }
    
    return GFX_IOCTL_UNSUPPORTED;
}

//CUSTOM CODE
void DRV_SSD1309_VerticalScroll(void)
{
    #define SSD1309_CMD_CONTINUOUS_SCROLL_V_AND_H_RIGHT 0x29
    #define SSD1309_CMD_ACTIVATE_SCROLL 0x2F

    uint8_t vparms[7] = {0, //No H Scroll
                    0, //Dummy byte for start page address
                    8, //time interval
                    0, //dummy byte for end page address
                    1, //vertical scrolling offset 1 row
                    0, //start column
                    0x7f}; //end column
    
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_CONTINUOUS_SCROLL_V_AND_H_RIGHT);
    GFX_Disp_Intf_Write(intf, vparms, 7);
    DRV_SSD1309_NCSDeassert(intf);
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_ACTIVATE_SCROLL);
    
    DRV_SSD1309_NCSDeassert(intf);
}

void DRV_SSD1309_LeftScroll(void)
{
    #define SSD1309_CMD_SCROLL_H_LEFT 0x27
    #define SSD1309_CMD_ACTIVATE_SCROLL 0x2F

    uint8_t parms[7] = {0, //Dummy byte
                        2, //start page address
                        4, //time interval
                        5, //end page
                        0, //dummy byte
                        32, //start column
                        0x7f}; //end column
    
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_SCROLL_H_LEFT);
    GFX_Disp_Intf_Write(intf, parms, 7);
    DRV_SSD1309_NCSDeassert(intf);
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_ACTIVATE_SCROLL);
    
    DRV_SSD1309_NCSDeassert(intf);
}

void DRV_SSD1309_RightScroll(void)
{
    #define SSD1309_CMD_SCROLL_H_RIGHT 0x26
    #define SSD1309_CMD_ACTIVATE_SCROLL 0x2F

    uint8_t parms[7] = {0, //Dummy byte
                        2, //start page address
                        4, //time interval
                        5, //end page
                        0, //dummy byte
                        32, //start column
                        0x7f}; //end column
    
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_SCROLL_H_RIGHT);
    GFX_Disp_Intf_Write(intf, parms, 7);
    DRV_SSD1309_NCSDeassert(intf);
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_ACTIVATE_SCROLL);
    
    DRV_SSD1309_NCSDeassert(intf);
} 

void DRV_SSD1309_SetDisplayStartLine(uint32_t lineNum)
{
    #define SSD1309_CMD_SET_DISPLAY_START_LINE(line)    (0x40 | (line))
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_SET_DISPLAY_START_LINE(lineNum));
    DRV_SSD1309_NCSDeassert(intf);
}

void DRV_SSD1309_StopScroll(void)
{
    #define SSD1309_CMD_DEACTIVATE_SCROLL                 0x2E
    
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, SSD1309_CMD_DEACTIVATE_SCROLL);
    
    DRV_SSD1309_NCSDeassert(intf);
}

void DRV_SSD1309_InverseDisplay(bool inverse)
{
    #define SSD1309_CMD_SET_NORMAL_DISPLAY              0xA6
    #define SSD1309_CMD_SET_INVERSE_DISPLAY             0xA7
    
    GFX_Disp_Intf intf = (GFX_Disp_Intf) drv.port_priv;
    
    DRV_SSD1309_NCSAssert(intf);
    GFX_Disp_Intf_WriteCommand(intf, (inverse == true) ? 
            SSD1309_CMD_SET_INVERSE_DISPLAY : 
            SSD1309_CMD_SET_NORMAL_DISPLAY);
    
    DRV_SSD1309_NCSDeassert(intf);    
    
}
//END CUSTOM CODE

