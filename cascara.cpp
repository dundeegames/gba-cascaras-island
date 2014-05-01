#include "cascara.h"			// my header

// CLASS FUNCTIONS =================================================================================

// GAMEPROP -------------------------------------------------------------------

//(ID, type, coordX,coordY,width(pixels),height(pixels),shape,size,tile)
GameProp::GameProp(int id, entity e, int x, int y, int w, int h, int shape, int size, int tile){	

	objNumber = id;
	type = e;
	coord.X = x;			// left
	coord.Y = y;			// top
	width = w;
	height = h;
	
	SetObject(objNumber,
	  ATTR0_SHAPE(shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(coord.Y),
	  ATTR1_SIZE(size) | ATTR1_X(coord.X),
	  ATTR2_ID8(tile));
	
}

bool GameProp::isDead(){
	return dead;
}

void GameProp::kill(){
	dead = true;
}

entity GameProp::getType(){
	return type;
}

void GameProp::render(){
	SetObjectX(objNumber, coord.X);
	SetObjectY(objNumber, coord.Y);
}

GameProp::~GameProp(){											// set to 1x1 empty tile with X,Y out of screen
	SetObject(objNumber,
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(190),
		  ATTR1_SIZE(0) | ATTR1_X(250),
		  ATTR2_ID8(39));
}

// PLAYER ---------------------------------------------------------------------

//(ID, type, coordX,coordY,width(pixels),height(pixels),shape,size,tile)
Player::Player(int id, int x, int y) : 
	GameProp(id, player, x, y, 32, 16, 1, 2, 0){}


void Player::update(){

	if(coolDown > 0){
		coolDown--;
	}

	// Check user input
	if (Key_Pressed(KEY_UP)) {
		if(coord.Y > 24){
			coord.Y--;
		}
	}
	
	if (Key_Pressed(KEY_DOWN)) {
		if(coord.Y < 108){
			coord.Y++;
		}
	}
	
	if (Key_Pressed(KEY_LEFT)) {
		if(coord.X > 8){
			coord.X--;
		}
	}

	if (Key_Pressed(KEY_RIGHT)) {
		if(coord.X < 200){
			coord.X++;
		}
	}
	
	if (Key_Pressed(KEY_A)) {
		shoot();
	}

	if (Key_Pressed(KEY_B)) {
		SetObjectTile(objNumber, ATTR2_ID8(4));
	}
	
}

void Player::shoot(){
	if(coolDown == 0){
		for(int i = 0; i<NUM_OBJECTS; i++){
			if(object[i] == 0){
				object[i] = new Bullet(i, true, (coord.X + width + 4), (coord.Y + 4));
				coolDown = 60;
				break;
			}
		}
	}
}


// ENEMY ----------------------------------------------------------------------

//(ID, type, coordX,coordY,width(pixels),height(pixels),shape,size,tile)
Enemy::Enemy(int id) :	GameProp(id, enemy, 250, (rand()%84)+24, 32, 8, 1, 1, 72){	
	coolDown = rand()%60;
}

void Enemy::update(){

	if(coolDown <= 0){
		if((coord.X > 10) && (coord.X < SCREEN_WIDTH)){
			shoot();
		}
	}
	else{
		coolDown--;
	}

	coord.X--;
	if(coord.X < 0){
		coord.X += 512;
	}
	if((coord.X > 400) && (coord.X < 480)){
		coord.Y = ((rand()%84)+24);
		coord.X = 250;
	}

}

int Enemy::getScore(){
	return score;
}

void Enemy::shoot(){

	for(int i = 0; i<NUM_OBJECTS; i++){
		if(object[i] == 0){
			object[i] = new Bullet(i, false, (coord.X - 4), coord.Y);
			coolDown = 120;
			break;
		}
	}
}

// BULLET ---------------------------------------------------------------------

//(ID, type, coordX,coordY,width(pixels),height(pixels),shape,size,tile)
Bullet::Bullet(int id, bool f, int x, int y) :	GameProp(id, enemy, x, y, 2, 2, 0, 0, 124){		
	myFriend = f;	
}

void Bullet::update(){

	if(isDead() == false){
		if(myFriend){
			coord.X += 4;

			if(coord.X > SCREEN_WIDTH){
				kill();
			}
		}
		else{
			coord.X -= 2;
			if(coord.X < 0){
				coord.X = 250;		// get of the screen
				coord.Y = 180;
				kill();
			}
		}
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
	Draw_Text(15, 1, 0, buffer);
}


// SCORE ----------------------------------------------------------------------

void Score::updateLife(int k){
	life += k;
}		
void Score::updateSkill(int k){
	skill += k;
}
void Score::updateScore(int k){
	score += k;
}

void Score::render(){
	drawScore();
	drawLife();
	drawSkill();
}

void Score::drawScore(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "SCORE:%5d", score);
	
	Draw_Text(1, 1, 0, buffer);
}


void Score::drawLife(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "LIFE:%4d", life);

	Draw_Text(1, 19, 0, buffer);
}


void Score::drawSkill(){

	char buffer[20];
	snprintf(buffer, sizeof buffer, "SKILL:%4d/100", skill);

	Draw_Text(15, 19, 0, buffer);
}


// TEXT ============================================================================================

// 	values for colour (0-15):
//	0-white, 1-yellow, 2-green, 3-red, 4-cyan, 5-blue, 6-pink,
//	14-black, 15-brown
void Draw_Text(int x, int y, int colour, const char string[]){

	int i = 0;
	
	while(string[i] != '\0'){
		SetTile(31, (x+i), y, string[i] | (colour << 12));
		i++;
	}
}

// ---------------------------------------------------------

void Clear_Text(int x, int y, const char string[]){

	int i = 0;
	
	while(string[i] != '\0'){
		SetTile(31, (x+i), y, 0);
		i++;
	}
}

// ---------------------------------------------------------

void Draw_Button(int x, int y, bool select, const char string[]){
	
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

void Clear_Button(int x, int y, const char string[]){
	
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
				
				BG1Y_offset = 4;				// reset BG1
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
				Draw_Text(9, 7, 15, "Choose from");
				Draw_Text(6, 9, 15, "following options");
				
				if (startSelect) {
					Draw_Button(8, 13, true, "START");
					Draw_Button(17, 13, false, "ABOUT");
				}
				else {
					Draw_Button(8, 13, false, "START");
					Draw_Button(17, 13, true, "ABOUT");
				}

				// Check user input
				if (Key_Pressed(KEY_RIGHT) && startSelect){
					 startSelect = !startSelect;
				}
				
				else if (Key_Pressed(KEY_LEFT) && !startSelect){
					startSelect = !startSelect;
				}
			
				if (Key_Pressed(KEY_START)){
					Clear_Text(9, 7, "Choose from");
					Clear_Text(6, 9, "following options");
				
					Clear_Button(8, 13, "START");
					Clear_Button(17, 13, "ABOUT");
					
					if(startSelect){
						logoStage = end;
					}
					else{
						logoStage = about;
					}
				}			
				break;
				
			case about:
				Draw_Text(6, 4, 5, "Created by Jiri Klic");
				Draw_Text(6, 6, 5, "@ Abertay, April 2014");
				Draw_Text(6, 10, 15, "Press SELECT to return");
				
				Draw_Button(12, 13, false, "SELECT");
				
				// Check user input
				if (Key_Pressed(KEY_SELECT)){
					Draw_Button(12, 13, true, "SELECT");
					Slow_Time(12);									// wait for MAX/60 seconds
				
					Clear_Text(6, 4, "Created by Jiri Klic");
					Clear_Text(6, 6, "@ Abertay, April 2014");
					Clear_Text(6, 10, "Press SELECT to return");
					
					Clear_Button(12, 13, "SELECT");
					
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

// Collision Detection: returns true if objects collide
bool Hit_Test(GameProp* obj1, GameProp* obj2){
	if ((obj1->coord.X + obj1->width) < (obj2->coord.X)) return false;
	if ((obj2->coord.X + obj2->width) < (obj1->coord.X)) return false;
	if ((obj1->coord.Y + obj1->height) < (obj2->coord.Y)) return false;
	if ((obj2->coord.Y + obj2->height) < (obj1->coord.Y)) return false;
	return true;
}

// ----------------------------------------------------------------------------

void Check_Collision(){

	
	// Collision test against Player ---------
	Player* player = (Player*)object[0];				// (DerivedClass*)instance;
	
	for(int i=1; i<NUM_OBJECTS; i++){
		if(Hit_Test(object[0], object[i])){
			

			object[i]->kill();						
		}		
	}

	for(int i = 0; i < (NUM_OBJECTS-1); i++){
		for(int j = i+1; j < NUM_OBJECTS; j++){
			if(Hit_Test(object[i], object[j])){
				if(i == 0){
					//object[i]->updateScore(object[j]->getScore());
					//object[j]->kill();						
				}
			}			
		}		
	}

}


// ----------------------------------------------------------------------------

void Collect_Dead(){

	for(int i = 0; i < NUM_OBJECTS; i++){
		if(object[i]->isDead()){
			delete object[i];
			object[i] = 0;
		}
	}
}


// ----------------------------------------------------------------------------

void Play_Game(){

	srand((unsigned)frameCounter);		// seed rand()

/*
// PSEUDOCODE ------------------

IF(object[i] != 0){
	object[i].update();
}
ELSE {CONTINUE}

IF(object[i].isDead()){
	delete object[i];
	object[i] = 0;
}

// -----------------------------
*/
	Time* time = new Time();
	Score* score = new Score();
	
	for(int i = 0; i<NUM_OBJECTS; i++){		// initialize all object addresses to 0
		object[i] = 0;
	}

	object[0] = new Player(0,8,32);
	object[1] = new Enemy(1);
	
	time->setTime(0, 0, 99);				//test values
	time->drawTime();
	score->render();

	REG_BG0VOFS = 4;	


	while(true){
	
		frameCounter++;
		
		// UPDATE ------------------
		time->update();

		for(int i = 0; i < NUM_OBJECTS; i++){
			if(object[i] != 0){
				object[i]->update();
			}
		}

		
		// COLLISION ---------------
		Check_Collision();
		
		
		// GARBAGE COLLECTION ------
		Collect_Dead();
		
		
		// RENDER ------------------
		for(int i = 0; i < NUM_OBJECTS; i++){
			if(object[i] != 0){
				object[i]->render();
			}
		}
		
		time->drawTime();
		score->render();

		
		// SYSTEM ------------------
		WaitVSync();
		UpdateObjects();
		
		if (!(frameCounter%3)){
			BG3X_offset += 1;
			REG_BG3HOFS = BG3X_offset;
		}
		
	} // end of while ---

	
	// release all memory ---------------
	delete time;
	delete score;
	
	for(int i = 0; i < NUM_OBJECTS; i++){
		if(object[i] != 0){
			delete object[i];
			object[i] = 0;
		}
	}

}