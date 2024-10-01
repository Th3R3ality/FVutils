#pragma once
#include "../../../IClass.h"

#define CURRENTCLASSNAME PlayerControllerMP

SETCLASSPATH( "net/minecraft/client/multiplayer/PlayerControllerMP" );

struct PlayerControllerMP : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V" );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME