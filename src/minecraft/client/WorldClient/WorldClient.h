#pragma once
#include "../../world/World/World.h"

#define CURRENTCLASSNAME WorldClient

SETCLASSPATH( "net/minecraft/client/multiplayer/WorldClient" );

struct CURRENTCLASSNAME : World
{
	using World::World;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};


#undef CURRENTCLASSNAME