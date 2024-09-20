#pragma once
#include "../../world/World/World.h"

struct WorldClient : World
{
	const char* klassPath = "net.minecraft.client.multiplayer.WorldClient";

	STRUCTORS( WorldClient );
};