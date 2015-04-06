#pragma once

#include "Common.h"
#include "Enemy.h"

#define MAX_ENEMY_COUNT 32

class EnemyController : public CommonObject
{
public:
	EnemyController ();
	~EnemyController ();

public:
	void update ();
	void draw ();

public:
	Enemy* getEnemy ( int i );

private:
	double lastRevived;
	Enemy enemies [ MAX_ENEMY_COUNT ];
};
