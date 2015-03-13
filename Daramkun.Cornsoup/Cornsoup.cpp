#include "Cornsoup.h"

unsigned g_width;
unsigned g_height;

bool g_flagDrawFPS;
double g_lastTime, g_elapsTime;
int g_frameCount;
double g_fps;

#ifdef WIN32
HANDLE g_screenBuffer;
WORD g_charColor;

CHAR_INFO * g_charBuffer;
#endif

void cornsoup_Initialize (/* unsigned width, unsigned height */)
{
	g_width = 80;//width;
	g_height = 25;//height;
#ifdef WIN32
	g_charBuffer = new CHAR_INFO [ g_width * g_height ];
	memset ( g_charBuffer, 0, sizeof ( CHAR_INFO ) * g_width * g_height );

	g_screenBuffer = CreateConsoleScreenBuffer ( GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr );

	if ( !SetConsoleActiveScreenBuffer ( g_screenBuffer ) )
		exit ( 1 );

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo ( g_screenBuffer, &cursorInfo );
#endif

	g_flagDrawFPS = false;
	g_lastTime = cornsoup_GetTime ();

	cornsoup_SetCharacterColor ( ( CornsoupColor ) ( CornsoupColor_ForegroundDefault | CornsoupColor_BackgroundDefault ) );
}

void cornsoup_Destroy ()
{
#ifdef WIN32
	CloseHandle ( g_screenBuffer );

	delete [] g_charBuffer;
#endif
}

double cornsoup_GetTime ()
{
#ifdef WIN32
	LARGE_INTEGER proc_freq;
	QueryPerformanceFrequency ( &proc_freq );

	LARGE_INTEGER pc;
	QueryPerformanceCounter ( &pc );

	return pc.QuadPart / ( double ) proc_freq.QuadPart;
#endif
}

bool cornsoup_GetKeyState ( char key )
{
#ifdef WIN32
	return ( GetAsyncKeyState ( key ) & 0x80000000 ) ? true : false;
#endif
}

void cornsoup_SetCharacterColor ( CornsoupColor charColor )
{
#ifdef WIN32
	g_charColor = 0;
	if ( charColor & CornsoupColor_ForegroundDefault )
		g_charColor |= FOREGROUND_INTENSITY;
	else if ( charColor & CornsoupColor_ForegroundRed )
		g_charColor |= FOREGROUND_RED;
	else if ( charColor & CornsoupColor_ForegroundGreen )
		g_charColor |= FOREGROUND_GREEN;
	else if ( charColor & CornsoupColor_ForegroundBlue )
		g_charColor |= FOREGROUND_BLUE;

	if ( charColor & CornsoupColor_BackgroundDefault )
		g_charColor |= 0;
	else if ( charColor & CornsoupColor_BackgroundRed )
		g_charColor |= BACKGROUND_RED;
	else if ( charColor & CornsoupColor_BackgroundGreen )
		g_charColor |= BACKGROUND_GREEN;
	else if ( charColor & CornsoupColor_BackgroundBlue )
		g_charColor |= BACKGROUND_BLUE;
#endif
}

void cornsoup_Clear ()
{
#ifdef WIN32
	memset ( g_charBuffer, 0, sizeof ( CHAR_INFO ) * g_width * g_height );
#endif
}

void cornsoup_Flush ()
{
	if ( g_flagDrawFPS )
	{
		++g_frameCount;
		double currentTime = cornsoup_GetTime (); 
		g_elapsTime += ( currentTime - g_lastTime );
		g_lastTime = currentTime;

		if ( g_elapsTime >= 1 )
		{
			g_fps = g_frameCount + ( g_frameCount * ( g_elapsTime - 1 ) );
			g_frameCount = 0;
			g_elapsTime -= 1;
		}

		wchar_t fpsText [ 32 ];
		wsprintf ( fpsText, TEXT ( "FPS: %d" ), ( int ) g_fps );
		cornsoup_SetCharacterColor ( ( CornsoupColor ) ( CornsoupColor_ForegroundGreen | CornsoupColor_BackgroundDefault ) );
		cornsoup_DrawText ( fpsText, 0, 0 );
	}

#ifdef WIN32
	COORD bufferSize = { g_width, g_height }, coord = { 0, 0 };
	SMALL_RECT region = { 0, 0, 80, 24 };

	if ( !WriteConsoleOutput ( g_screenBuffer, g_charBuffer, bufferSize, coord, &region ) )
	{
		DWORD temp = GetLastError ();
		exit ( 2 );
	}

	Sleep ( 1 );
#endif
}

void cornsoup_DrawChar ( wchar_t ch, unsigned x, unsigned y )
{
#ifdef WIN32
	if ( x >= g_width || x < 0 )
		return;
	if ( y >= g_height || y < 0 )
		return;

	g_charBuffer [ y * g_width + x ].Char.UnicodeChar = ch;
	g_charBuffer [ y * g_width + x ].Attributes = g_charColor;
#endif
}

void cornsoup_DrawText ( const wchar_t * text, unsigned x, unsigned y )
{
#ifdef WIN32
	if ( y >= g_height || y < 0 )
		return;

	size_t len = wcslen ( text );
	for ( unsigned i = 0; i < len; ++i )
	{
		if ( x + i >= g_width || x + i < 0 )
			continue;

		g_charBuffer [ y * g_width + x + i ].Char.UnicodeChar = text [ i ];
		g_charBuffer [ y * g_width + x + i ].Attributes = g_charColor;
	}
#endif
}

void cornsoup_FillRect ( int x, int y, int width, int height )
{
#ifdef WIN32
	for ( int cy = y; cy < y + height; ++cy )
	{
		if ( cy >= ( int ) g_height || cy < 0 )
			continue;

		for ( int cx = x; cx < x + width; ++cx )
		{
			if ( cx >= ( int ) g_width || cx < 0 )
				continue;

			g_charBuffer [ cy * g_width + cx ].Char.UnicodeChar = ' ';
			g_charBuffer [ cy * g_width + cx ].Attributes = g_charColor;
		}
	}
#endif
}

void cornsoup_FlagDrawFPS ( bool flag )
{
	g_flagDrawFPS = flag;
}