#pragma once

#include "Common.h"
#include "Bullet.h"

#define MAX_BULLET_COUNT 32

class BulletController : public CommonObject
{
public:
	BulletController ();
	~BulletController ();

public:
	void update ();
	void draw ();

private:
	double lastRevived;
	Bullet bullets [ MAX_BULLET_COUNT ];
};
