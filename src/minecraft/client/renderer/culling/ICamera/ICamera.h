#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME ICamera

_SETCLASSPATH( "net/minecraft/client/renderer/culling", "ICamera", "bia");

struct ICamera : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME