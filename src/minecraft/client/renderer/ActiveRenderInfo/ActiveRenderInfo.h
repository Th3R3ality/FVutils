#pragma once
#include <IClass.h>

#include "../../../../util/math/vec.h"
#include "../../../../java/nio/FloatBuffer/FloatBuffer.h"
#include "../../../../java/nio/IntBuffer/IntBuffer.h"
#include <lang/Class.h>
#include "../../../util/Vec3/Vec3.h"

#include <iostream>

#define CURRENTCLASSNAME ActiveRenderInfo

SETCLASSPATH( "net/minecraft/client/renderer/ActiveRenderInfo" );

struct ActiveRenderInfo : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_STATIC_FIELD( "PROJECTION", "Ljava/nio/FloatBuffer;" );
		GET_STATIC_FIELD( "MODELVIEW", "Ljava/nio/FloatBuffer;" );
		GET_STATIC_FIELD( "VIEWPORT", "Ljava/nio/IntBuffer;" );

		GET_STATIC_METHOD( "getPosition", "()Lnet/minecraft/util/Vec3;" );
	}

	static std::array<double, 16> RawProjectionMatrix()
	{
		jobject matrix = java::env->GetStaticObjectField( ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs[ "PROJECTION" ] );
		
		std::vector<double> data = FloatBuffer( matrix ).GetFloatsAsDoubles( 16 );

		std::array<double, 16> out;
		std::copy_n( data.begin(), 16, out.begin() );

		return out;
	}

	static std::array<double, 16> RawModelViewMatrix()
	{
		jobject matrix = java::env->GetStaticObjectField( ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs[ "MODELVIEW" ] );
		
		std::vector<double> data = FloatBuffer( matrix ).GetFloatsAsDoubles( 16 );

		std::array<double, 16> out;
		std::copy_n( data.begin(), 16, out.begin() );

		return out;
	}

	static matrix ProjectionMatrix()
	{
		jobject projection = java::env->GetStaticObjectField( ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs[ "PROJECTION" ] );
		matrix m = FloatBuffer( projection ).GetMatrix();
		//java::env->DeleteLocalRef(projection); // IClass derefs
		return m;
	}

	static matrix ModelViewMatrix()
	{
		jobject modelView = java::env->GetStaticObjectField( ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs[ "MODELVIEW" ] );
		matrix m = FloatBuffer( modelView ).GetMatrix();
		//java::env->DeleteLocalRef(modelView); // IClass derefs
		return m;
	}

	static ivec4 Viewport()
	{
		jobject viewport = java::env->GetStaticObjectField( ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs[ "VIEWPORT" ] );

		ivec4 vec = IntBuffer( viewport ).GetInt4();

		return vec;
	}

	static fvec3 RenderPos()
	{
		jobject vec3 = java::env->CallStaticObjectMethod( ActiveRenderInfo::klass, ActiveRenderInfo::methodIDs[ "getPosition" ] );

		//Class klass = java::env->GetObjectClass(vec3);

		//std::cout << klass.getName().ToString() << "\n";

		return Vec3( vec3 ).fvec();
	}

	STRUCTORS();
};

#undef ActiveRenderInfo