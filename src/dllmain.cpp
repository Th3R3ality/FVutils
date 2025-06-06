#include <windows.h>
#include <chrono>
#include <thread>

#include <jni.h>
#include <jvmti.h>

#include "imgui/imgui.h"

#include "hooks/hooks.h"
#include "java/java.h"
#include "minecraft/minecraft.h"
#include "JavaHook/JavaHook.h"
#include "cache/cache.h"
#include "cheat/modules/Modules.h"

void mainthread( HMODULE hmodule )
{
	AllocConsole();
	HWND consoleHwnd = GetConsoleWindow();
	FILE* f;
 	freopen_s( &f, "CONOUT$", "w", stdout );
	printf( "hello\n" );

	java::Init();
	hooks::Init();
	modules::Init();

	while ( !GetAsyncKeyState( VK_END ) )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}

	printf( "destroying hooks\n" );
	hooks::Destroy();

	printf( "destroying java\n" );
	java::Destroy();
	printf( "bye o/\n" );
	Sleep( 100 );

	if ( consoleHwnd )
	{
		FreeConsole();
		Sleep( 100 );
		PostMessageA( consoleHwnd, WM_CLOSE, 0, 0 );
	}

	Sleep( 10 );
	FreeLibraryAndExitThread( hmodule, 0 );
}

BOOL APIENTRY DllMain( HMODULE hmodule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		if ( auto handle = CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )mainthread, hmodule, 0, 0 ) )
		{
			CloseHandle( handle );
		}
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

