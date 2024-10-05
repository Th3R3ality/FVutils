#pragma once

#include <IClass.h>
#include "String.h"

#define CURRENTCLASSNAME Class

SETCLASSPATH( "java/lang/Class" );

struct Class : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();
		GET_METHOD( "getName", "()Ljava/lang/String;" );
	}

	String getName(JNIEnv* env = java::env)
	{
		return env->CallObjectMethod( instance, Class::methodIDs[ "getName" ] );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME