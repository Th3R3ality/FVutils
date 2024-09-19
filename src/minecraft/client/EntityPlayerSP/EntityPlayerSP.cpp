#include "EntityPlayerSP.h"
#include "../../minecraft.h"

jobject EntityPlayerSP::GetInstance()
{
	return java::env->GetObjectField(minecraft::GetInstance(), minecraft::fieldIDs["thePlayer"]);
}
