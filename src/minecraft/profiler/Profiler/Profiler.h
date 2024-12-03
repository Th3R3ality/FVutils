#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME Profiler

_SETCLASSPATH( "net/minecraft/profiler", "Profiler", "nt");

struct Profiler : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		_GET_METHOD( "startSection", "func_76320_a", "a", "(Ljava/lang/String;)V" );
		_GET_METHOD( "endSection", "func_76319_b", "b", "()V" );
		_GET_METHOD( "endStartSection", "func_76318_c", "c", "(Ljava/lang/String;)V" );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME