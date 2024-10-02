#pragma once
#include <IClass.h>

#define CURRENTCLASSNAME List

SETCLASSPATH( "java/util/List" );

struct List : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "toArray", "()[Ljava/lang/Object;" );
	}

	jobjectArray toArray()
	{
		return ( jobjectArray )java::env->CallObjectMethod( instance, methodIDs[ "toArray" ] );
	}

	STRUCTORS();
};


#undef CURRENTCLASSNAME