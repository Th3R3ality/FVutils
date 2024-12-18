#include "../hooks.h"
#include "../../minecraft/client/renderer/entity/RenderManager/RenderManager.h"

#include "../../global.h"
#include "../../cache/cache.h"
#include "../../minecraft/minecraft.h"
namespace hooks
{
	JNIEXPORT jboolean JNICALL jnihk_renderEntitySimple( JNIEnv* env, jobject instance, /*Entity*/jobject entityIn, jfloat partialTicks)
	{
		jboolean ret;
		if ( global::glUnhookWaiting )
			return 0;

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return 0;
		}

		try
		{
			ret = env->CallNonvirtualBooleanMethod( instance, RenderManager::klass, __orig_mid_jnihk_renderEntitySimple, entityIn, partialTicks );

			if ( env->ExceptionCheck() )
			{
				printf( "jnihk_renderEntitySimple: env exception\n" );
				return 0;
			}

		}
		catch ( std::exception e )
		{
			printf( "jnihk_renderEntitySimple: try/catch exception\n" );
			return 0;
		}

		//std::cout << "jnihk_renderEntitySimple : " << minecraft::world->theProfiler(true).getNameOfLastSection(true) << "\n";

		return ret;
	}
}