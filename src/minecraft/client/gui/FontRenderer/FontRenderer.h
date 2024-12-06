#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME FontRenderer

_SETCLASSPATH( "net/minecraft/client/gui", "FontRenderer", "avn");

struct FontRenderer : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME