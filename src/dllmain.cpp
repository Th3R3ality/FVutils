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
#include "jnihook/jnihook.h"

jmethodID runTickOrig = nullptr;

void runTickHook(JNIEnv* env, jclass klass)
{
	printf( "getMinecraft hook\n" );
	env->CallStaticVoidMethod( klass, runTickOrig );
}

void mainthread( HMODULE hmodule )
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	printf("hello\n");
	printf("BaseAddress : %x\n", GetModuleHandleA(NULL));


	java::Init();
	minecraft::Init();

	hooks::Init();
	jnihook_result_t init_res = JNIHook_Init(java::jvm);
	printf( "init_res: %i", init_res );

	if ( init_res == JNIHOOK_OK )
	{
		jnihook_result_t attach_res = JNIHook_Attach( minecraft::methodIDs[ "getMinecraft" ], runTickHook, &runTickOrig );
		printf( "attach_res: %i", attach_res );
	}


	printf( "runtick: %p\n", minecraft::methodIDs[ "runTick" ] );

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

	java::env->DeleteLocalRef( nhpc );
	if ( init_res == JNIHOOK_OK )
	{
		JNIHook_Shutdown();
	}
	hooks::Destroy();

	minecraft::Destroy();
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

