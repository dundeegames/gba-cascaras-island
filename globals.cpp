
#include "cascara.h"			// my header

int BG3X_offset = 0;			// holds value for reading REG_BG(X)HOFS, which are write only
int BG2X_offset = 0;

int BG2Y_offset= -16;			// holds value for reading REG_BG(X)VOFS, which are write only
int BG1Y_offset= 24;

int frameCounter = 0;

GameProp* object[NUM_OBJECTS];

Score* score = new Score();