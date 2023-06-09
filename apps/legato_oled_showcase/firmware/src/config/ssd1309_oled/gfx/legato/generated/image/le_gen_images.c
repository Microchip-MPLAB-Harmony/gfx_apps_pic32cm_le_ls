#include "gfx/legato/generated/le_gen_assets.h"

/*********************************
 * Legato Image Asset
 * Name:   PlayButton20
 * Size:   20x20 pixels
 * Mode:   MONOCHROME
 ***********************************/

const uint8_t PlayButton20_data[50] =
{
    0x07,0xFE,0x00,0xE0,0x70,0x38,0x01,0xC3,0x18,0x0C,0x61,0xC0,0x6C,0x1E,0x03,0xC1,
    0xF8,0x38,0x1F,0xC1,0x81,0xFE,0x18,0x1F,0xF9,0x81,0xFF,0x98,0x1F,0xE1,0x81,0xFC,
    0x1C,0x1F,0x83,0xC1,0xE0,0x36,0x1C,0x06,0x31,0x80,0xC3,0x80,0x1C,0x0E,0x07,0x00,
    0x7F,0xE0,
};

leImage PlayButton20 =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)PlayButton20_data, // data variable pointer
        50, // data size
    },
    LE_IMAGE_FORMAT_MONO,
    {
        LE_COLOR_MODE_MONOCHROME,
        {
            20,
            20
        },
        400,
        50,
        (void*)PlayButton20_data, // data variable pointer
        0, // flags
    },
    0, // image flags
    {
        0x0, // color mask
    },
    NULL, // alpha mask
    NULL, // palette
};

/*********************************
 * Legato Image Asset
 * Name:   PauseButton20
 * Size:   20x20 pixels
 * Mode:   MONOCHROME
 ***********************************/

const uint8_t PauseButton20_data[50] =
{
    0x07,0xFE,0x00,0xE0,0x70,0x38,0x01,0xC3,0x00,0x0C,0x67,0x9E,0x6C,0x79,0xE3,0xC7,
    0x9E,0x38,0x79,0xE1,0x87,0x9E,0x18,0x79,0xE1,0x87,0x9E,0x18,0x79,0xE1,0x87,0x9E,
    0x1C,0x79,0xE3,0xC7,0x9E,0x36,0x00,0x06,0x30,0x00,0xC3,0x80,0x1C,0x0E,0x07,0x00,
    0x7F,0xE0,
};

leImage PauseButton20 =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)PauseButton20_data, // data variable pointer
        50, // data size
    },
    LE_IMAGE_FORMAT_MONO,
    {
        LE_COLOR_MODE_MONOCHROME,
        {
            20,
            20
        },
        400,
        50,
        (void*)PauseButton20_data, // data variable pointer
        0, // flags
    },
    0, // image flags
    {
        0x0, // color mask
    },
    NULL, // alpha mask
    NULL, // palette
};

