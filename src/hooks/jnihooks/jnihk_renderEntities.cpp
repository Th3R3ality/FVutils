#include "../hooks.h"
#include "../../global.h"
#include "../../minecraft/client/renderer/RenderGlobal/RenderGlobal.h"
#include "../../cache/cache.h"
namespace hooks
{
	JNIEXPORT void JNICALL jnihk_renderEntities ( JNIEnv* env, jobject instance, /*Entity*/ jobject renderViewEntity, /*ICamera*/jobject camera, jfloat partialTicks )
	{
		if ( global::glUnhookWaiting )
			return;

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return;
		}

		try
		{
			env->CallNonvirtualVoidMethod( instance, RenderGlobal::klass, __orig_mid_jnihk_renderEntities, renderViewEntity, camera, partialTicks );

			if ( env->ExceptionCheck() )
			{
				printf( "jnihk_renderEntities: env exception\n" );
				return;
			}
		}
		catch ( std::exception e )
		{
			printf( "jnihk_renderEntities: try/catch exception\n" );
			return;
		}

		//cache::renderEntitiesData = { .instance = env->NewGlobalRef(instance), .renderViewEntity = env->NewGlobalRef(renderViewEntity), .camera = env->NewGlobalRef(camera), .partialTicks = partialTicks};
		//printf( "renderEntities\n" );
	}
}