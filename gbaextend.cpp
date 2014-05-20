/*
**************************************************************************
**                                                                      **
**           Extension of GBA development library for AG0700            **
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

#include "gbaextend.h"


// ADAM'S TEXT =====================================================================================

// Found another way around, i.e. cascara.cpp line818, function kept for future use
void DrawText(int x, int y, const char string[]){

	int i = 0;

	while(string[i] != '\0'){
		SetTile(30, (x+i), y, string[i] | ((i % 2) == 0 ? SE_VFLIP : 0));
		i++;
	}
}


// STEFANO'S TEXT =================================================================================

/*
	SetPaletteBG(0, RGB(0, 0, 0));				// black (but actually transparent)
	SetPaletteBG(1, RGB(31, 31, 31));			// white
	SetPaletteBG(17, RGB(31, 0, 0));			// red
	SetPaletteBG(1 + 16 * 2, RGB(0, 31, 0));	// green

	int char_num_normal = 'a' | (0 << 12);		// white
	int char_num_red = 'a' | (1 << 12);
	int char_num_green = 'a' | (2 << 12);

	SetTile(30,5,5, char_num_normal);
	SetTile(30,5,6, char_num_red);
	SetTile(30,5,7, char_num_green);

*/


// my derived function:
void LoadCompressedText(){				// works only in | BG_4BPP |

	for(char c = 0; c < 128; c++){
		uint8_t font_compressed[32];
		for(char x = 0; x < 64; x += 2)
		{
			font_compressed[x >> 1] = font_bold[c][x] | (font_bold[c][x + 1] << 4);
		}
		LoadTile4(0,c,font_compressed);
	}

}





// JIRI'S 32-bit FUNCTIONS =========================================================================

// CopyToVRAM 32-bit version --------------------------------------------------

void CopyToVRAM32(volatile uint32_t *dest, const uint32_t *src, int num_words)	// Copy data into video RAM, 32 bits at a time.
{
	while (num_words-- > 0)
	{
		*dest++ = *src++;
	}
}