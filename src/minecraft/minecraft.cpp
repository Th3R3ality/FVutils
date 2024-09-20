#include "minecraft.h"

#include <iostream>

#include "../java/java.h"

namespace minecraft
{
	void Init()
	{
		GetClass();
		methodIDs["getMinecraft"] = java::env->GetStaticMethodID(klass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");

		GetInstance();

		fieldIDs["thePlayer"] = java::env->GetFieldID(klass, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		fieldIDs["theWorld"] = java::env->GetFieldID(klass, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");

		fieldIDs["renderManager"] = java::env->GetFieldID(klass, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		fieldIDs["timer"] = java::env->GetFieldID(klass, "timer", "Lnet/minecraft/util/Timer;");
		fieldIDs["gameSettings"] = java::env->GetFieldID(klass, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
		methodIDs["getRenderViewEntity"] = java::env->GetMethodID(klass, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
		fieldIDs["currentScreen"] = java::env->GetFieldID(klass, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
		fieldIDs["objectMouseOver"] = java::env->GetFieldID(klass, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
		methodIDs["clickMouse"] = java::env->GetMethodID(klass, "clickMouse", "()V");

		//thePlayer = new CEntityPlayerSP();
		//theWorld = new CWorldClient();
		//activeRenderInfo = new CActiveRenderInfo();
		//renderManager = new CRenderManager();
		//timer = new CTimer();
		//gameSettings = new CGameSettings();
	}

	void Destroy()
	{
		java::env->DeleteLocalRef( klass );
	}

	jobject GetInstance()
	{
		if ( !instance )
			instance = java::env->CallStaticObjectMethod(GetClass(), methodIDs["getMinecraft"]);

		return instance;
	}

	jclass GetClass()
	{
		if ( !klass )
			klass = java::FindClass(klassPath);

		return klass;
	}

	bool ValidateObjects()
	{
		jobject localPlayerInstance = java::env->GetObjectField( instance, fieldIDs[ "thePlayer" ] );
		if ( !localPlayerInstance )
		{
			localPlayer = nullptr;
			return false;
		}
		if ( localPlayer == nullptr || localPlayerInstance != localPlayer->instance )
			localPlayer = std::make_unique<EntityPlayerSP>( localPlayerInstance );
		//else
		//	java::env->DeleteLocalRef( localPlayerInstance );
		
		jobject worldClientInstance = java::env->GetObjectField( instance, fieldIDs[ "thePlayer" ] );
		if ( !worldClientInstance )
		{
			world = nullptr;
			return false;
		}
		if (world == nullptr || worldClientInstance != world->instance )
			world = std::make_unique<WorldClient>(worldClientInstance);
		//else
		//	java::env->DeleteLocalRef( worldClientInstance );

		return true;
	}
}