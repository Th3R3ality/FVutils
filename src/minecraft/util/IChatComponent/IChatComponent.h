#pragma once
#include <IClass.h>
#include "../../../java/lang/String.h"

#define CURRENTCLASSNAME IChatComponent

SETCLASSPATH( "net/minecraft/util/IChatComponent" );

struct IChatComponent : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "getFormattedText", "()Ljava/lang/String;" );
		GET_METHOD( "getUnformattedText", "()Ljava/lang/String;" );

	}

	String getFormattedText()
	{
		return java::env->CallObjectMethod( instance, IChatComponent::methodIDs[ "getFormattedText" ] );

	}
	String getUnformattedText()
	{
		return java::env->CallObjectMethod( instance, IChatComponent::methodIDs[ "getUnformattedText" ] );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME