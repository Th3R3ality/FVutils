#pragma once
#include "../../entity/EntityPlayer/EntityPlayer.h"

#define CURRENTCLASSNAME EntityPlayerSP

SETCLASSPATH( "net/minecraft/entity/EntityLivingBase" );

struct CURRENTCLASSNAME : public EntityPlayer
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();
	}

	STRUCTORS();

	jobject GetInstance();
};


#undef CURRENTCLASSNAME