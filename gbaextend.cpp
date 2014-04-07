/*
**************************************************************************
**                                                                      **
**           Extension of GBA development library for AG0700            **
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

#include "gbaextend.h"


// ADAM'S TEXT =====================================================================================

/*
void DrawText(int x, int y, const char string[]){

	int i = 0;

	while(string[i] != '\0'){
		SetTile(30, (x+i), y, string[i] | ((i % 2) == 0 ? SE_VFLIP : 0));
		i++;
	}
}


// ---------------------------------------------------------

*/


// STEFANOS'S TEXT =================================================================================

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
// JIRI'S 32-bit FUNCTIONS =========================================================================

// CopyToVRAM 32-bit version --------------------------------------------------

void CopyToVRAM32(volatile uint32_t *dest, const uint32_t *src, int num_words)	// Copy data into video RAM, 32 bits at a time.
{
	while (num_words-- > 0)
	{
		*dest++ = *src++;
	}
}








// ----------------------------------------------------------------------------

/*
// JIRI'S NOTES ====================================================================================




// ----------------------------------------------------------------------------
a[i]
*(a + i)

int *p;
*p
p[0]

int x;

char x[24];


x += y	// take x+y and assign it to x
x |= y	// take x|y (bitwise OR) and assign it to x

// ----------------------------------------------------------------------------

// MAX'S NOTES =====================================================================================================================================================================

void LoadStartFrame(uint16_t frame)
{
	bool screenLoop = false;
	uint16_t endOfGraphic, startOfGraphic;
	// Title image scrolling
	for(uint16_t i = 0; i < SCREEN_HEIGHT; i++)
	{
		
		endOfGraphic = frame*2 + SCREEN_WIDTH;
		startOfGraphic = SCREEN_WIDTH - (endOfGraphic % (SCREEN_WIDTH*2));
		screenLoop = (endOfGraphic > (SCREEN_WIDTH*2)) ? true : false;
		if(!screenLoop)
		{
			memcpy((void*)&BackBuffer[i * SCREEN_WIDTH / 2], &TitleScreenBackgroundBitmap[frame + i * SCREEN_WIDTH], SCREEN_WIDTH);
		} else {
			memcpy((void*)&BackBuffer[i * SCREEN_WIDTH / 2], &TitleScreenBackgroundBitmap[frame + i * SCREEN_WIDTH], startOfGraphic);
			memcpy((void*)&BackBuffer[(i * SCREEN_WIDTH / 2) + (startOfGraphic / 2)], &TitleScreenBackgroundBitmap[i * SCREEN_WIDTH], SCREEN_WIDTH - startOfGraphic);
		}
	}
	// Title text
	for(uint16_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH / 4; i++)
	{
		if(TitleScreenTextBitmap[i] != 0x0000)
			BackBuffer[i] = TitleScreenTextBitmap[i];
	}
}

void StartGame()
{
	uint16_t frameCounter = 0;
	LoadStartPal();
	LoadStartFrame(frameCounter);
	REG_DISPCNT = MODE4	| DCNT_BG2;
	while(true)
	{
		frameCounter++;
		frameCounter = frameCounter % SCREEN_WIDTH;
		LoadStartFrame(frameCounter);
		FlipBuffers();
		// Start game if start is pressed
		if((REG_KEYINPUT & KEY_START) == 0)
		{
			Game = Main;
			break;
		}
	}
}


*/


