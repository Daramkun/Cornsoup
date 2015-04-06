#pragma once

#include "Common.h"

class Bullet : CommonObject
{
public:
	Bullet ();
	~Bullet ();

public:
	void update ();
	void draw ();

public:
	void reset ( int x, int y );
	void kill ();
	bool isLive ();

public:
	int getX ();
	int getY ();

private:
	int x, y;
	bool isAlive;

	double lastMoved;
};
