#include "Enemy.h"

Enemy::Enemy ()
{
	isAlive = false;
}

Enemy::~Enemy () { }

void Enemy::update ()
{
	if ( !isAlive ) return;

	double currentTime = cornsoup_GetTime ();
	if ( currentTime - lastMoved > 0.3 )
	{
		++y;
		lastMoved = currentTime;
	}

	if ( y > 25 )
	{
		kill ();
	}
}

void Enemy::draw ()
{
	if ( !isAlive ) return;

	cornsoup_SetCharacterColor ( CornsoupColor_BackgroundDefault, CornsoupColor_ForegroundGreen );
	cornsoup_DrawChar ( 'E', x, y );
}

void Enemy::revive ()
{
	isAlive = true;
	x = rand () % 62;
	y = -1;
	lastMoved = cornsoup_GetTime ();
}

void Enemy::kill ()
{
	isAlive = false;
}

bool Enemy::isLive ()
{
	return isAlive;
}

int Enemy::getX () { return x; }
int Enemy::getY () { return y; }