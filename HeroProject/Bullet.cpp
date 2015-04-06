#include "Bullet.h"

Bullet::Bullet () { reset ( 0, 0 ); }

Bullet::~Bullet () { }

void Bullet::update ()
{
	if ( !isAlive ) return;

	double currentTime = cornsoup_GetTime ();
	if ( currentTime - lastMoved > 0.1 )
	{
		--y;
		lastMoved = currentTime;
	}

	if ( y < 0 )
	{
		kill ();
	}
}

void Bullet::draw ()
{
	if ( !isAlive ) return;

	cornsoup_SetCharacterColor ( CornsoupColor_BackgroundDefault, CornsoupColor_ForegroundRed );
	cornsoup_DrawChar ( '!', x, y );
}

void Bullet::reset ( int x, int y )
{
	isAlive = true;
	this->x = x;
	this->y = y;
	lastMoved = cornsoup_GetTime ();
}

void Bullet::kill ()
{
	isAlive = false;
}

bool Bullet::isLive ()
{
	return isAlive;
}

int Bullet::getX () { return x; }
int Bullet::getY () { return y; }