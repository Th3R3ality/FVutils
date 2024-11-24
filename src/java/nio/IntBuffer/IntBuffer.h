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
		return java::env->CallIntMethod( this->instance, IntBuffer::methodIDs[ "get" ], index );
	}

	ivec4 GetInt4()
	{
		return ivec4{
			this->Get( 0 ),
			this->Get( 1 ),
			this->Get( 2 ),
			this->Get( 3 )
		};
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME