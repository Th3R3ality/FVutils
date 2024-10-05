#pragma once

#include <IClass.h>
#include "../../../../../util/math/vec.h"

#define CURRENTCLASSNAME RenderManager

SETCLASSPATH( "net/minecraft/client/renderer/entity/RenderManager" );

struct RenderManager : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD("renderPosX", "D");
		GET_FIELD("renderPosY", "D");
		GET_FIELD("renderPosZ", "D");
		
		GET_FIELD("viewerPosX", "D");
		GET_FIELD("viewerPosY", "D");
		GET_FIELD("viewerPosZ", "D");
	}

	fvec3 RenderPos()
	{
		return fvec3{
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["renderPosX"]),
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["renderPosY"]),
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["renderPosZ"])
		};
	}

	fvec3 ViewerPos()
	{
		return fvec3{
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosX"]),
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosY"]),
			(float)java::env->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosZ"])
		};
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME