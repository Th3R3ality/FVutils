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
#include "JavaHook/JavaHook.h"

void mainthread( HMODULE hmodule )
{
	AllocConsole();
	FILE* f;
	freopen_s( &f, "CONOUT$", "w", stdout );
	printf( "hello\n" );
	printf( "BaseAddress : %x\n", GetModuleHandleA( NULL ) );


	java::Init();
	minecraft::Init();
	hooks::Init();
	

	jclass nhpc = java::FindClass( "net.minecraft.client.network.NetHandlerPlayClient" );

	jmethodID handleChatID = java::env->GetMethodID( nhpc, "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );

	printf( "handleChat: %p\n", handleChatID );

	while ( !GetAsyncKeyState( VK_DELETE ) )
	{
		if ( !minecraft::ValidateObjects() )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
			continue;
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
	}

	//if ( nhpc )
	//	java::env->DeleteLocalRef( nhpc );

	//java::env->ExceptionClear();
	printf( "destroying hooks\n" );
	hooks::Destroy();

	printf( "destroying minecraft\n" );
	minecraft::Destroy();

	printf( "destroying java\n" );
	java::Destroy();

	if ( HWND consoleHwnd = GetConsoleWindow() )
	{
		FreeConsole();
		PostMessageA( consoleHwnd, WM_CLOSE, 0, 0 );
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

