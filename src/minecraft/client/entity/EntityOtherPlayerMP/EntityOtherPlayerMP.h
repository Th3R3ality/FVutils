#pragma once

#include "../AbstractClientPlayer/AbstractClientPlayer.h"

#define CURRENTCLASSNAME EntityOtherPlayerMP

SETCLASSPATH( "net/minecraft/client/entity/EntityOtherPlayerMP" );

struct EntityOtherPlayerMP : public AbstractClientPlayer
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME