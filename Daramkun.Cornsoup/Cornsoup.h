#ifndef __CORNSOUP_H__
#define __CORNSOUP_H__

#ifdef WIN32
#include <Windows.h>
#else
#error "Cornsoup is not support this platform."
#endif

enum CornsoupColor
{
	CornsoupColor_ForegroundDefault =	1,
	CornsoupColor_ForegroundRed =		2,
	CornsoupColor_ForegroundGreen =		4,
	CornsoupColor_ForegroundBlue =		8,

	CornsoupColor_BackgroundDefault =	16,
	CornsoupColor_BackgroundRed =		32,
	CornsoupColor_BackgroundGreen =		64,
	CornsoupColor_BackgroundBlue =		128,
};

#ifdef WIN32
#define KEY_LEFT				VK_LEFT
#define KEY_UP					VK_UP
#define KEY_RIGHT				VK_RIGHT
#define KEY_DOWN				VK_DOWN

#define KEY_ESC					VK_ESCAPE
#define KEY_ENTER				VK_RETURN
#define KEY_SPACEBAR			VK_SPACE
#endif

void cornsoup_Initialize (/* unsigned width = 80, unsigned height = 25 */);
void cornsoup_Destroy ();

double cornsoup_GetTime ();
bool cornsoup_GetKeyState ( char key );

void cornsoup_SetCharacterColor ( CornsoupColor charColor );

void cornsoup_Clear ();
void cornsoup_Flush ();

void cornsoup_DrawChar ( wchar_t ch, unsigned x, unsigned y );
void cornsoup_DrawText ( const wchar_t * text, unsigned x, unsigned y );

void cornsoup_FillRect ( int x, int y, int width, int height );

void cornsoup_FlagDrawFPS ( bool flag );

#endif
