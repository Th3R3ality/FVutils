#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME IChatComponent

SETCLASSPATH("net/minecraft/util/IChatComponent");

struct IChatComponent : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );

		GET_METHOD( "getFormattedText", "()Ljava/lang/String;" );
		GET_METHOD( "getUnformattedText", "()Ljava/lang/String;" );

	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME