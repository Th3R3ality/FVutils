#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME World

SETCLASSPATH( "net/minecraft/world/World" );

struct CURRENTCLASSNAME : IClass
{
	using IClass::IClass;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD( "playerEntities", "Ljava/util/List;" );
	}

	STRUCTORS();
};


#undef CURRENTCLASSNAME