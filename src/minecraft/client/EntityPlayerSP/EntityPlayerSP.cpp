#include "EntityPlayerSP.h"
#include "../../minecraft.h"

MAKE_INITIALISER( EntityPlayerSP );

jobject EntityPlayerSP::GetStaticInstance()
{
	return java::env->GetObjectField(Minecraft::staticInstance, Minecraft::fieldIDs["thePlayer"]);
}
