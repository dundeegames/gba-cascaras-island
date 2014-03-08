#include <stdlib.h>
#include <cstdio>

#include "gba.h"
#include "font.h"

#include "cascara.h"			// my header


// The entry point for the game
int main() {

	Set_Background();

	// Player:
	int playerX = 19;
	int playerY = 19;
	
	int frameCounter = 0;
	
	enum stage {start, studioRise, studioPause, studioFade, fadePause, gameRise, gamePause, gameFade, end};
	stage logoStage = start;
	
// ----------------------------------------------------------------------------	

	//Menu();

	//Game();

// ----------------------------------------------------------------------------
	
    int BG3X_offset=0;						// holds value for reading REG_BG(X)HOFS, which are write only
	int BG2X_offset=0;

	
	// Set up the palette.
	//LoadPaletteObj(spritePal);
	//LoadPaletteObj(logoPal);
	

	  
	//LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
	LoadTileData(4, 0, logoTiles, sizeof logoTiles);	
	ClearObjects();

// ----------------------------------------------------------------------------

	for (int i = 0; i < 256; i++) {
		SetPaletteObj(i, 0x6F37);
	}

	
	while (true){
	
		frameCounter++;
		
		if((logoStage == start) && (frameCounter > 120)){
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

		else if((logoStage == studioRise) && (!(frameCounter%5))){
		
			if (Rise_PaletteObj(logoPal)){
				frameCounter = 0;
				logoStage = studioPause;
			}
		}
		
		else if((logoStage == studioPause) && (frameCounter > 120)){
			logoStage = studioFade;
		}

		
		else if((logoStage == studioFade) && (!(frameCounter%5))){
		
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

		else if((logoStage == fadePause) && (frameCounter > 120)){
			logoStage = gameRise;
		}
		
		else if((logoStage == gameRise) && (!(frameCounter%7))){
		
			if (Rise_PaletteObj(logoPal)){
				frameCounter = 0;
				logoStage = gamePause;
			}
		}

		
		else if((logoStage == gamePause) && (frameCounter > 120)){
			logoStage = gameFade;
		}

		else if((logoStage == gameFade) && (!(frameCounter%5))){
		
			if (Fade_PaletteObj()){
				frameCounter = 0;
				logoStage = start;				// change to end
			}
		}
	
		WaitVSync();
		
		UpdateObjects();
		
		if (!(frameCounter%3)){
		BG3X_offset += 1;
		REG_BG3HOFS = BG3X_offset;
		}
	}

	return 0;
}

/* JIRI'S NOTES ===================================

	for (int i = 0; i < 128; i++){			// Load Bold Font into charblock 0
		LoadTile8(0, i, font_bold[i]);	
	}



	SetObject(0,
	          ATTR0_SHAPE(1) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(playerY),
			  ATTR1_SIZE(2) | ATTR1_X(playerX),
			  ATTR2_ID8(0));
	
	DrawText(5, 5, "hello, world!");
	DrawText(10, 7, "how is it going?");
	DrawText(15, 9, "I'm fine.");

	
	
		if (Button_Pressed(KEY_RIGHT)) {
		
			if (playerX < (SCREEN_WIDTH - 32)) {
				playerX++;		
			}
		}
		
		else if (Button_Pressed(KEY_LEFT)) {
		
			if (playerX > 0) {
				playerX--;			
			}
		}
		
		if (Button_Pressed(KEY_UP)) {
		
			if (playerY > 0) {
				playerY--;			
			}
		}
		
		else if (Button_Pressed(KEY_DOWN)) {
			if (playerY < (SCREEN_HEIGHT - 16)) {
				playerY++;		
			}
		}
		
		SetObjectX(0, playerX);
		SetObjectY(0, playerY);
	


*/