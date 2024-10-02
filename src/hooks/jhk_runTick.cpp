#include "hooks.h"

namespace hooks
{
	void jhk_runTick( HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel )
	{
		JNIEnv* env = thread->get_env();
	}
}