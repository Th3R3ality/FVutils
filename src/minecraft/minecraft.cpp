#include "minecraft.h"

MAKE_INITIALISER( Minecraft );
jobject Minecraft::staticInstance = 0;

namespace minecraft
{
	bool ValidateObjects()
	{
		jobject localPlayerInstance = java::env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "thePlayer" ] );
		if ( !localPlayerInstance )
		{
			localPlayer = nullptr;
			return false;
		}
		if ( localPlayer == nullptr || localPlayerInstance != localPlayer->instance )
		{
			localPlayer = std::make_unique<EntityPlayerSP>( localPlayerInstance );
			localPlayer->noDeref = true;
		}
		else
			java::env->DeleteLocalRef( localPlayerInstance );

		jobject worldClientInstance = java::env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "theWorld" ] );
		if ( !worldClientInstance )
		{
			world = nullptr;
			return false;
		}
		if ( world == nullptr || worldClientInstance != world->instance )
		{
			world = std::make_unique<WorldClient>( worldClientInstance );
			world->noDeref = true;
		}
		else
			java::env->DeleteLocalRef( worldClientInstance );

		jobject timerInstance = java::env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "timer" ] );
		if ( !timerInstance )
		{
			timer = nullptr;
			return false;
		}
		if ( timer == nullptr || timerInstance != timer->instance )
		{
			timer = std::make_unique<Timer>( timerInstance );
			timer->noDeref = true;
		}
		else
			java::env->DeleteLocalRef( timerInstance );

		jobject rmInstance = java::env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "renderManager" ] );
		if ( !rmInstance )
		{
			renderManager = nullptr;
			return false;
		}
		if ( renderManager == nullptr || rmInstance != renderManager->instance )
		{
			renderManager = std::make_unique<RenderManager>( rmInstance );
			renderManager->noDeref = true;
		}
		else
			java::env->DeleteLocalRef( rmInstance );

		return true;
	}
}