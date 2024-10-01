#pragma once
#include "../../../IClass.h"

#define CURRENTCLASSNAME ActiveRenderInfo

SETCLASSPATH("net/minecraft/client/renderer/ActiveRenderInfo");

struct ActiveRenderInfo : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_STATIC_FIELD("PROJECTION", "Ljava/nio/FloatBuffer;");
		GET_STATIC_FIELD("MODELVIEW", "Ljava/nio/FloatBuffer;");
	}

	STRUCTORS();
};

#undef ActiveRenderInfo