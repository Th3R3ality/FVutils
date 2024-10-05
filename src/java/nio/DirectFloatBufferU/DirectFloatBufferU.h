#pragma once

#include "../FloatBuffer/FloatBuffer.h"

#define CURRENTCLASSNAME DirectFloatBufferU

SETCLASSPATH( "java/nio/DirectFloatBufferU" );

struct DirectFloatBufferU : public FloatBuffer
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME