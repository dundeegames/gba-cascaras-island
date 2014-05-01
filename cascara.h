/*
**************************************************************************
**                                                                      **
**                    Cascara's Island for GBA, 2014                    **
**                         Header by Jiri Klic                          **
**                                                                      **
**************************************************************************
*/


#ifndef CASCARA_H
#define CASCARA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "font.h"
#include "gbaextend.h"


// ENUMERATION ------------------------------------------------------

enum entity {player, enemy, bullet};


// STRUCTURES -------------------------------------------------------

struct COORD{	// holds the coordinates of an object
	int X;
	int Y;
};


// CLASS PROTOTYPES -------------------------------------------------

// GAMEPROP (Abstract) -------------

class GameProp {
		
		bool dead = false;
		entity type;
		
		friend bool Hit_Test(GameProp* obj1, GameProp* obj2);
		
	public:
	
		// (ID,coordX,coordY,width(pixels),height(pixels),shape,size,tile)
		GameProp(int id, entity e, int x, int y, int w, int h, int sp, int sz, int tile);	
		
		bool isDead();
		void kill();
		entity getType();
		
		
		virtual void update() = 0;
		
		void render();

		
		~GameProp();

	private:
	
		//GameProp();					// prevents using of general constructor
		
		void move(int dx, int dy);		// move player on the screen
		
	protected:
		
		COORD coord;
		int objNumber;
		int width;
		int height;
};


// PLAYER ------------

class Player : public GameProp{

		int coolDown = 0;

	public:
	
		Player(int id, int x, int y);
	
		void update();

	private:
		
		void shoot();

};

// ENEMY -------------

class Enemy : public GameProp{

		int coolDown;
		
	public:

		Enemy(int id);
	
		void update();

	private:
		
		void shoot();
};


// BULLET ------------

class Bullet : public GameProp{
		
		bool myFriend;					// true if Player's bullet, false if Enemy's

	public:
				
		Bullet(int id, bool f, int x, int y);		// constructor
		bool isFriend();
		void update();
	
		//~bullet(){}					// destructor

	private:
		//bullet();						// prevents using of general constructor
		
};


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


// SCORE ------------

class Score {
		
		int life = 100;
		int skill = 1;
		int score = 0;

	public:
		
		void updateLife(int k);		
		void updateSkill(int k);
		void updateScore(int k);
		
		void render();
		
				

	private:
		
		void drawScore();
		void drawLife();
		void drawSkill();
};

// FUNCTION PROTOTYPES ----------------------------------------------

// FONT --------------

void Draw_Text(int x, int y, int colour, const char string[]);

void Clear_Text(int x, int y, const char string[]);

void Draw_Button(int x, int y, bool select, const char string[]);

void Clear_Button(int x, int y, const char string[]);

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


void Check_Collision();


void Collect_Dead();

// The entry point for the game
void Play_Game();


// GLOBAL VARIABLES -------------------------------------------------

extern int BG3X_offset;				// holds value for reading REG_BG(X)HOFS, which are write only

extern int BG2X_offset;

extern int BG2Y_offset;				// holds value for reading REG_BG(X)VOFS, which are write only
extern int BG1Y_offset;

extern int frameCounter;

extern GameProp* object[NUM_OBJECTS];

extern Score* score;

// GRAPHIC HEADERS --------------------------------------------------

extern const unsigned short logoTiles[8192];

extern const unsigned short logoPal[256];

extern const uint8_t blank_tile[64];

extern const unsigned short charblockTiles[8192];

extern const unsigned short charblockPal[256];

extern const unsigned short spriteTiles[8192];

extern const unsigned short spritePal[256];

extern const uint16_t seaSB[1024];

extern const uint16_t menuSB[1024];

// Easter Egg --------
extern const unsigned short easterEggTiles[8192];

extern const unsigned short easterEggPal[256];

// ------------------------------------------------------------------

#endif
