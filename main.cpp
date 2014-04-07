#include <stdlib.h>
#include <cstdio>

#include "gba.h"
#include "font.h"

#include "cascara.h"			// my header




int main() {

	Set_Background();

	// Player:
	int playerX = 19;
	int playerY = 19;
	
// ----------------------------------------------------------------------------	

	Play_Intro();

	//Game();

// ----------------------------------------------------------------------------
	


	

	//LoadPaletteObj(logoPal);
	

	  
	//LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
	
	ClearObjects();

// ----------------------------------------------------------------------------


	return 0;
}
 
/* JIRI'S NOTES ===================================





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