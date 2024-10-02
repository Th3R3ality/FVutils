#pragma once
#include <IClass.h>

#define CURRENTCLASSNAME Timer

SETCLASSPATH( "net/minecraft/util/Timer" );

struct Timer : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD( "renderPartialTicks", "F" );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME