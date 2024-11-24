#pragma once
#include <memory>

#include "IClass.h"
#include "client/EntityPlayerSP/EntityPlayerSP.h"
#include "client/WorldClient/WorldClient.h"
#include "util/Timer/Timer.h"
#include "client/renderer/entity/RenderManager/RenderManager.h"

struct Minecraft;

namespace minecraft
{
	//inline std::unique_ptr<Minecraft> mc = {};
	inline std::unique_ptr<EntityPlayerSP> localPlayer = {};
	inline std::unique_ptr<WorldClient> world = {};
	inline std::unique_ptr<Timer> timer = {};
	inline std::unique_ptr<RenderManager> renderManager = {};

	inline bool objectsAreValid = false;
	bool ValidateObjects();
}


#define CURRENTCLASSNAME Minecraft

SETCLASSPATH("net/minecraft/client/Minecraft");

struct Minecraft : IClass
{
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
		//minecraft::mc = std::make_unique<Minecraft>(GetStaticInstance());
		//minecraft::mc->noDeref = true;
	}

	STRUCTORS();

	static jobject GetStaticInstance()
	{
		if ( !Minecraft::staticInstance )
			Minecraft::staticInstance = java::env->CallStaticObjectMethod( Minecraft::klass, methodIDs[ "getMinecraft" ] );

		return Minecraft::staticInstance;
	}


	static bool IsInGuiState()
	{

		if ( ( ( JNIEnv* )TlsGetValue( java::envTlsIndex ) )->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "currentScreen" ] ) != NULL ) return true;
		return false;
	}
};

#undef CURRENTCLASSNAME