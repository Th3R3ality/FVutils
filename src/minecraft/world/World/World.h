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

	}

	STRUCTORS();
};


#undef CURRENTCLASSNAME