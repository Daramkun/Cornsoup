#include "Cornsoup.h"

int main ( void )
{
	cornsoup_Initialize ();
	cornsoup_FlagDrawFPS ( true );

	int x = 1, y = 1;

	while ( cornsoup_IsRunning () )
	{
		cornsoup_Clear ();

		cornsoup_SetCharacterColor ( ( CornsoupColor ) ( CornsoupColor_BackgroundBlue | CornsoupColor_ForegroundGreen ) );
		cornsoup_DrawChar ( 'a', x, y );
		cornsoup_DrawChar ( 'b', 1, 2 );

		cornsoup_SetCharacterColor ( ( CornsoupColor ) ( CornsoupColor_BackgroundRed ) );
		cornsoup_FillRect ( 10, 10, 10, 10 );

		cornsoup_SetCharacterColor ( ( CornsoupColor ) ( CornsoupColor_ForegroundDefault | CornsoupColor_BackgroundDefault ) );
		cornsoup_DrawChar ( 'c', 2, 2 );

		if ( cornsoup_GetKeyState ( KEY_UP ) )
			y -= 1;
		if ( cornsoup_GetKeyState ( KEY_DOWN ) )
			y += 1;
		if ( cornsoup_GetKeyState ( KEY_LEFT ) )
			x -= 1;
		if ( cornsoup_GetKeyState ( KEY_RIGHT ) )
			x += 1;

		char text [ 128 ];
		sprintf ( text, "%d", ( int ) ( cornsoup_GetTime () * 1000 ) );
		cornsoup_DrawText ( text, 0, 24 );

		cornsoup_Flush ();
	}

	cornsoup_Destroy ();

	return 0;
}