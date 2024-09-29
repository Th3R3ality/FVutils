#pragma once
#include <memory>

#include "IClass.h"
#include "client/EntityPlayerSP/EntityPlayerSP.h"
#include "client/WorldClient/WorldClient.h"
#include "util/Timer/Timer.h"

namespace minecraft
{
	inline std::unique_ptr<EntityPlayerSP> localPlayer = {};
	inline std::unique_ptr<WorldClient> world = {};
	inline std::unique_ptr<Timer> timer = {};

	bool ValidateObjects();
}


#define CURRENTCLASSNAME Minecraft

SETCLASSPATH("net/minecraft/client/Minecraft");

struct CURRENTCLASSNAME : IClass
{
	using IClass::IClass;


	STATICS();

	static jobject staticInstance;

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_STATIC_METHOD( "getMinecraft", "()Lnet/minecraft/client/Minecraft;" );
		
		GET_FIELD("thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
		GET_FIELD("theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
		GET_FIELD("renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
		GET_FIELD("timer", "Lnet/minecraft/util/Timer;");
		GET_FIELD("gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
		GET_FIELD("currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
		GET_FIELD("objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");

		GET_METHOD("getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
		GET_METHOD("clickMouse", "()V");
		GET_METHOD("runTick", "()V");

		GetStaticInstance();
	}



	STRUCTORS();

	static jobject GetStaticInstance()
	{
		if ( !Minecraft::staticInstance )
			Minecraft::staticInstance = java::env->CallStaticObjectMethod( Minecraft::klass, methodIDs[ "getMinecraft" ] );

		return Minecraft::staticInstance;
	}

};

#undef CURRENTCLASSNAME