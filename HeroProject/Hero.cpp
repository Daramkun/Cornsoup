#include "Hero.h"

Hero::Hero ()
{
	reset ();
}

Hero::~Hero () { }

void Hero::update ()
{
	if ( cornsoup_GetKeyState ( KEY_UP ) ) { --y; if ( y < 0 ) y = 0; }
	if ( cornsoup_GetKeyState ( KEY_DOWN ) ) { ++y; if ( y >= 25 ) y = 24; }
	if ( cornsoup_GetKeyState ( KEY_LEFT ) ) { --x; if ( x < 0 ) x = 0; }
	if ( cornsoup_GetKeyState ( KEY_RIGHT ) ) { ++x; if ( x >= 62 ) x = 61; }

	cornsoup_PrintDebug ( "x: %d y: %d\n", x, y );
}

void Hero::draw ()
{
	cornsoup_SetCharacterColor ( CornsoupColor_BackgroundDefault, CornsoupColor_ForegroundDefault );
	cornsoup_DrawChar ( TEXT ( '^' ), x, y - 1 );
	cornsoup_DrawChar ( TEXT ( 'H' ), x, y );
	cornsoup_DrawChar ( TEXT ( 'A' ), x - 1, y );
	cornsoup_DrawChar ( TEXT ( 'A' ), x + 1, y );
}

void Hero::crashed ()
{
	--hp;
}

void Hero::reset ()
{
	x = 31; y = 20;
	hp = 5;
}

int Hero::getX () { return x; }
int Hero::getY () { return y; }

int Hero::getHP () { return hp; }