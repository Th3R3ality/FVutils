#pragma once
#include "../EntityLivingBase/EntityLivingBase.h"

#define CURRENTCLASSNAME EntityPlayer

SETCLASSPATH( "net/minecraft/entity/player/EntityPlayer" );

struct CURRENTCLASSNAME : public EntityLivingBase
{
	using EntityLivingBase::EntityLivingBase;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );
	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME