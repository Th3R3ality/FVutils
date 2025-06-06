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
	//inline std::unique_ptr<Minecraft> mc = nullptr;
	inline std::unique_ptr<EntityPlayerSP> localPlayer = nullptr;
	inline std::unique_ptr<WorldClient> world = nullptr;
	inline std::unique_ptr<Timer> timer = nullptr;
	inline std::unique_ptr<RenderManager> renderManager = nullptr;

	inline bool objectsAreValid = false;
	bool ValidateObjects();
}


#define CURRENTCLASSNAME Minecraft

_SETCLASSPATH( "net/minecraft/client", "Minecraft", "ave");

struct Minecraft : IClass
{
	STATICS();

	static jobject staticInstance;

	static void Initialise()
	{
		INITIALISER_HEADER();

		_GET_STATIC_METHOD( "getMinecraft",	"func_71410_x",		"A",	"()Lnet/minecraft/client/Minecraft;" );

		_GET_FIELD( "currentScreen",		"field_71462_r",	"m",	"Lnet/minecraft/client/gui/GuiScreen;");
		_GET_FIELD( "gameSettings",			"field_71474_y",	"t",	"Lnet/minecraft/client/settings/GameSettings;" );
		_GET_FIELD( "objectMouseOver",		"field_71476_x",	"s",	"Lnet/minecraft/util/MovingObjectPosition;" );
		_GET_FIELD( "renderManager",		"field_175616_W",	"aa",	"Lnet/minecraft/client/renderer/entity/RenderManager;" );
		_GET_FIELD( "thePlayer",			"field_71439_g",	"h",	"Lnet/minecraft/client/entity/EntityPlayerSP;" );
		_GET_FIELD( "theWorld",				"field_71441_e",	"f",	"Lnet/minecraft/client/multiplayer/WorldClient;" );
		_GET_FIELD( "timer",				"field_71428_T",	"Y",	"Lnet/minecraft/util/Timer;" );
		_GET_FIELD( "leftClickCounter",		"field_71429_W",	"ag",	"I");
		_GET_FIELD( "renderGlobal",			"field_71438_f",	"g",	"Lnet/minecraft/client/renderer/RenderGlobal;" );

		_GET_METHOD( "clickMouse",			"func_147116_af",	"aw",	"()V" );
		_GET_METHOD( "getRenderViewEntity",	"func_175606_aa",	"ac",	"()Lnet/minecraft/entity/Entity;");
		_GET_METHOD( "runTick",				"func_71407_l",		"s",	"()V" );
		_GET_METHOD( "runGameLoop",			"func_71411_J",		"av",	"()V");

		GetStaticInstance();
	}

	STRUCTORS();

	jobject renderManager()
	{
		return TLSENV->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "renderManager" ] );
	}

	static jobject GetStaticInstance()
	{
		if ( !Minecraft::staticInstance )
			Minecraft::staticInstance = java::env->CallStaticObjectMethod( Minecraft::klass, methodIDs[ "getMinecraft" ] );

		return Minecraft::staticInstance;
	}

	static bool IsInGuiState()
	{
		jobject screen = nullptr;
		if ( ( screen = TLSENV->GetObjectField( Minecraft::staticInstance, Minecraft::fieldIDs[ "currentScreen" ] ) ) != NULL )
		{
			//TLSENV->DeleteLocalRef( screen );
			return true;
		}
		return false;
	}

	static void leftClickCounter( jint i )
	{
		TLSENV->SetIntField( Minecraft::staticInstance, Minecraft::fieldIDs[ "leftClickCounter" ], i );
	}
};

#undef CURRENTCLASSNAME