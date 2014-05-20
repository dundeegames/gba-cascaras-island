#include <stdlib.h>
#include <cstdio>

#include "gba.h"
#include "font.h"

#include "cascara.h"			// my header




int main() {

	Set_Background();
	
	while(true){
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