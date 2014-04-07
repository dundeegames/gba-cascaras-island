#include <stdlib.h>
#include <cstdio>

#include "gba.h"
#include "font.h"

#include "cascara.h"			// my header




int main() {

	Set_Background();

// ------------------------------------------------

	Play_Intro();

	Play_Game();

// ------------------------------------------------
	
	return 0;
}



 
/* JIRI'S NOTES ===================================

	
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