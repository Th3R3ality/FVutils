#include "hooks.h"
#include <iostream>
#include <thread>

#include "../global.h"
#include "../rendering/rendering.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../minecraft/client/renderer/entity/RenderLivingEntity/RenderLivingEntity.h"
#include "../minecraft/minecraft.h"
#include "../minecraft/client/renderer/entity/RenderPlayer/RenderPlayer.h"

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
	
	jvmtiError err;

	jthread* threads;
	jint threadCount;
	err = java::tienv->GetAllThreads( &threadCount, &threads );

	jthread currentThread = nullptr;
	err = java::tienv->GetCurrentThread( &currentThread );

	for ( int i = 0; i < threadCount; i++ )
	{
		if ( !java::env->IsSameObject(currentThread, threads[i]))
		{
			err = java::tienv->SuspendThread( threads[ i ] );
		}
	}

	Sleep( 100 );

	//HOOK( jhk_handleChat, NetHandlerPlayClient::methodIDs[ "handleChat" ] );
	//HOOK( jhk_renderName, RenderLivingEntity::methodIDs[ "renderName" ] );
	//HOOK( jhk_runTick, Minecraft::methodIDs[ "runTick" ] );
	HOOK( jhk_runGameLoop, Minecraft::methodIDs[ "runGameLoop" ] );	
	//HOOK( jhk_clickMouse, Minecraft::methodIDs[ "clickMouse" ] );	

	Sleep( 100 );

	std::vector<jvmtiError> errors;
	errors.resize( threadCount );
	java::tienv->ResumeThreadList( threadCount, threads, errors.data() );
}

void hooks::Destroy()
{
	while ( !global::glUnhookWaiting )
	{
		global::glUnhookWant = true;
		Sleep( 10 );
	}

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize();

	Sleep( 10 );

	jvmtiError err;

	jthread* threads;
	jint threadCount;
	err = java::tienv->GetAllThreads( &threadCount, &threads );

	jthread currentThread = nullptr;
	err = java::tienv->GetCurrentThread( &currentThread );

	for ( int i = 0; i < threadCount; i++ )
	{
		if ( !java::env->IsSameObject(currentThread, threads[i]))
		{
			err = java::tienv->SuspendThread( threads[ i ] );
		}
	}

	Sleep( 100 );

	JavaHook::clean();

	Sleep( 100 );

	std::vector<jvmtiError> errors;
	errors.resize( threadCount );
	java::tienv->ResumeThreadList( threadCount, threads, errors.data() );

	Sleep( 10 );

}
