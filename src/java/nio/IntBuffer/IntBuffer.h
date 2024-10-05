#pragma once

#include <IClass.h>
#include "../../../util/math/vec.h"

#define CURRENTCLASSNAME IntBuffer

SETCLASSPATH( "java/nio/IntBuffer" );

struct IntBuffer : public IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_METHOD( "get", "(I)I" );
	}

	int Get( int index )
	{
		return java::env->CallFloatMethod( this->instance, IntBuffer::methodIDs[ "get" ], index );
	}

	ivec4 GetInt4()
	{
		return ivec4{
			java::env->CallIntMethod( this->instance, IntBuffer::methodIDs[ "get" ], 0 ),
			java::env->CallIntMethod( this->instance, IntBuffer::methodIDs[ "get" ], 1 ),
			java::env->CallIntMethod( this->instance, IntBuffer::methodIDs[ "get" ], 2 ),
			java::env->CallIntMethod( this->instance, IntBuffer::methodIDs[ "get" ], 3 )
		};
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME