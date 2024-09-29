#pragma once
#include <jni.h>
#include "../../IClass.h"
#include "../../../java/lang/String.h"

#define CURRENTCLASSNAME Entity

SETCLASSPATH( "net/minecraft/entity/Entity" );

struct Entity : public IClass
{
	using IClass::IClass;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER( );

		GET_METHOD("getName", "()Ljava/lang/String;");
		GET_METHOD("isSneaking", "()Z");

		GET_FIELD("posX", "D");
		GET_FIELD("posY", "D");
		GET_FIELD("posZ", "D");
		GET_FIELD("lastTickPosX", "D");
		GET_FIELD("lastTickPosY", "D");
		GET_FIELD("lastTickPosZ", "D");
		GET_FIELD("width", "F");
		GET_FIELD("height", "F");
		GET_FIELD("distanceWalkedModified", "F");
		GET_FIELD("prevDistanceWalkedModified", "F");
		GET_FIELD("rotationYaw", "F");
		GET_FIELD("rotationPitch", "F");
		GET_FIELD("prevRotationYaw", "F");
		GET_FIELD("prevRotationPitch", "F");
		GET_FIELD("boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
	}

	String getName()
	{
		return String(java::env->CallObjectMethod(this->instance, Entity::methodIDs["getName"]));
	}

	STRUCTORS( );
};


#undef CURRENTCLASSNAME