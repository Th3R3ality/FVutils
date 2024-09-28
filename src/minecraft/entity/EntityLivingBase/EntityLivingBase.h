#pragma once
#include "../Entity/Entity.h"

#define CURRENTCLASSNAME EntityLivingBase

SETCLASSPATH( "net/minecraft/entity/EntityLivingBase" );

struct CURRENTCLASSNAME : public Entity
{
	using Entity::Entity;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );


		GET_METHOD( "getHealth", "()F");
		GET_METHOD( "getMaxHealth", "()F");
		GET_METHOD( "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME