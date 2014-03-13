/* 
 * Cascara's Island for GBA 2013
 * Header
 * by Jiri Klic
 * 
 */

#ifndef CASCARA_H
#define CASCARA_H

#include <stdint.h>
#include "gba.h"
#include "gbaextend.h"



// GRAPHIC HEADERS --------------------------------------------------

#define logoTilesLen 16384
extern const unsigned short logoTiles[8192];

#define logoPalLen 512
extern const unsigned short logoPal[256];


extern const uint8_t blank_tile[64];


#define charblock1TilesLen 16384
extern const unsigned short charblock1Tiles[8192];

#define charblock1PalLen 512
extern const unsigned short charblock1Pal[256];


#define spriteTilesLen 16384
extern const unsigned short spriteTiles[8192];

#define spritePalLen 512
extern const unsigned short spritePal[256];


extern const uint16_t seaSB[1024];


extern const uint16_t menuSB[1024];



// GLOBAL VARIABLE --------------------------------------------------




// CLASS PROTOTYPES -------------------------------------------------

// ASSET -------------

class player {
		
		int pointX;			// x coordinates
		int pointY;			// y coordinates
		int width;
		int height;
		int colour;			// replace by sprite in the future

	public:
				
		player(int x, int y, int wdt, int hgt);							// constructor
	
		void move(int dx, int dy);		// move player on the screen
		
		void draw();					// draws player on the screen
		
		void clear();					// clears player from the screen
				
		~player(){}						// destructor

	private:
		player();						// prevents using of general constructor
		
};

// BULLET ------------
/*
class bullet {
		
		int pointX;			// x coordinates
		int pointY;			// y coordinates
		int dx;				// x direction
		int dy;				// y direction

	public:
				
		bullet(int x, int y, int _dx, int _dy);		// constructor
	
		void move();					// move bullet on the screen
		
		void draw();					// draws bullet on the screen
		
		void clear();					// clears bullet from the screen
				
		~bullet(){}						// destructor

	private:
		bullet();						// prevents using of general constructor
		
};
*/



// FUNCTION PROTOTYPES ----------------------------------------------

// FONT --------------

// Draw ASCII character (c) at (x,y) coordinates in colour (colour)
//void Draw_Char(int x, int y, int colour, char c);

// Draw \0-terminated string (s) at position (x,y) in colour (colour)
//void Draw_String(int x, int y, int colour, const char *s);

void DrawText(int x, int y, const char string[]);



// BUTTONS -----------

// check if desired button was pressed
bool Button_Pressed(int KEY);

// check if desired button was just pressed
bool Button_JustPressed(int KEY, uint16_t &oldButtons);


// COLOUR PALETTE ------------

bool Fade_PaletteObj();

bool Rise_PaletteObj(const uint16_t data[256]);

// SLOW TIME -----------------

// wait for MAX/60 seconds
void Slow_Time(int MAX);

// MENU FUNCTION -------------

void Menu();			// The entry point for the menu
void Rules();			// Rules menu
void Draw_Logo();
void Set_Background();

// GAME FUNCTION -------------

// The entry point for the game
void Game();

void Play_Intro();
// ------------------------------------------------------------------

#endif
