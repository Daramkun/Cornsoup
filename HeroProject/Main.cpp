#include "Common.h"

#include "Hero.h"
#include "EnemyController.h"
#include "BulletController.h"

Hero g_Hero;
EnemyController g_EnemyController;
BulletController g_BulletController;

int main ( void )
{
	cornsoup_Initialize ();
	cornsoup_FlagFixedFPS ( true );
	cornsoup_FlagDrawFPS ( true );
	cornsoup_SetTitle ( "Hero Project" );

	while ( cornsoup_IsRunning () )
	{
		cornsoup_Clear ();

		g_Hero.update ();
		g_EnemyController.update ();
		g_BulletController.update ();

		g_Hero.draw ();
		g_EnemyController.draw ();
		g_BulletController.draw ();

		cornsoup_SetCharacterColor ( CornsoupColor_BackgroundBlue );
		cornsoup_FillRect ( 62, 0, 18, 25 );

		cornsoup_Flush ();
	}

	cornsoup_Destroy ();

	return 0;
}