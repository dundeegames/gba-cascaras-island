/*
**************************************************************************
**                                                                      **
**           Extension of GBA development header for AG0700,            **
**                     based on:  gba.h by eloist 		                **
**                                                                      **
**    Created by:			Jiri Klic			2014                    **
**                                                                      **
**    Contributors:         Adam Sampson	    2014                    **
**                          Stefano Musumeci    2014                    **
**                                                                      **
**    ==============================================================    **
**    Note:                                                             **
**         32-bit version of regular functions are not used in code     **
**         at the moment, but were developed for future experiment      **
**         with hopes of hardware performance improvement.              **
**                                                                      **
**    ==============================================================    **
**                                                                      **
**    If you have additions or corrections to this code, please send    **
**    them to Adam Sampson <a.sampson@abertay.ac.uk>.				    **
**                                                                      **
**************************************************************************
*/


#ifndef GBAEXTEND_H
#define GBAEXTEND_H


#include "gba.h"
#include "font.h"

// ADAM'S FUNCTION =================================================================================


// Found another way around, i.e. cascara.cpp line818, function kept for future use
static inline void OrTile(int screenblock, int x, int y, int tile_flags)
{
	REG_VIDEO_BASE[(screenblock * 1024) + (y * 32) + x] |= tile_flags;
}



// STEFANOS'S TEXT =================================================================================

void LoadCompressedText();



// JIRI'S FUNCTIONS ================================================================================

// Copy a tile entry from a (32x32) screenblock1 to (32x32) screenblock2.
static inline void CopyTile(int screenblock1, int x1, int y1, int screenblock2, int x2, int y2)
{
	REG_VIDEO_BASE[(screenblock2 * 1024) + (y2 * 32) + x2] = REG_VIDEO_BASE[(screenblock1 * 1024) + (y1 * 32) + x1];
}

// CopyTile from screenblock1 to screenblock2 and then Set a tile entry within a screenblock1 to 0.
static inline int MoveTile(int screenblock1, int x1, int y1, int screenblock2, int x2, int y2)
{
	REG_VIDEO_BASE[(screenblock2 * 1024) + (y2 * 32) + x2] = REG_VIDEO_BASE[(screenblock1 * 1024) + (y1 * 32) + x1];
	REG_VIDEO_BASE[(screenblock1 * 1024) + (y1 * 32) + x1] = 0;
}

// Custom function to overwrite artefact pixels on bottom menu
// not needed since last charblock update
static inline void FixTile8(int charblock, int tile_num)
{
	volatile uint16_t *dest = REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 32);
	for(int i = 0; i < 4; i++){
		*dest++ = 0;
	}
	//CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 32), 0x0000, 32);
}

// ---------------------------------------------------

//SetObjectTile(object, ATTR2_ID8(tile)| ATTR2_PRIO(priority))
static inline void SetObjectTile(int object, uint16_t attr2)
{
	ObjAttr& obj(ObjBuffer[object]);
	obj.attr2 = attr2;
}


// 32-bit FUNCTIONS --------------------------------------------------------------------------------

// Copy data into video RAM, 32 bits at a time.
void CopyToVRAM32(volatile uint32_t *dest, const uint32_t *src, int num_words);


// INLINE FUNCTIONS --------------------------------------------------------------------------------

// Load the entire background palette from an array.
static inline void LoadPaletteBG32(const uint32_t palette_data[128])
{
	volatile uint32_t *p = (volatile uint32_t *) REG_PALETTE_BG;
	
	CopyToVRAM32(p, palette_data, 128);
}


// LoadPaletteObj 32-bit version ----------------------------------------------

// Load the entire object palette from an array.

static inline void LoadPaletteObj32(const uint32_t palette_data[128])
{
	volatile uint32_t *p = (volatile uint32_t *) REG_PALETTE_OBJ;
	
	CopyToVRAM32(p, palette_data, 128);
}



// LoadTileData 32-bit version ------------------------------------------------

// Load a variable amount of tile data from an array,
// storing it in charblock memory starting at the given position. data_bytes is the length of the data in bytes.
static inline void LoadTileData32(int charblock, int first_tile, const void *data, int data_bytes)
{
	volatile uint32_t *p = (volatile uint32_t *) REG_VIDEO_BASE;
	
	CopyToVRAM32(p + (charblock * 4096) + (first_tile * 16),
	           (const uint32_t *) data, data_bytes / 4);
}







#endif