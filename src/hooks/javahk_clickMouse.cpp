#include "hooks.h"

#include "../minecraft/minecraft.h"
#include "../global.h"

namespace hooks
{
	void javahk_clickMouse( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return;
		}

		Minecraft::leftClickCounter( 0 );
	}
}