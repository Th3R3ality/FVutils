#include "../hooks.h"
#include "../../minecraft/minecraft.h"
#include "../../cache/cache.h"
#include "../../global.h"

#include <iostream>

JNIEXPORT void JNICALL hooks::jnihk_runGameLoop( JNIEnv* env, jobject instance )
{
	if ( global::glUnhookWaiting )
		return;

	if ( !TlsSetValue( java::envTlsIndex, env ) )
	{
		printf( "TlsSetValue error" );
		return;
	}

	//std::cout << "Target::sayHello HOOK CALLED!" << std::endl;
	//std::cout << "Calling original method..." << std::endl;

	try
	{
		env->CallNonvirtualVoidMethod( instance, Minecraft::klass, __orig_mid_jnihk_runGameLoop );

		if ( env->ExceptionCheck() )
		{
			printf( "runGameLoop: env exception\n" );
			return;
		}
	}
	catch (std::exception e) {
		printf( "runGameLoop: try/catch exception\n" );
		return;
	}

	if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
	{
		cache::UpdateCache();
	}
}