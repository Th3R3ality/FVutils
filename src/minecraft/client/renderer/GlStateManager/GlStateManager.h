#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME GlStateManager

_SETCLASSPATH( "net/minecraft/client/renderer", "GlStateManager", "bfl");

struct GlStateManager : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		//			enablePolygonOffset			func_179088_q		q		()V
		_GET_STATIC_METHOD( "enablePolygonOffset",		"func_179088_q",	"q",	"()V" );

		//			disablePolygonOffset		func_179113_r		r		()V
		_GET_STATIC_METHOD( "disablePolygonOffset",	"func_179113_r",	"r",	"()V" );

		//			doPolygonOffset				func_179136_a		a		(FF)V
		_GET_STATIC_METHOD( "doPolygonOffset",			"func_179136_a",	"a",	"(FF)V" );
	}

	static void enablePolygonOffset();
	static void disablePolygonOffset();
	static void doPolygonOffset( float factor, float units );


	STRUCTORS();
};

#undef CURRENTCLASSNAME