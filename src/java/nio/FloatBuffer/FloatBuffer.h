#pragma once

#include <array>

#include <IClass.h>
#include "../../../util/math/vec.h"

#define CURRENTCLASSNAME FloatBuffer

SETCLASSPATH( "java/nio/FloatBuffer" );

struct FloatBuffer : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD("get", "(I)F");
	}

	float Get(int index)
	{
		return java::env->CallFloatMethod( this->instance, FloatBuffer::methodIDs[ "get" ], index );
	}
	
	fvec4 GetFloat4()
	{
		return fvec4{
			java::env->CallFloatMethod( this->instance, FloatBuffer::methodIDs[ "get" ], 0 ),
			java::env->CallFloatMethod( this->instance, FloatBuffer::methodIDs[ "get" ], 1 ),
			java::env->CallFloatMethod( this->instance, FloatBuffer::methodIDs[ "get" ], 2 ),
			java::env->CallFloatMethod( this->instance, FloatBuffer::methodIDs[ "get" ], 3 )
		};
	}

	matrix GetMatrix()
	{
		std::array<float, 16> arr;
		for (int i = 0; i < 16; i++)
		{
			arr.at(i) = java::env->CallFloatMethod(this->instance, FloatBuffer::methodIDs["get"], i);
		}

		matrix m;

		m.m00 = arr[0];
		m.m01 = arr[1];
		m.m02 = arr[2];
		m.m03 = arr[3];
		m.m10 = arr[4];
		m.m11 = arr[5];
		m.m12 = arr[6];
		m.m13 = arr[7];
		m.m20 = arr[8];
		m.m21 = arr[9];
		m.m22 = arr[10];
		m.m23 = arr[11];
		m.m30 = arr[12];
		m.m31 = arr[13];
		m.m32 = arr[14];
		m.m33 = arr[15];

		return m;
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME