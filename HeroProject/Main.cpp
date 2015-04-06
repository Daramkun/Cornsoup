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

		if ( g_Hero.getHP () != 0 )
		{
			g_Hero.update ();
			g_EnemyController.update ();
			g_BulletController.update ();
		}
		else
		{
			if ( cornsoup_GetKeyState ( ' ' ) )
			{
				g_Hero.reset ();
				g_EnemyController.reset ();
				g_BulletController.reset ();
			}
		}

		g_Hero.draw ();
		g_EnemyController.draw ();
		g_BulletController.draw ();

		cornsoup_SetCharacterColor ( CornsoupColor_BackgroundBlue );
		cornsoup_FillRect ( 62, 0, 18, 25 );

		cornsoup_SetCharacterColor ( CornsoupColor_BackgroundBlue, CornsoupColor_ForegroundDefault );
		cornsoup_DrawText ( "HP", 63, 1 );

		cornsoup_SetCharacterColor ( CornsoupColor_BackgroundDefault );
		cornsoup_FillRect ( 63, 3, 16, 1 );

		cornsoup_SetCharacterColor ( CornsoupColor_BackgroundRed );
		cornsoup_FillRect ( 63, 3, 16 * ( g_Hero.getHP () / 5.0f ), 1 );

		if ( g_Hero.getHP () == 0 )
		{
			cornsoup_SetCharacterColor ( CornsoupColor_BackgroundDefault, CornsoupColor_ForegroundDefault );
			cornsoup_DrawText ( "GAME OVER", 80 / 2 - 4, 25 / 2 );
			cornsoup_DrawText ( "press space bar to continue.", 80 / 2 - strlen ( "press space bar to continue." ) / 2, 25 / 2 + 2 );
		}

		cornsoup_Flush ();
	}

	cornsoup_Destroy ();

	return 0;
}