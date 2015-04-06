#include "BulletController.h"
#include "Extern.h"

BulletController::BulletController ()
{
}


BulletController::~BulletController () { }

void BulletController::update ()
{
	Bullet * temp = nullptr;
	for ( int i = 0; i < MAX_BULLET_COUNT; ++i )
	{
		if ( bullets [ i ].isLive () )
		{
			bullets [ i ].update ();

			for ( int j = 0; j < MAX_ENEMY_COUNT; ++j )
			{
				if ( g_EnemyController.getEnemy ( j )->getX () == bullets [ i ].getX () && g_EnemyController.getEnemy ( j )->getY () == bullets [ i ].getY () )
				{
					g_EnemyController.getEnemy ( j )->kill ();
					bullets [ i ].kill ();
				}
			}
		}
		else
		{
			if ( temp == nullptr )
				temp = &bullets [ i ];
		}
	}

	if ( cornsoup_GetKeyState ( ' ' ) && temp != nullptr )
	{
		double now = cornsoup_GetTime ();
		if ( now - lastRevived > 0.1 )
		{
			temp->reset ( g_Hero.getX (), g_Hero.getY () );
			lastRevived = now;
		}
	}
}

void BulletController::draw ()
{
	for ( int i = 0; i < MAX_BULLET_COUNT; ++i )
	{
		if ( bullets [ i ].isLive () )
			bullets [ i ].draw ();
	}
}

void BulletController::reset ()
{
	for ( int i = 0; i < MAX_BULLET_COUNT; ++i )
		bullets [ i ].kill ();
}