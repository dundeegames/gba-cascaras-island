#include "cascara.h"			// my header

// CLASS FUNCTIONS =================================================================================


// PLAYER ---------------------------------------------------------------------










// TEXT ============================================================================================


void DrawText(int x, int y, const char string[]){

	int i = 0;

	while(string[i] != '\0'){
		SetTile(31, (x+i), y, string[i]);
		i++;
	}
}

// ---------------------------------------------------------

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


// BUTTONS =========================================================================================

bool Button_Pressed(int KEY) { // check if desired button was pressed
	
	bool x = false;
	
	if ((REG_KEYINPUT & KEY) == 0) {
	x = true;
	}
	
	
	return x;
}	// end Button_Pressed

// ----------------------------------------------------------------------------

bool Button_JustPressed(int KEY, uint16_t &oldButtons) {	// check if desired button was just pressed
	
	
	uint16_t changed = REG_KEYINPUT ^ oldButtons;			// bitwise masking on REG_KEYINPUT
	oldButtons = REG_KEYINPUT;								// storing the current button value in oldButtons
	bool x = false;
	
	if ((changed & KEY) != 0) {
	x = true;
	}
	
	
	return x;
}	// end Button_JustPressed


// COLOUR PALETTE ==================================================================================

bool Fade_PaletteObj() {					// Reduce the value of colour palette

	uint16_t background = 0x6F37;
	bool aligned = true;
	
	uint16_t colour = 0;

	uint16_t r = 0;
	uint16_t g = 0;
	uint16_t b = 0;


	for (int i = 0; i < 256; i++) {	
		colour = GetPaletteObj(i);

		r = colour & 31;					// 0x1F
		g = (colour >> 5) & 31;
		b = (colour >> 10) & 31;
		
		if (r != 23) {
			aligned = false;
			if(r < 23){
				r++;
			}
			else r--;
		}
		
		if (g != 25) {
			aligned = false;
			if(g < 25) {
				g++;
			}
			else g--;
		}
		
		if (b != 27) {
			aligned = false;
			if(b < 27) {
				b++;
			}
			else b--;
		}
		

		//SetPaletteObj(i, colour);
		SetPaletteObj(i, RGB(r, g, b));
	}

return aligned;	

} // end Fade_PaletteObj



// ----------------------------------------------------------------------------

bool Rise_PaletteObj(const uint16_t data[256]) {

	bool aligned = true;
	
	uint16_t colour = 0;

	uint16_t r = 0;
	uint16_t g = 0;
	uint16_t b = 0;
	
	uint16_t rData = 0;
	uint16_t gData = 0;
	uint16_t bData = 0;


	for (int i = 0; i < 256; i++) {
		colour = GetPaletteObj(i);

		r = colour & 31;
		g = (colour >> 5) & 31;
		b = (colour >> 10) & 31;
		
		rData = data[i] & 31;
		gData = (data[i] >> 5) & 31;
		bData = (data[i] >> 10) & 31;
		
		if (r != rData) {
			aligned = false;
			
			if(r < rData){
				r++;
			}
			else r--;
		}
		
		if (g != gData) {
			aligned = false;
			
			if(g < gData) {
				g++;
			}
			else g--;
		}
		
		if (b != bData) {
			aligned = false;
			
			if(b < bData) {
				b++;
			}
			else b--;
		}
		

		//SetPaletteObj(i, colour);
		SetPaletteObj(i, RGB(r, g, b));
	}
	
return aligned;

} // end Set_PaletteObj

// SLOW TIME =======================================================================================

void Slow_Time(int MAX) {			// wait for MAX/60 seconds
	for(int i=0; i<MAX; i++) {
		WaitVSync();
	}
} // end of Slow_Time

// SET BACKGROUND ==================================================================================

void Set_Background(){

	// Set display options.
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_BG0 | DCNT_BG1| DCNT_BG2 | DCNT_BG3 ;
	
	// Set background 3 options.
	REG_BG3CNT = BG_CBB(1) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;			// sea background
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;
	
	// Set background 2 options.
	REG_BG2CNT = BG_CBB(1) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;			// land background
	REG_BG2HOFS = 0;
	REG_BG2VOFS = 0;
	
	// Set background 1 options.
	REG_BG1CNT = BG_CBB(1) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;			// menu layer
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 4;
	
	// Set background 0 options.
	REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_8BPP | BG_REG_32x32;			// text layer
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	
// ----------------------------------------------------------------------------

	LoadPaletteBG(charblock1Pal);

	LoadTileData(1, 0, charblock1Tiles, sizeof charblock1Tiles);	
	LoadTile8(1, 0, blank_tile);			// Load blank_tile into charblock - 1 / tile - 0
	
	
	LoadScreenblock(28, seaSB);
	
	// vertically flip the tiles for upper menu
	/*
	for (int i = 0; i < 96; i++){
		menuSB[i] |= SE_VFLIP;	
	}
	*/
	
	LoadScreenblock(30, menuSB);
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 32; ++x) {
			OrTile(30, x, y, SE_VFLIP);		// amended function from gbaextend.h
		}
	}
	
	
	// set backgrounds
	for (int y = 0; y < 32; ++y){			// Ask about efficiency! Is is OK if it is jumping each loop to 3 different places in memory? Or should I rather create function and execute each SB separately?

		for (int x = 0; x < 32; ++x){
			SetTile(29, x, y, 0);			// Load blank tiles into SB 29
			//SetTile(30, x, y, 0);			// Load blank tiles into SB 30
			SetTile(31, x, y, 0);			// Load blank tiles into SB 31

		}
	}


} // end of Set_Background


// ----------------------------------------------------------------------------

void Play_Intro(){			// Play logo and sets menu

	int frameCounter = 0;
	bool showGameName = true;
	
	enum stage {start, studioRise, studioPause, studioFade, fadePause, gameRise, gamePause, gameFade, end};
	stage logoStage = start;
	
	LoadTileData(4, 0, logoTiles, sizeof logoTiles);
	
	ClearObjects();
	
	for (int i = 0; i < 256; i++) {
		SetPaletteObj(i, 0x6F37);
	}

	
	while (true){
	
		frameCounter++;

		switch(logoStage){
			
			case start:
				if(frameCounter > 120){
					SetObject(0,
					  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
					  ATTR1_SIZE(3) | ATTR1_X(56),
					  ATTR2_ID8(0));
					  
					SetObject(1,
					  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
					  ATTR1_SIZE(3) | ATTR1_X(120),
					  ATTR2_ID8(8));
			  
					logoStage = studioRise;
				}				
				break;
				
			case studioRise:
				if(!(frameCounter%5)){
					if (Rise_PaletteObj(logoPal)){
						frameCounter = 0;
						logoStage = studioPause;
					}				
				}
				break;
				
			case studioPause:
				if(frameCounter > 120){
					logoStage = studioFade;				
				}
				break;
				
			case studioFade:
				if(!(frameCounter%5)){
					if (Fade_PaletteObj()){
						SetObject(0,
						  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
						  ATTR1_SIZE(3) | ATTR1_X(56),
						  ATTR2_ID8(128));
						  
						SetObject(1,
						  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
						  ATTR1_SIZE(3) | ATTR1_X(120),
						  ATTR2_ID8(136));
						
						frameCounter = 0;
						logoStage = fadePause;
					}				
				}
				break;
				
			case fadePause:
				if(frameCounter > 120){
					logoStage = gameRise;
				}
				break;
				
			case gameRise:
				if(!(frameCounter%7)){
					if (Rise_PaletteObj(logoPal)){
						frameCounter = 0;
						logoStage = gamePause;
					}
				}
				break;
				
			case gamePause:
				if(frameCounter > 120){
					logoStage = gameFade;				
				}
				break;
				
			case gameFade:
				if(!(frameCounter%5)){
					if (Fade_PaletteObj()){
						frameCounter = 0;
						logoStage = start;				// change to end
					}				
				}
				break;
						
		}
		
		WaitVSync();
		
		UpdateObjects();
		
		if (!(frameCounter%3)){
		BG3X_offset += 1;
		REG_BG3HOFS = BG3X_offset;
		}
	}


}


// MENU ============================================================================================