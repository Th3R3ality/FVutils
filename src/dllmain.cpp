#include <windows.h>
#include <chrono>
#include <thread>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <jni.h>
#include <jvmti.h>

#include "imgui/imgui.h"

#include "hooks/hooks.h"
#include "java/java.h"
#include "minecraft/minecraft.h"

void mainthread( HMODULE hmodule )
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	printf("hello\n");
	printf("BaseAddress : %x\n", GetModuleHandleA(NULL));


	java::Init();
	hooks::Init();
	minecraft::Init();

	while ( !GetAsyncKeyState( VK_DELETE ) )
	{
		if ( !minecraft::ValidateObjects() )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
			continue;
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
	}

	minecraft::Destroy();
	hooks::Destroy();
	java::Destroy();

	if ( HWND consoleHwnd = GetConsoleWindow() )
	{
		FreeConsole();
		PostMessageA(consoleHwnd, WM_CLOSE, 0, 0);
	}
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

