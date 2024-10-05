#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME DirectIntBufferU

SETCLASSPATH( "java/nio/DirectIntBufferU" );

struct DirectIntBufferU : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME