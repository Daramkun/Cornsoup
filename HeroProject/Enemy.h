#pragma once

#include "Common.h"

class Enemy : public CommonObject
{
public:
	Enemy ();
	~Enemy ();

public:
	void update ();
	void draw ();

public:
	void revive ();
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
