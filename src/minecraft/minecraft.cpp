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
			localPlayer = std::make_unique<EntityPlayerSP>( localPlayerInstance );
		else
			java::env->DeleteLocalRef( localPlayerInstance );

		jobject worldClientInstance = java::env->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "theWorld" ] );
		if ( !worldClientInstance )
		{
			world = nullptr;
			return false;
		}
		if ( world == nullptr || worldClientInstance != world->instance )
			world = std::make_unique<WorldClient>( worldClientInstance );
		else
			java::env->DeleteLocalRef( worldClientInstance );

		return true;
	}
}