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

		_GET_METHOD("renderEntitySimple",	"func_147937_a",	"a",	"(Lnet/minecraft/entity/Entity;F)Z");

		GET_FIELD("renderPosX", "D");
		GET_FIELD("renderPosY", "D");
		GET_FIELD("renderPosZ", "D");
		
		GET_FIELD("viewerPosX", "D");
		GET_FIELD("viewerPosY", "D");
		GET_FIELD("viewerPosZ", "D");
	}

	jboolean renderEntitySimple( /*Entity*/jobject entityIn, jfloat partialTicks )
	{
		return TLSENV->CallBooleanMethod( instance, RenderManager::methodIDs[ "renderEntitySimple" ], entityIn, partialTicks );
	}


	fvec3 RenderPos()
	{
		return fvec3{
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["renderPosX"]),
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["renderPosY"]),
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["renderPosZ"])
		};
	}

	fvec3 ViewerPos()
	{
		return fvec3{
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosX"]),
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosY"]),
			(float)TLSENV->GetDoubleField(instance, RenderManager::fieldIDs["viewerPosZ"])
		};
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME