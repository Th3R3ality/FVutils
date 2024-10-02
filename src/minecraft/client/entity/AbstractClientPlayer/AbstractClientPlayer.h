#pragma once

#include "../../../entity/EntityLivingBase/EntityLivingBase.h"

#define CURRENTCLASSNAME AbstractClientPlayer

SETCLASSPATH( "net/minecraft/client/entity/AbstractClientPlayer" );

struct AbstractClientPlayer : public EntityLivingBase
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME