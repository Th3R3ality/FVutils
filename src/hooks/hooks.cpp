#include "hooks.h"
#include <iostream>
#include <thread>
#include <vector>

#include "../global.h"
#include "../rendering/rendering.h"
#include "../minecraft/client/NetHandlerPlayClient/NetHandlerPlayClient.h"
#include "../minecraft/client/renderer/entity/RenderLivingEntity/RenderLivingEntity.h"
#include "../minecraft/minecraft.h"
#include "../minecraft/client/renderer/entity/RenderPlayer/RenderPlayer.h"
#include "../minecraft/profiler/Profiler/Profiler.h"

std::vector<jmethodID> hookedMethods = {};

#define JAVA_HOOK(detour, methodID) \
if (false == JavaHook::hook(methodID, detour)) \
{ printf( "[-] failed hooking: " ## #detour ## "\n" ); } \
else {printf( "[+] hooked: " ## #detour ## "\n" );}

#define JNI_HOOK(methodID, detour) \
{auto res = jnihook::attach(methodID, detour, &__orig_mid_ ## detour); \
if ( res.has_value()) { printf( "[+] hooked: " ## #detour ## "\n" ); hookedMethods.emplace_back(methodID); } \
else { printf( "[-] failed hooking: " ## #detour ## "\n" ); }}

#define JNI_UNHOOK_ALL() {for (auto&& mid : hookedMethods){if (mid != NULL){jnihook::detach(mid);}}}

bool jnihookInitialised = false;
void hooks::Init()
{
	MH_Initialize();

	auto hMod = GetModuleHandleA( "OPENGL32.dll" );
	if ( !hMod ) return;

	MH_CreateHook( GetProcAddress( hMod, "wglSwapBuffers" ), hkwglSwapBuffers, &wglSwapBuffersOrig );
	MH_EnableHook( MH_ALL_HOOKS );

	if ( !java::initialised )
		return;

	



	//jvmtiError err;
	//jthread* threads;
	//jint threadCount;
	//err = java::tienv->GetAllThreads( &threadCount, &threads );

	//jthread currentThread = nullptr;
	//err = java::tienv->GetCurrentThread( &currentThread );

	//for ( int i = 0; i < threadCount; i++ )
	//{
	//	if ( !java::env->IsSameObject( currentThread, threads[ i ] ) )
	//	{
	//		err = java::tienv->SuspendThread( threads[ i ] );
	//	}
	//}

	//Sleep( 100 );

	// jni hook
	{
		printf( "jnihook INIT : " );
		if ( jnihook::result_t::JNIHOOK_OK != jnihook::init( java::jvm ) )
		{
			printf( "ERR\n" );
			return;
		}
		printf( "OK\n" );
		jnihookInitialised = true;

		java::env->ExceptionClear();

		JNI_HOOK( Minecraft::methodIDs[ "runGameLoop" ], jnihk_runGameLoop );
		JNI_HOOK( Minecraft::methodIDs[ "runTick" ], jnihk_runTick );


	}

	// java hook
	{
		//static int runonce = []()->int
		//	{
		//		jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
		//		//capabilities.can_suspend = JVMTI_ENABLE;
		//		java::tienv->GetPotentialCapabilities(&capabilities);
		//		java::tienv->AddCapabilities(&capabilities);
		//		return 0;
		//	}();

		//JAVA_HOOK( javahk_handleChat, NetHandlerPlayClient::methodIDs[ "handleChat" ] );
		//JAVA_HOOK( javahk_renderName, RenderLivingEntity::methodIDs[ "renderName" ] );
		//JAVA_HOOK( javahk_runTick, Minecraft::methodIDs[ "runTick" ] );
		//JAVA_HOOK( javahk_runGameLoop, Minecraft::methodIDs[ "runGameLoop" ] );	
		//JAVA_HOOK( javahk_clickMouse, Minecraft::methodIDs[ "clickMouse" ] );	
		//JAVA_HOOK( javahk_endStartSection, Profiler::methodIDs[ "endStartSection" ] );	

	}

	//Sleep( 100 );

	//std::vector<jvmtiError> errors;
	//errors.resize( threadCount );
	//java::tienv->ResumeThreadList( threadCount, threads, errors.data() );
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




	// java hook
	//{
	//	jvmtiError err;

	//	jthread* threads;
	//	jint threadCount;
	//	err = java::tienv->GetAllThreads( &threadCount, &threads );

	//	jthread currentThread = nullptr;
	//	err = java::tienv->GetCurrentThread( &currentThread );

	//	for ( int i = 0; i < threadCount; i++ )
	//	{
	//		if ( !java::env->IsSameObject( currentThread, threads[ i ] ) )
	//		{
	//			err = java::tienv->SuspendThread( threads[ i ] );
	//		}
	//	}

	//	Sleep( 100 );


	//	//JavaHook::clean();

	//	Sleep( 10 );

	//	std::vector<jvmtiError> errors;
	//	errors.resize( threadCount );
	//	java::tienv->ResumeThreadList( threadCount, threads, errors.data() );
	//}

	//Sleep( 100 );


	// jni hook
	{
		if ( jnihookInitialised )
		{
			JNI_UNHOOK_ALL();

			jnihook::shutdown();
		}
	}
}
