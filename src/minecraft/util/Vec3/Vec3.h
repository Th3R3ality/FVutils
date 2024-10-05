#pragma once

#include <IClass.h>
#include "../../../util/math/vec.h"

#define CURRENTCLASSNAME Vec3

SETCLASSPATH( "net/minecraft/util/Vec3" );

struct Vec3 : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD( "xCoord", "D");
		GET_FIELD( "yCoord", "D");
		GET_FIELD( "zCoord", "D");
	}

	fvec3 fvec()
	{
		return fvec3{
			(float)java::env->GetDoubleField(instance, Vec3::fieldIDs["xCoord"]),
			(float)java::env->GetDoubleField(instance, Vec3::fieldIDs["yCoord"]),
			(float)java::env->GetDoubleField(instance, Vec3::fieldIDs["zCoord"])
		};
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME