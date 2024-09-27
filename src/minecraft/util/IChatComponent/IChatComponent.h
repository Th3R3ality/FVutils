#pragma once
#include "../../IClass.h"

#define CURRENTCLASSNAME IChatComponent

SETCLASSPATH("net/minecraft/util/IChatComponent");

struct CURRENTCLASSNAME : public IClass
{
	using IClass::IClass;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );

		METHOD( "getFormattedText", "()Ljava/lang/String;" );
		METHOD( "getUnformattedText", "()Ljava/lang/String;" );

	}

	STRUCTORS( );
};

#undef CURRENTCLASSNAME