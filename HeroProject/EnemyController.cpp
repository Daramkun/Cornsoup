#include "EnemyController.h"
#include "Extern.h"

EnemyController::EnemyController ()
{
	lastRevived = cornsoup_GetTime ();
}

EnemyController::~EnemyController () { }

void EnemyController::update ()
{
	Enemy * temp = nullptr;
	for ( int i = 0; i < MAX_ENEMY_COUNT; ++i )
	{
		if ( enemies [ i ].isLive () )
		{
			enemies [ i ].update ();

			if ( g_Hero.getX () == enemies [ i ].getX () && g_Hero.getY () == enemies [ i ].getY () )
			{
				g_Hero.crashed ();
				enemies [ i ].kill ();
			}
		}
		else
		{
			if ( temp == nullptr )
				temp = &enemies [ i ];
		}
	}

	if ( temp != nullptr )
	{
		double now = cornsoup_GetTime ();
		if ( now - lastRevived > 0.3 )
		{
			temp->revive ();
			lastRevived = now;
		}
	}
}

void EnemyController::draw ()
{
	for ( int i = 0; i < MAX_ENEMY_COUNT; ++i )
	{
		if ( enemies [ i ].isLive () )
			enemies [ i ].draw ();
	}
}

Enemy* EnemyController::getEnemy ( int i )
{
	return &enemies [ i ];
}