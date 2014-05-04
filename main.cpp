#include <stdlib.h>
#include <cstdio>

#include "gba.h"
#include "font.h"

#include "cascara.h"			// my header




int main() {

	Set_Background();
	
	while(gameRunning){
		// ------------------------------------------------

		Play_Intro();

		Play_Game();

		// ------------------------------------------------
	}
	
	// release all memory ---------------
	delete time;
	delete score;
	
	return 0;
}




/*
// !!! BUG REPORT !!! ==============================================================================

01/05/2014	After creating "enemy bullet" the sprite sheet char-block starts  appearing on the
			screen. Seems like I am overwriting some graphical memory while going with bullet to
			negative numbers!
			
	FIX:	Seems like bug was in enemy shooting while already off the screen. Adjusted
			Enemy::shoot() to activate only while still on screen. No glitches since...
			
			

// =================================================================================================
*/