#pragma once
#include "IClass.h"

#define CURRENTCLASSNAME Render

SETCLASSPATH( "net/minecraft/client/renderer/entity/Render" );

struct Render : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "renderLivingLabel", "(Lnet/minecraft/entity/Entity;Ljava/lang/String;DDDI)V" );
		GET_METHOD( "renderOffsetLivingLabel", "(Lnet/minecraft/entity/Entity;DDDLjava/lang/String;FD)V" );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME