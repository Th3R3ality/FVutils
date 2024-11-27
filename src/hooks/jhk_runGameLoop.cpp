#include "hooks.h"
#include "../minecraft/minecraft.h"
#include "../cache/cache.h"
#include "../global.h"

namespace hooks
{
	void jhk_runGameLoop( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		if ( global::glUnhookWant )
			return;

		JNIEnv* env = thread->get_env();
		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf("TlsSetValue error"); 
			return;
		}

		if ( ( minecraft::objectsAreValid = minecraft::ValidateObjects() ) )
		{
			cache::UpdateCache();
		}
	}
}