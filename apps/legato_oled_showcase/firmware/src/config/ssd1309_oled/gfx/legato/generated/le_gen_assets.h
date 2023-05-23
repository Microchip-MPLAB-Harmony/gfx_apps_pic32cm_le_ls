/*******************************************************************************
 Module for Microchip Legato Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    le_gen_assets.h

  Summary:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.


  Description:
    Header file containing a list of asset specifications for use with the
    Legato Graphics Stack.

*******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C)  Microchip Technology Inc. and its subsidiaries.
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

// DOM-IGNORE-END

#ifndef LE_GEN_ASSETS_H
#define LE_GEN_ASSETS_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

#include "gfx/legato/legato.h"

extern const lePalette leGlobalPalette;

/*****************************************************************************
 * Legato Graphics Image Assets
 *****************************************************************************/
/*********************************
 * Legato Image Asset
 * Name:   PlayButton20
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: MONOCHROME
 ***********************************/
extern leImage PlayButton20;

/*********************************
 * Legato Image Asset
 * Name:   PauseButton20
 * Size:   20x20 pixels
 * Type:   RGB Data
 * Format: MONOCHROME
 ***********************************/
extern leImage PauseButton20;

/*****************************************************************************
 * Legato Graphics Font Assets
 *****************************************************************************/
/*********************************
 * Legato Font Asset
 * Name:         BigLabelFont
 * Height:       21
 * Baseline:     15
 * Style:        Plain
 * Glyph Count:  95
 * Range Count:  1
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont BigLabelFont;

/*********************************
 * Legato Font Asset
 * Name:         SmallFont
 * Height:       21
 * Baseline:     12
 * Style:        Plain
 * Glyph Count:  95
 * Range Count:  8
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont SmallFont;

/*********************************
 * Legato Font Asset
 * Name:         XlargeFont
 * Height:       21
 * Baseline:     19
 * Style:        Plain
 * Glyph Count:  95
 * Range Count:  3
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont XlargeFont;

/*********************************
 * Legato Font Asset
 * Name:         LargeFont
 * Height:       21
 * Baseline:     14
 * Style:        Plain
 * Glyph Count:  95
 * Range Count:  2
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont LargeFont;

/*********************************
 * Legato Font Asset
 * Name:         SmallFontMedium
 * Height:       21
 * Baseline:     9
 * Style:        Plain
 * Glyph Count:  95
 * Range Count:  10
 * Glyph Ranges: 0x20-0x7E
***********************************/
extern leRasterFont SmallFontMedium;

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   8
 *****************************************************************************/

// language IDs
#define language_Default    0

// string IDs
#define stringID_PMLabel    0
#define stringID_TimeDefault    1
#define stringID_TempLabel    2
#define stringID_ColonLabel    3
#define stringID_TempUnitC    4
#define stringID_DateLabel    5
#define stringID_SongLabel    6
#define stringID_TempUnitF    7

extern const leStringTable stringTable;


// string list
extern leTableString string_PMLabel;
extern leTableString string_TimeDefault;
extern leTableString string_TempLabel;
extern leTableString string_ColonLabel;
extern leTableString string_TempUnitC;
extern leTableString string_DateLabel;
extern leTableString string_SongLabel;
extern leTableString string_TempUnitF;

void initializeStrings(void);
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* LE_GEN_ASSETS_H */
