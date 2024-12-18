#pragma once

#include <IClass.h>

#define CURRENTCLASSNAME RenderGlobal

_SETCLASSPATH( "net/minecraft/client/renderer", "RenderGlobal", "bfr");

struct RenderGlobal : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		_GET_METHOD( "renderEntities",	"func_180446_a",	"a",	"(Lnet/minecraft/entity/Entity;Lnet/minecraft/client/renderer/culling/ICamera;F)V");
	

		//List<RenderGlobal.ContainerLocalRenderInformation> renderInfos
		//_GET_METHOD( "renderInfos", "field_72755_R", "m", "" );
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME