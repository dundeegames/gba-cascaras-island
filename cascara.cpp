#include "cascara.h"			// my header

// CLASS FUNCTIONS =================================================================================

// GAMEPROP -------------------------------------------------------------------

GameProp::GameProp(int id, int x, int y, int w, int h, int shape, int size, int tile){	//(ID,coordX,coordY,width(pixels),height(pixels),shape,size,tile)

	objNumber = id;
	coordX = x;			// left
	coordY = y;			// top
	width = w;
	height = h;
	
	SetObject(objNumber,
	  ATTR0_SHAPE(shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(coordY),
	  ATTR1_SIZE(size) | ATTR1_X(coordX),
	  ATTR2_ID8(tile));
	
}

bool GameProp::isDead(){
	return dead;
}

void GameProp::render(){
	SetObjectX(objNumber, coordX);
	SetObjectY(objNumber, coordY);
}
// PLAYER ---------------------------------------------------------------------

Player::Player(int id, int x, int y) : GameProp(id, x, y, 32, 16, 1, 2, 0){
	drawScore();
	drawLife();
	drawSkill();	
}


void Player::update(){

	// Check user input
	if (Key_Pressed(KEY_UP)) {
		if(coordY > 24){
			coordY--;
		}
	}
	
	if (Key_Pressed(KEY_DOWN)) {
		if(coordY < 108){
			coordY++;
		}
	}
	
	if (Key_Pressed(KEY_LEFT)) {
		if(coordX > 8){
			coordX--;
		}
	}

	if (Key_Pressed(KEY_RIGHT)) {
		if(coordX < 200){
			coordX++;
		}
	}
	
	if (Key_Pressed(KEY_A)) {
		SetObjectTile(objNumber, ATTR2_ID8(4));
	}

	if (Key_Pressed(KEY_B)) {
		SetObjectTile(objNumber, ATTR2_ID8(0));
	}
	
}


void Player::drawScore(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "SCORE:%5d", score);
	
	DrawText(1, 1, 0, buffer);
}


void Player::drawLife(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "LIFE:%4d", life);

	DrawText(1, 19, 0, buffer);
}


void Player::drawSkill(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "SKILL:%4d/100", skill);

	DrawText(15, 19, 0, buffer);
}


// ENEMY ----------------------------------------------------------------------

Enemy::Enemy(int id, int x, int y) :
	GameProp(id, x, y, 32, 8, 1, 1, 72){}


void Enemy::update(){

	coordX--;
	if(coordX < 0){
		coordX += 512;
	}
	if((coordX > 400) && (coordX < 480)){
		coordY = ((rand()%84)+24);
		coordX = 250;
	}

}




// TIME -----------------------------------------------------------------------

void Time::setTime(int f, int s, int m){		// initialize time
	frames = f;									// 60/second
	seconds = s;
	minutes = m;
}

void Time::update(){

	frames++;									// 60/second
	
	if (frames == 60){
		frames = 0;
		seconds++;
	
		if (seconds == 60){
			seconds = 0;
			minutes++;
		}
	}
}

void Time::drawTime(){
	if(minutes < 100){
		snprintf(buffer, sizeof buffer, "TIME: %02d:%02d:%02d", minutes, seconds, frames);
	}
	else{
		snprintf(buffer, sizeof buffer, "TIME:%02d:%02d:%02d", minutes, seconds, frames);
	}
	DrawText(15, 1, 0, buffer);
}



// TEXT ============================================================================================

/*
// Draw \0-terminated string s at position (x, y) in colour colour.
void DrawString8(int x, int y, int colour, const char *s) {
	while (*s != '\0') {
		DrawChar8(x, y, colour, *s);
		x += 8;
		s++;
	}
}

// Then you can use it something like this...
void SomeOtherFunction() {
	int score = 42;

	DrawString8(10, 10, 1, "Hello world!");
	
	// To print variables, use snprintf to produce a string, then print the string.
	// (Look at the manual for "printf" to see how the % directives work.)
	char buf[40];
	snprintf(buf, sizeof buf, "Score is %03d", score);
	DrawString8(10, 30, 1, buf);
*/

// ---------------------------------------------------------

// 	values for colour (0-15):
//	0-white, 1-yellow, 2-green, 3-red, 4-cyan, 5-blue, 6-pink,
//	14-black, 15-brown
void DrawText(int x, int y, int colour, const char string[]){

	int i = 0;
	
	while(string[i] != '\0'){
		SetTile(31, (x+i), y, string[i] | (colour << 12));
		i++;
	}
}

// ---------------------------------------------------------

void ClearText(int x, int y, const char string[]){

	int i = 0;
	
	while(string[i] != '\0'){
		SetTile(31, (x+i), y, 0);
		i++;
	}
}

// ---------------------------------------------------------

void DrawButton(int x, int y, bool select, const char string[]){
	
	int i = 0;
	
	if(select){
		SetTile(30, x-1, y, 1);
		SetTile(30, x-1, y+1, 17);
	}
	else{
		SetTile(30, x-1, y, 222);
		SetTile(30, x-1, y+1, 238);
	}
	
	while(string[i] != '\0'){
				
		if(select){
			SetTile(31, (x+i), y, string[i] | (1 << 12));
			SetTile(30, (x+i), y, 2);
			SetTile(30, (x+i), y+1, 18);
		}
		else{
			SetTile(31, (x+i), y, string[i]);
			SetTile(30, (x+i), y, 254);
			SetTile(30, (x+i), y+1, 255);
		}
		i++;
	}
	
	if(select){
		SetTile(30, (x+i), y, 3);
		SetTile(30, (x+i), y+1, 19);
	}
	else{
		SetTile(30, (x+i), y, 223);
		SetTile(30, (x+i), y+1, 239);
	}
}

// ---------------------------------------------------------

void ClearButton(int x, int y, const char string[]){
	
	int i = 0;
	
	SetTile(30, x-1, y, 0);
	SetTile(30, x-1, y+1, 0);

	while(string[i] != '\0'){

		SetTile(31, (x+i), y, 0);
		SetTile(30, (x+i), y, 0);
		SetTile(30, (x+i), y+1, 0);

		i++;
	}

	SetTile(30, (x+i), y, 0);
	SetTile(30, (x+i), y+1, 0);
}

// KEYS =========================================================================================

bool Key_Pressed(int KEY) { // check if desired button was pressed
	
	bool x = false;
	
	if ((REG_KEYINPUT & KEY) == 0) {
		x = true;
	}
	
	
	return x;
}	// end Button_Pressed

// ----------------------------------------------------------------------------

bool Key_JustPressed(int KEY, uint16_t &oldButtons) {	// check if desired button was just pressed
	
	
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
	REG_BG2VOFS = BG2Y_offset;
	
	// Set background 1 options.
	REG_BG1CNT = BG_CBB(1) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;			// menu layer
	REG_BG1HOFS = 0;
	REG_BG1VOFS = BG1Y_offset;
	
	// Set background 0 options.
	//REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_8BPP | BG_REG_32x32;			// text layer
	REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;			// text layer
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	
	// ----------------------------------------------------------------------------

	//LoadPaletteBG(charblock1Pal);
	LoadPaletteBG(charblockPal);

	//LoadTileData(1, 0, charblock1Tiles, sizeof charblock1Tiles);
	LoadTileData(1, 0, charblockTiles, sizeof charblockTiles);	
	LoadTile8(1, 0, blank_tile);			// Load blank_tile into charblock - 1 / tile - 0

	/*
	// Bug fix the artefact pixels
	FixTile8(1, 160);
	FixTile8(1, 161);
	FixTile8(1, 170);
	FixTile8(1, 172);
	*/
	
	// initiate backgrounds -------------------------------------------------------
	
	LoadScreenblock(28, seaSB);
	
	for (int y = 0; y < 32; ++y){			// Ask about efficiency! Is is OK if it is jumping each loop to 3 different places in memory? Or should I rather create function and execute each SB separately?

		for (int x = 0; x < 32; ++x){
			SetTile(29, x, y, 0);			// Load blank tiles into SB 29
			SetTile(30, x, y, 0);			// Load blank tiles into SB 30
			SetTile(31, x, y, 0);			// Load blank tiles into SB 31

		}
	}	
	
	
	//LoadScreenblock(30, menuSB);
	
	
	// set upper menu --------------------------------
	for (int y = 0; y < 3; ++y) {
		int tileNum;
		for (int x = 0; x < 32; ++x) {
			tileNum = menuSB[(y*32)+x] | SE_VFLIP;
			SetTile(30, x, y, tileNum);
			//OrTile(30, x, y, SE_VFLIP);		// amended function from gbaextend.h
		}
	}
	
	// set bottom menu -------------------------------
	for (int y = 18; y < 21; ++y) {
		for (int x = 0; x < 32; ++x) {
			SetTile(29, x, y, menuSB[(y*32)+x]);
		}
	}
	



} // end of Set_Background


// ----------------------------------------------------------------------------


void Play_Intro(){			// Play logo and sets menu

	bool inLoop = true;
	bool startSelect = true;	// draw first screen with START selected
	
	int pauseCounter = 0;
	
	int planeX = 480;			// holds Xcoord for fake plane
	
	enum stage {skip, start, studioRise, Pause, studioFade, gameRise, gameFade, menuSlide, planeSlide, buttons, about, end};
	stage logoStage = start;
	
	LoadTileData(4, 0, logoTiles, sizeof logoTiles);
	
	ClearObjects();
	
	for (int i = 0; i < 256; i++) {
		SetPaletteObj(i, 0x6F37);
	}

	
	while (inLoop){

		frameCounter++;

		if (Key_Pressed(KEY_START)){
			switch(logoStage){
				case buttons:	break;
				case about:		break;
				case end:		break;
				default:	logoStage = skip;	break;
			}				
		}

		switch(logoStage){

			case skip:
				ClearObjects();
				
				LoadPaletteObj(spritePal);
				LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
				
				//-------------------------------
				for (int y = 0; y < 32; ++y){
					for (int x = 0; x < 32; ++x){
						SetTile(29, x, y, 0);			// Set SB 29 to 0
					}
				}	
				
				LoadScreenblock(30, menuSB);

				// set upper menu --------------------------------
				for (int y = 0; y < 3; ++y) {
					for (int x = 0; x < 32; ++x) {
						OrTile(30, x, y, SE_VFLIP);		// amended function from gbaextend.h
					}
				}
				
				BG1Y_offset = 4;				// rset BG1
				REG_BG1VOFS = BG1Y_offset;
				
				BG2Y_offset = 0;				// reset BG2
				REG_BG2VOFS = BG2Y_offset;
				
				LoadCompressedText();
				
				logoStage = end;
				
				break;

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
						logoStage = Pause;
					}				
				}
				break;
				
			case Pause:
				if(frameCounter > 120){
					switch(pauseCounter){
						case 0:	logoStage = studioFade;	break;
						case 1:	logoStage = gameRise;	break;
						case 2:	logoStage = gameFade;	break;
						case 3:	logoStage = studioFade;	break;		// should never activate (ToDo: evolve into proper Error test)			
					}
					pauseCounter++;									
				}
				break;
				
			case studioFade:
				if(!(frameCounter%5)){
					if (Fade_PaletteObj()){

						SetObjectTile(0, ATTR2_ID8(128));
						SetObjectTile(1, ATTR2_ID8(136));

						frameCounter = 0;
						logoStage = Pause;
					}				
				}
				break;
				
			case gameRise:
				if(!(frameCounter%7)){
					if (Rise_PaletteObj(logoPal)){
						frameCounter = 0;
						logoStage = Pause;
					}
				}
				break;
				
			case gameFade:
				if(!(frameCounter%5)){
					if (Fade_PaletteObj()){
						frameCounter = 0;
						logoStage = menuSlide;
					}				
				}
				break;
				
			case menuSlide:
				if(!(frameCounter%3)){
					if(BG2Y_offset < 4){
						BG2Y_offset++;					// slide bottom menu up
						REG_BG2VOFS = BG2Y_offset;					
					}
					if(BG1Y_offset > 4){
						BG1Y_offset--;					// slide top menu down
						REG_BG1VOFS = BG1Y_offset;					
					}

					if ((BG1Y_offset == 4) && (BG2Y_offset == 4)){
					
						// Move bottom menu from SB29 to SB30-------------------------------
						for (int y = 18; y < 21; ++y) {
							for (int x = 0; x < 32; ++x) {
								MoveTile(29, x, y, 30, x, y);
							}
						}
						
						BG2Y_offset = 0;				// reset BG2
						REG_BG2VOFS = BG2Y_offset;
						
						// Change objects to (fake) play characters and update Charbolock and Palette
						SetObject(0,
						  ATTR0_SHAPE(1) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
						  ATTR1_SIZE(2) | ATTR1_X(planeX),
						  ATTR2_ID8(0));
						  
						SetObject(1,
						  ATTR0_SHAPE(1) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(32),
						  ATTR1_SIZE(1) | ATTR1_X(250),
						  ATTR2_ID8(72));
						  
						LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);

						LoadPaletteObj(spritePal);

						// -----------------------------------------------------------------
						
						logoStage = planeSlide;
					}				
				}				
				break;
				
			case planeSlide:
				if(!(frameCounter%3)){
					if(planeX < 520){
						planeX++;
						SetObjectX(0, planeX);
					}
					else{
					
						LoadCompressedText();

						logoStage = buttons;
					}					
				}
				break;
				
			case buttons:
				DrawText(9, 7, 15, "Choose from");
				DrawText(6, 9, 15, "following options");
				
				if (startSelect) {
					DrawButton(8, 13, true, "START");
					DrawButton(17, 13, false, "ABOUT");
				}
				else {
					DrawButton(8, 13, false, "START");
					DrawButton(17, 13, true, "ABOUT");
				}

				// Check user input
				if (Key_Pressed(KEY_RIGHT) && startSelect){
					 startSelect = !startSelect;
				}
				
				else if (Key_Pressed(KEY_LEFT) && !startSelect){
					startSelect = !startSelect;
				}
			
				if (Key_Pressed(KEY_START)){
					ClearText(9, 7, "Choose from");
					ClearText(6, 9, "following options");
				
					ClearButton(8, 13, "START");
					ClearButton(17, 13, "ABOUT");
					
					if(startSelect){
						logoStage = end;
					}
					else{
						logoStage = about;
					}
				}			
				break;
				
			case about:
				DrawText(6, 4, 5, "Created by Jiri Klic");
				DrawText(6, 6, 5, "@ Abertay, April 2014");
				DrawText(6, 10, 15, "Press SELECT to return");
				
				DrawButton(12, 13, false, "SELECT");
				
				// Check user input
				if (Key_Pressed(KEY_SELECT)){
					DrawButton(12, 13, true, "SELECT");
					Slow_Time(12);									// wait for MAX/60 seconds
				
					ClearText(6, 4, "Created by Jiri Klic");
					ClearText(6, 6, "@ Abertay, April 2014");
					ClearText(6, 10, "Press SELECT to return");
					
					ClearButton(12, 13, "SELECT");
					
					startSelect = true;
					
					logoStage = buttons;
				}
				break;
				
			case end:
				inLoop = false;
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


// GAME ============================================================================================

// ----------------------------------------------------------------------------


// Collision Detection: returns true if objects collide
bool Hit_Test(GameProp* obj1, GameProp* obj2){
	if ((obj1->coordX + obj1->width) < (obj2->coordX)) return false;
	if ((obj2->coordX + obj2->width) < (obj1->coordX)) return false;
	if ((obj1->coordY + obj1->height) < (obj2->coordY)) return false;
	if ((obj2->coordY + obj2->height) < (obj1->coordY)) return false;
	return true;
}


// USE WITH SORT ALGORITHM ON object[128]


// ----------------------------------------------------------------------------

void Play_Game(){

	srand((unsigned)frameCounter);

/*
// PSEUDOCODE ------------------

GameProp* object[128];

for(int i = 0; i<128; i++){
	object[i] = 0;
}

IF(object[i] != 0){
	object[i].updae();
}
ELSE {CONTINUE}

IF(object[i].isDead()){
	delete object[i];
	object[i] = 0;
}

// -----------------------------
*/
	Time* time = new Time();
	Player* player = new Player(0,8,32);
	Enemy* enemy = new Enemy(1,250,32);

	
	time->setTime(0, 0, 99);			//test values
	time->drawTime();

	
	REG_BG0VOFS = 4;	


	while(true){
	
		frameCounter++;
		
		// UPDATE ------------------
		time->update();
		player->update();
		enemy->update();

		
		// COLLISION ---------------
		
		
		
		
		// RENDER ------------------
		player->render();
		enemy->render();
		time->drawTime();

		
		// SYSTEM ------------------
		WaitVSync();
		UpdateObjects();
		
		if (!(frameCounter%3)){
			BG3X_offset += 1;
			REG_BG3HOFS = BG3X_offset;
		}
		
	}

	delete time;
	delete player;
	delete enemy;
}