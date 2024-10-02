#pragma once

#include "../Render/Render.h"

#define CURRENTCLASSNAME RenderLivingEntity

SETCLASSPATH( "net/minecraft/client/renderer/entity/RendererLivingEntity" );

struct RenderLivingEntity : public Render
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD("renderName", "(Lnet/minecraft/entity/Entity;DDD)V");
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME