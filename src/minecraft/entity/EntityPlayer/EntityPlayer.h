#pragma once
#include "../EntityLivingBase/EntityLivingBase.h"

#define CURRENTCLASSNAME EntityPlayer

SETCLASSPATH( "net/minecraft/entity/player/EntityPlayer" );

struct EntityPlayer : public EntityLivingBase
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME