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

	float renderPartialTicks()
	{
		return TLSENV->GetFloatField(this->instance, Timer::fieldIDs["renderPartialTicks"]);
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME