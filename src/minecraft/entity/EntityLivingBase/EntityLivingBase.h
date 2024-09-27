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
	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME