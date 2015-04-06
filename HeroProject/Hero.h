#pragma once

#include "Common.h"

class Hero : public CommonObject
{
public:
	Hero ();
	~Hero ();

public:
	void update ();
	void draw ();

	void crashed ();
	void reset ();

public:
	int getX ();
	int getY ();
	int getHP ();

private:
	int x, y;
	int hp;
};