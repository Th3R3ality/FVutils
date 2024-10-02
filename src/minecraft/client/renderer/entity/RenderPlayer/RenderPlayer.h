#pragma once

#include "../RenderLivingEntity/RenderLivingEntity.h"

#define CURRENTCLASSNAME RenderPlayer

SETCLASSPATH( "net/minecraft/client/renderer/entity/RenderPlayer" );

struct RenderPlayer : public RenderLivingEntity
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "renderOffsetLivingLabel", "(Lnet/minecraft/client/entity/AbstractClientPlayer;DDDLjava/lang/String;FD)V" );
	}

	RenderPlayer() = default; RenderPlayer( INITIALISER_TYPE )
	{
		java::classInitialisers.push_back( &Initialise );
	} RenderPlayer( jobject _instance )
	{
		instance = _instance;
	} ~RenderPlayer()
	{
		if ( instance && !this->noDeref ) java::env->DeleteLocalRef( instance );
	};
};

#undef CURRENTCLASSNAME