/*
**************************************************************************
**                                                                      **
**           Extension of GBA development header for AG0700,            **
**                     based on:  gba.h by eloist 		                **
**                                                                      **
**    Created by:			Jiri Klic			2014                    **
**                          Stefano Musumeci    2014                    **
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


// ADAM'S FUNCTIONS ================================================================================


// Set a tile entry within a (32x32) screenblock ------------------------------
static inline void OrTile(int screenblock, int x, int y, int tile_flags)
{
	REG_VIDEO_BASE[(screenblock * 1024) + (y * 32) + x] |= tile_flags;
}



// STEFANOS'S TEXT =================================================================================



// JIRI'S FUNCTIONS ================================================================================

/*
// Load an 8bpp tile into video RAM.
static inline void LoadTile8(int charblock, int tile_num, const uint8_t tile_data[64])
{
	CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 32), (const uint16_t *) tile_data, 32);
}

void CopyToVRAM(volatile uint16_t *dest, const uint16_t *src, int num_words)
{
	while (num_words-- > 0)
	{
		*dest++ = *src++;
	}
}


*/

// Custom function to overwrite artefat pixels on bottom menu
// Load an 8bpp tile into video RAM.
static inline void fixArtefacts(int charblock, int tile_num, const uint8_t tile_data[64])
{
	CopyToVRAM(REG_VIDEO_BASE + (charblock * 8192) + (tile_num * 32), 0x0000, 32);
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