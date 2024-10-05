#pragma once
#include <jni.h>
#include "IClass.h"
#include "../../../java/lang/String.h"
#include "../../util/IChatComponent/IChatComponent.h"
#include "../../../util/math/vec.h"

#define CURRENTCLASSNAME Entity

SETCLASSPATH( "net/minecraft/entity/Entity" );

struct Entity : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "getName", "()Ljava/lang/String;" );
		GET_METHOD( "getDisplayName", "()Lnet/minecraft/util/IChatComponent;" );
		GET_METHOD( "isSneaking", "()Z" );

		GET_FIELD( "posX", "D" );
		GET_FIELD( "posY", "D" );
		GET_FIELD( "posZ", "D" );
		GET_FIELD( "lastTickPosX", "D" );
		GET_FIELD( "lastTickPosY", "D" );
		GET_FIELD( "lastTickPosZ", "D" );
		GET_FIELD( "width", "F" );
		GET_FIELD( "height", "F" );
		GET_FIELD( "distanceWalkedModified", "F" );
		GET_FIELD( "prevDistanceWalkedModified", "F" );
		GET_FIELD( "rotationYaw", "F" );
		GET_FIELD( "rotationPitch", "F" );
		GET_FIELD( "prevRotationYaw", "F" );
		GET_FIELD( "prevRotationPitch", "F" );
		GET_FIELD( "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;" );
	}

	String getName()
	{
		return java::env->CallObjectMethod( this->instance, Entity::methodIDs[ "getName" ] );
	}
	String getDisplayName()
	{
		return IChatComponent(java::env->CallObjectMethod( this->instance, Entity::methodIDs[ "getDisplayName" ] )).getUnformattedText();
	}

	fvec3 GetPos()
	{
		return fvec3{
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["posX"]),
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["posY"]),
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["posZ"])
		};
	}

	float GetHeight()
	{
		return java::env->GetFloatField(this->instance, Entity::fieldIDs["height"]);
	}

	fvec3 GetEyePos()
	{
		fvec3 pos = GetPos();
		pos.y += this->GetHeight() * 0.85f;
		return pos;
	}

	fvec3 GetLastTickPos()
	{
		return fvec3{
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["lastTickPosX"]),
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["lastTickPosY"]),
			(float)java::env->GetDoubleField(this->instance, Entity::fieldIDs["lastTickPosZ"])
		};
	}


	STRUCTORS();
};

#undef CURRENTCLASSNAME