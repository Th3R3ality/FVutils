#include "hooks.h"
#include <iostream>
#include "../global.h"
#include "../render/render.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"

void hooks::Init()
{
	MH_Initialize();

	auto hMod = GetModuleHandleA( "OPENGL32.dll" );
	if ( !hMod ) return;

	MH_CreateHook( GetProcAddress( hMod, "wglSwapBuffers" ), hkwglSwapBuffers, &wglSwapBuffersOrig );
	MH_EnableHook( MH_ALL_HOOKS );

	if ( !java::initialised )
		return;

	jclass __NetHandlerPlayClient = java::FindClass( "net/minecraft/client/network/NetHandlerPlayClient" );
	printf( "__NetHandlerPlayClient: %p\n", __NetHandlerPlayClient );
	jmethodID __handleChat = java::env->GetMethodID( __NetHandlerPlayClient, "handleChat", "(Lnet/minecraft/network/play/server/S02PacketChat;)V" );
	printf( "__handleChat: %p\n", __handleChat );

	jclass _NetHandlerPlayClient = NetHandlerPlayClient::klass;
	printf( "NetHandlerPlayClient: %p\n", _NetHandlerPlayClient );
	if ( !_NetHandlerPlayClient )
		return;
	jmethodID handleChat =  NetHandlerPlayClient::methodIDs["handleChat"];
	printf( "handleChat: %p\n", handleChat );
	if ( !handleChat )
		return;


	JavaHook::hook( handleChat, jhk_handleChat );
}

void hooks::Destroy()
{
	while ( !global::glUnhookWaiting )
	{
		global::glUnhookWant = true;
		Sleep( 10 );
	}
	//if ( EndSceneOrig )
	//{
	//	VMTEntryHook( vtable, INDEX_ENDSCENE, EndSceneOrig );
	//}

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize();

	Sleep( 10 );

	JavaHook::clean();

	Sleep( 10 );

}
