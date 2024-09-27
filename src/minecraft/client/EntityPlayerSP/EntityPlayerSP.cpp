#include "EntityPlayerSP.h"
#include "../../minecraft.h"

MAKE_INITIALISER( EntityPlayerSP );


jobject EntityPlayerSP::GetInstance()
{
	return java::env->GetObjectField(minecraft::GetInstance(), minecraft::fieldIDs["thePlayer"]);
}
