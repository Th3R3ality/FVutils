#include "hooks.h"
#include <iostream>
#include "../global.h"
#include "../rendering/rendering.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../minecraft/client/renderer/entity/RenderLivingEntity/RenderLivingEntity.h"
#include "../minecraft/minecraft.h"

#define HOOK(detour, methodID) \
if (false == JavaHook::hook(methodID, detour)) \
{ printf( "[-] failed hooking: " ## #detour ## "\n" ); } \
else {printf( "[+] hooked: " ## #detour ## "\n" );}

void hooks::Init()
{
	MH_Initialize();

	auto hMod = GetModuleHandleA( "OPENGL32.dll" );
	if ( !hMod ) return;

	MH_CreateHook( GetProcAddress( hMod, "wglSwapBuffers" ), hkwglSwapBuffers, &wglSwapBuffersOrig );
	MH_EnableHook( MH_ALL_HOOKS );

	if ( !java::initialised )
		return;

	HOOK( jhk_handleChat, NetHandlerPlayClient::methodIDs[ "handleChat" ] );
	HOOK( jhk_renderName, RenderLivingEntity::methodIDs[ "renderName" ] );
	HOOK( jhk_runTick, Minecraft::methodIDs[ "runTick" ] );
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
