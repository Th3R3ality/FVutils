#pragma once
#include "IClass.h"

#include "../../../gui/FontRenderer/FontRenderer.h"

#define CURRENTCLASSNAME Render

_SETCLASSPATH( "net/minecraft/client/renderer/entity", "Render", "biv");

struct Render : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		_GET_METHOD( "getFontRendererFromRenderManager",	"func_76983_a",		"c",	"()Lnet/minecraft/client/gui/FontRenderer;" );
		_GET_METHOD( "renderLivingLabel",					"func_147906_a",	"a",	"(Lnet/minecraft/entity/Entity;Ljava/lang/String;DDDI)V" );
		_GET_METHOD( "renderOffsetLivingLabel",				"func_177069_a",	"a",	"(Lnet/minecraft/entity/Entity;DDDLjava/lang/String;FD)V" );
	}

	FontRenderer getFontRendererFromRenderManager()
	{
		TLSENV->CallObjectMethod( this->instance, Render::methodIDs[ "getFontRendererFromRenderManager" ] );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME