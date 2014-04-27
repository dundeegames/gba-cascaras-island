/* 
 * Cascara's Island for GBA 2013
 * Header
 * by Jiri Klic
 * 
 */

#ifndef CASCARA_H
#define CASCARA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "font.h"
#include "gbaextend.h"



// GRAPHIC HEADERS --------------------------------------------------

#define logoTilesLen 16384
extern const unsigned short logoTiles[8192];

#define logoPalLen 512
extern const unsigned short logoPal[256];


extern const uint8_t blank_tile[64];

#define charblock2TilesLen 16384
extern const unsigned short charblockTiles[8192];

#define charblock2PalLen 512
extern const unsigned short charblockPal[256];

#define spriteTilesLen 16384
extern const unsigned short spriteTiles[8192];

#define spritePalLen 512
extern const unsigned short spritePal[256];


extern const uint16_t seaSB[1024];


extern const uint16_t menuSB[1024];

// Easter Egg --------
#define easterEggTilesLen 16384
extern const unsigned short easterEggTiles[8192];

#define easterEggPalLen 512
extern const unsigned short easterEggPal[256];


// GLOBAL VARIABLE --------------------------------------------------

extern int BG3X_offset;				// holds value for reading REG_BG(X)HOFS, which are write only

extern int BG2X_offset;

extern int BG2Y_offset;				// holds value for reading REG_BG(X)VOFS, which are write only
extern int BG1Y_offset;

extern int frameCounter;

// CLASS PROTOTYPES -------------------------------------------------

// GAMEPROP (Abstract) -------------

class GameProp {
		
		bool dead = false;
		
		friend bool Hit_Test(GameProp* obj1, GameProp* obj2);
		
	public:
	
		// (ID,coordX,coordY,width(pixels),height(pixels),shape,size,tile)
		GameProp(int id, int x, int y, int w, int h, int sp, int sz, int tile);	
		
		bool isDead();
		
		virtual void update() = 0;
		
		void render();

		
		~GameProp(){}

	private:
	
		//GameProp();						// prevents using of general constructor
		
		void move(int dx, int dy);		// move player on the screen
		
	protected:
		
		int objNumber;
		int coordX;			// left
		int coordY;			// top
		int width;
		int height;
};


// PLAYER ------------

class Player : public GameProp{

		int life = 100;
		int skill = 1;
		int score = 9999;

	public:
	
		Player(int id, int x, int y);
	
		void update();
		
		//void drawStats();

	private:
		
		void drawScore();
		void drawLife();
		void drawSkill();
};

// ENEMY -------------

class Enemy : public GameProp{

		int score = 20;

	public:
	
		Enemy(int id, int x, int y);
	
		void update();


	private:

};





// BULLET ------------
/*
class Bullet {
		
		int dx;				// x direction
		int dy;				// y direction
		bool friend;

	public:
				
		bullet(int x, int y, int _dx, int _dy);		// constructor
		
		bool isFriend();
	
		~bullet(){}						// destructor

	private:
		bullet();						// prevents using of general constructor
		
};
*/

// TIME -------------

class Time {
		
		int frames = 0;			// 60/second
		int seconds = 0;
		int minutes = 0;
		
		char buffer[20];

	public:
	
		void setTime(int f, int s, int m);			// initialize time
		
		void update();
		
		void drawTime();

	private:

};

// FUNCTION PROTOTYPES ----------------------------------------------

// FONT --------------

void DrawText(int x, int y, int colour, const char string[]);

void ClearText(int x, int y, const char string[]);

void DrawButton(int x, int y, bool select, const char string[]);

void ClearButton(int x, int y, const char string[]);

// KEYS -----------

// check if desired button was pressed
bool Key_Pressed(int KEY);

// check if desired button was just pressed
bool Key_JustPressed(int KEY, uint16_t &oldButtons);


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

void Play_Intro();

// The entry point for the game
void Play_Game();

// ------------------------------------------------------------------

#endif
