#include "../hooks.h"
#include "../../minecraft/minecraft.h"
#include "../../global.h"
#include "../../cheat/modules/Modules.h"

JNIEXPORT void JNICALL hooks::jnihk_runTick( JNIEnv* env, jobject instance )
{
	if ( global::glUnhookWaiting )
		return;

	if ( !TlsSetValue( java::envTlsIndex, env ) )
	{
		printf( "TlsSetValue error" );
		return;
	}

	bool cancelled = false;
	for ( auto&& fn : modules::callbacks::hooks::preRunTick )
	{
		if ( fn() )
			cancelled = true;
	}
	if ( cancelled )
		return;

	try
	{
		env->CallNonvirtualVoidMethod( instance, Minecraft::klass, __orig_mid_jnihk_runTick );

		if ( env->ExceptionCheck() )
		{
			printf( "runTick: env exception\n" );
			return;
		}
	}
	catch ( std::exception e )
	{
		printf( "runTick: try/catch exception\n" );
		return;
	}

	for ( auto&& fn : modules::callbacks::hooks::postRunTick )
	{
		fn();
	}
}
