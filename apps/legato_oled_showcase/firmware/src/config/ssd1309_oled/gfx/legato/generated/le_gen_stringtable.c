#include "gfx/legato/generated/le_gen_assets.h"

/*****************************************************************************
 * Legato String Table
 * Encoding        ASCII
 * Language Count: 1
 * String Count:   8
 *****************************************************************************/

/*****************************************************************************
 * string table data
 * 
 * this table contains the raw character data for each string
 * 
 * unsigned short - number of indices in the table
 * unsigned short - number of languages in the table
 * 
 * index array (size = number of indices * number of languages
 * 
 * for each index in the array:
 *   unsigned byte - the font ID for the index
 *   unsigned byte[3] - the offset of the string codepoint data in
 *                      the table
 * 
 * string data is found by jumping to the index offset from the start
 * of the table
 * 
 * string data entry:
 *     unsigned short - length of the string in bytes (encoding dependent)
 *     codepoint data - the string data
 ****************************************************************************/

const uint8_t stringTable_data[78] =
{
    0x08,0x00,0x01,0x00,0x04,0x24,0x00,0x00,0x02,0x28,0x00,0x00,0x03,0x2C,0x00,0x00,
    0x02,0x30,0x00,0x00,0x04,0x34,0x00,0x00,0x04,0x38,0x00,0x00,0x01,0x40,0x00,0x00,
    0x04,0x4A,0x00,0x00,0x02,0x00,0x50,0x4D,0x02,0x00,0x30,0x30,0x02,0x00,0x37,0x37,
    0x01,0x00,0x3A,0x00,0x01,0x00,0x43,0x00,0x06,0x00,0x4A,0x61,0x6E,0x20,0x30,0x31,
    0x08,0x00,0x4D,0x75,0x73,0x69,0x63,0x20,0x30,0x31,0x01,0x00,0x46,0x00,
};

/* font asset pointer list */
leFont* fontList[5] =
{
    (leFont*)&BigLabelFont,
    (leFont*)&SmallFont,
    (leFont*)&XlargeFont,
    (leFont*)&LargeFont,
    (leFont*)&SmallFontMedium,
};

const leStringTable stringTable =
{
    {
        LE_STREAM_LOCATION_ID_INTERNAL, // data location id
        (void*)stringTable_data, // data address pointer
        78, // data size
    },
    (void*)stringTable_data, // string table data
    fontList, // font lookup table
    LE_STRING_ENCODING_ASCII // encoding standard
};


// string list
leTableString string_PMLabel;
leTableString string_TimeDefault;
leTableString string_TempLabel;
leTableString string_ColonLabel;
leTableString string_TempUnitC;
leTableString string_DateLabel;
leTableString string_SongLabel;
leTableString string_TempUnitF;

void initializeStrings(void)
{
    leTableString_Constructor(&string_PMLabel, stringID_PMLabel);
    leTableString_Constructor(&string_TimeDefault, stringID_TimeDefault);
    leTableString_Constructor(&string_TempLabel, stringID_TempLabel);
    leTableString_Constructor(&string_ColonLabel, stringID_ColonLabel);
    leTableString_Constructor(&string_TempUnitC, stringID_TempUnitC);
    leTableString_Constructor(&string_DateLabel, stringID_DateLabel);
    leTableString_Constructor(&string_SongLabel, stringID_SongLabel);
    leTableString_Constructor(&string_TempUnitF, stringID_TempUnitF);
}
