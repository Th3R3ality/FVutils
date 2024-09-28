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

		GET_METHOD( "getPosition", "()Lnet/minecraft/util/BlockPos;" );
		GET_METHOD( "setSprinting", "(Z)V" );
		GET_METHOD( "swingItem", "()V" );
	}

	STRUCTORS();

	static jobject GetStaticInstance();
};


#undef CURRENTCLASSNAME