/*
// MAIN.CPP






// CASCARA.CPP
// CLASS FUNCTIONS ===============================================================================================================================================================


// PLAYER ----------------------------------------------------------------------------------

player::player(int x, int y, int wdt, int hgt) {							// constructor definition
				
	pointX = x;
	pointY = y;
			
	width = wdt;
	height = hgt;

}
		
void player::move(int dx, int dy) {			// move player on the screen
	
	if (((pointX + dx) > 0) && ((pointX + width + dx) < (SCREEN_WIDTH-80) )) {			// fly only in first 2/3
		pointX += dx;		
	}
	
	if (((pointY + dy) > 20) && ((pointY + height + dy) < (SCREEN_HEIGHT-30) )) {
		pointY += dy;
	}
		
} // end of move();

void player::draw(){							// draws player on the screen

	uint16_t colour = 0;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			colour = sprite[((25+j)*SCREEN_WIDTH)+ i];
			if (colour != 0x00) {
				PlotPixel8(pointX+i, pointY+j, colour);
			}
		}
	}
	
} // end of draw();

void player::clear() {						// clears player from the screen

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			PlotPixel8(pointX+i, pointY+j, 0x00);
		}
	}
	
} // end of clear();


// BULLET ----------------------------------------------------------------------------------

bullet::bullet(int x, int y, int _dx, int _dy) {							// constructor definition
				
	pointX = x;
	pointY = y;
			
	dx = _dx;
	dy = _dy;
			
}
		
void bullet::move() {							// move bullet on the screen
	
	if (((pointX + dx) > 0) && ((pointX + 2 + dx) < (SCREEN_WIDTH) )) {			// fly only in first 2/3
		pointX += dx;		
	}
	
	if (((pointY + dy) > 20) && ((pointY + 2 + dy) < (SCREEN_HEIGHT-30) )) {
		pointY += dy;
	}
		
} // end of move();

void bullet::draw(){							// draws bullet on the screen

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 2; i++) {
			PlotPixel8(i, j, 5);
		}
	}
	
} // end of draw();

void bullet::clear() {						// clears bullet from the screen

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 2; i++) {
			PlotPixel8(i, j, 0x00);
		}
	}
	
} // end of clear();

*/

// FONT =========================================================================================================================================================================
/*
// Draw ASCII character (c) at (x,y) coordinates in colour (colour)
void Draw_Char(int x, int y, int colour, char c) {
	for (int iY = 0; iY < 8; iY++) {
		for (int iX = 0; iX < 8; iX++) {
			if (font_bold[int(c)][(iY * 8) + iX]) {
				PlotPixel8(x + iX, y + iY, colour);
			}
		}
	}
}

// ----------------------------------------------------------------------------------

// Draw \0-terminated string (s) at position (x,y) in colour (colour)
void Draw_String(int x, int y, int colour, const char *s) {
	while (*s != '\0') {
		Draw_Char(x, y, colour, *s);
		x += 8;
		s++;
	}
}


// ----------------------------------------------------------------------------------

void Set_Background() {

	uint16_t colour = 0;

	for (int y=0; y<SCREEN_HEIGHT; y++) {				// Draw Background
	
		for (int x=0; x<SCREEN_WIDTH; x++) {
			if ((y > 20) && (y < 135)) {
			colour = 0x00;							// Clean Background area
			}
			else {
			colour = sprite[(y*SCREEN_WIDTH)+x];
			}
			PlotPixel8(x, y, colour);
		}
	}

	// code works, but the screen is total mess!! DO NOT USE!!

	// Fill the display by writing 32 bits at a time.
	int count = (240 * 160) / 4;
	volatile uint32_t *p = (volatile uint32_t *) BackBuffer;
	
	for (int i = 0; i < count; i++) {
		// Set up a 32-bit value containing four pixels in the right colour.
		uint32_t value = (background[i] << 24) | (background[i+1] << 16) | (background[i+2] << 8) | background[i+3];
		*p++ = value;
	}

	
} // end Set_Background


// ----------------------------------------------------------------------------



void Set_Palette (int x) {					// Reduce the value of colour palette by (x)

	int colour = 0;

	for (int i = 0; i < 16; i++) {			// red palette
		colour = 15+i-x;
		if (colour < 0) colour = 0;			// make sure the colour is not less than 0
		SetPaletteBG(16+i, RGB(colour, 0, 0));
	}
	for (int i = 0; i < 16; i++) {			// green palette
		colour = 15+i-x;
		if (colour < 0) colour = 0;				// make sure the colour is not less than 0
		SetPaletteBG(32+i, RGB(0, colour, 0));
	}
	for (int i = 0; i < 16; i++) {			// blue palette
		colour = 15+i-x;
		if (colour < 0) colour = 0;				// make sure the colour is not less than 0
		SetPaletteBG(48+i, RGB(0, 0, colour));
	}
	for (int i = 0; i < 32; i++) {			// gray palette
		colour = i-x;
		if (colour < 0) colour = 0;				// make sure the colour is not less than 0
		SetPaletteBG(64+i, RGB(colour, colour, colour));
	}


} // end Set_Palette


// MENU FUNCTION ================================================================================================================================================================

void Draw_Logo() {

	uint16_t colour = 0;

	for (int y=70; y<115; y++) {						// values based on coordinates and size in sprite sheet
	
		for (int x=40; x<160; x++) {
			colour = sprite[(y*SCREEN_WIDTH)+ x];
			if (colour != 0x00) {
				PlotPixel8(x+20, y-35, colour);
			}
		}
	}

}
*/
// ----------------------------------------------------------------------------------
/*
void Draw_Button(int x, int y, bool select, const char *s) {			// (in the future make it scalable based on size of string)

	uint16_t colour = 0;
	
	
	if (select) {
	
		for (int j=0; j<20; j++) {						// values based on coordinates and size in sprite sheet
	
			for (int i=0; i<80; i++) {
				colour = sprite[((j+25)*SCREEN_WIDTH)+ (i+160)];
				if (colour != 0x00) {
					PlotPixel8((x+i),(y+j), colour);
				}
			}
		}
		
		//Draw_String(x, y, 153, str);
		while (*s != '\0') {
			Draw_Char(x+6, y+6, 154, *s);
			x += 8;
			s++;
		}
  
	}
	else {
	
		for (int j=0; j<20; j++) {						// values based on coordinates and size in sprite sheet
	
			for (int i=0; i<80; i++) {
				colour = sprite[((j+45)*SCREEN_WIDTH)+ (i+160)];
				if (colour != 0x00) {
					PlotPixel8((x+i),(y+j), colour);
				}
			}
		}
  	
		while (*s != '\0') {
			Draw_Char(x+6, y+6, 153, *s);
			x += 8;
			s++;
		}
	
	}


}

// ----------------------------------------------------------------------------------

void Rules() {							// Draw Rules Menu
	
	
	
	
	Set_Background();
	Draw_Button(80, 110, 0, " SELECT");
	Draw_String(15, 30, 233, "Work in progress..");
	Draw_String(15, 70, 233, "PRESS SELECT");
	FlipBuffers();
	CopyScreen();
	
		
	while (true) {
	
		
		if (Button_Pressed(KEY_SELECT)) {
			Draw_Button(80, 110, 1, " SELECT");
			FlipBuffers();
			Slow_Time(30);
			break;
		}
		
		
		
		WaitVSync();
	}
	Set_Background();
	Draw_Logo();
	FlipBuffers();
}


// ----------------------------------------------------------------------------------



// The entry point for the menu 
void Menu() {

	LoadPaletteBG(spritePalette);

	bool inMenu = true;
	
	while (inMenu) {

		bool startSelect = true;				// draw first screen with START selected
		Set_Background();
		Draw_Logo();
		CopyScreen();
			
	
		while(true) {
		
			FlipBuffers();
			
			if (startSelect) {
				Draw_Button(25, 100, 1, "  START");
				Draw_Button(135, 100, 0, "  RULES");
			}
			else {
				Draw_Button(25, 100, 0, "  START");
				Draw_Button(135, 100, 1, "  RULES");
			}
		
			
		
			// Check user input
			if (Button_Pressed(KEY_RIGHT) && startSelect) {
				 startSelect = !startSelect;
			}
			
			if (Button_Pressed(KEY_LEFT) && !startSelect) {
				startSelect = !startSelect;
			}
		
			if (Button_Pressed(KEY_START) && startSelect) {
				inMenu = false;
				break;
			}
			
			if (Button_Pressed(KEY_START) && !startSelect) {
				Rules();
				break;
			}
		
		}
		
	}

}


// ----------------------------------------------------------------------------------

void Update_SkillMenu(int x) {

	uint16_t colour = 0;
	
	for (int y=149; y<158; y++) {						// Draw Specific pixels from the sprite
	
		for (int x=176; x<200; x++) {
			colour = sprite[(y*SCREEN_WIDTH)+x];
			PlotPixel8(x, y, colour);
		}
	}

	
	//To print variables, use snprintf to produce a string, then print the string.


	char buf[5];
	snprintf(buf, sizeof buf, "% 4d", x);

	Draw_String(168, 149, 153, buf);



}


// GAME FUNCTION ================================================================================================================================================================

// The entry point for the game
void Game()	{

	Set_Background();									// Draw Game Menu
	Draw_String(5, 3, 153, "SCORE: 9999");
	Draw_String(120, 3, 153, "TIME: 00:00:00");
	Draw_String(5, 149, 153, "LIFE: 100");
	Draw_String(120, 149, 153, "SKILL:    /100");
	FlipBuffers();
	CopyScreen();
	

	int skillLevel = 1;
	int skillPractice = 0;
	int skillLimit = 100;			// level of skillPractice to reach next skillLevel
	
	Update_SkillMenu(skillLevel);
	
	int fade = 32;
	bool fadeToggle = false;
	
	player* hero = new player(20, 20, 40, 20);
	
	uint16_t prevButtons = 0;
	//uint16_t curButtons = 0;
	
	// Main Loop
	while (true) {
	
	
	
		if (skillPractice >= skillLimit) {
		
			skillPractice = 0;
			skillLimit += 200;
			if (skillLimit > 20000) {			// to prevent overflowing the int
				skillLimit = 20000;			
			}
			skillLevel++;
			
			if (skillLevel > 100) {
				skillLevel = 100;			
			}
			
			Update_SkillMenu(skillLevel);
		}
	
		
		if (fadeToggle) {
			++fade;
			if (fade < 32) {
				Set_Palette (fade);
			}
		}
		
		if (fade > 50) {
			break;
		}
		
		
		FlipBuffers();
		CopyScreen();
		
		// Clear screen
		hero->clear();						// clears hero from the screen
		
		
		

		
		
		if (Button_Pressed(KEY_UP)) {
		hero->move(0, -1);					//move 3pixels up
		skillPractice++;
		}
		
		if (Button_Pressed(KEY_DOWN)) {
		hero->move(0, 1);					//move 3pixels down
		skillPractice++;
		}
		
		if (Button_Pressed(KEY_RIGHT)) {
		hero->move(1, 0);					//move 3pixels right
		skillPractice++;
		}
		
		if (Button_Pressed(KEY_LEFT)) {
		hero->move(-1, 0);					//move 3pixels left
		skillPractice++;
		}
		
		
		hero->draw();						// draws player on the screen
		
		
		// Get the current state of the buttons.
		//curButtons = REG_KEYINPUT;
		
		if (Button_JustPressed(KEY_A, prevButtons)) {		// Press A to switch off lights ;-)
			//fadeToggle = !fadeToggle;	
		}
		
		//prevButtons = curButtons;
		

		WaitVSync();

		
	}	
} // end of Game();

*/

