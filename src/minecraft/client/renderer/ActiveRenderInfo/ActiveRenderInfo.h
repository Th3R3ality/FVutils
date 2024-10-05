#pragma once
#include <IClass.h>

#include "../../../../util/math/vec.h"
#include "../../../../java/nio/FloatBuffer/FloatBuffer.h"
#include <lang/Class.h>

#include <iostream>

#define CURRENTCLASSNAME ActiveRenderInfo

SETCLASSPATH("net/minecraft/client/renderer/ActiveRenderInfo");

struct ActiveRenderInfo : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_STATIC_FIELD("PROJECTION", "Ljava/nio/FloatBuffer;");
		GET_STATIC_FIELD("MODELVIEW", "Ljava/nio/FloatBuffer;");
	}

	static matrix ProjectionMatrix()
	{
		jobject projection = java::env->GetStaticObjectField(ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs["PROJECTION"]);
		matrix m = FloatBuffer(projection).GetMatrix();
		//java::env->DeleteLocalRef(projection); // IClass derefs
		return m;
	}

	static matrix ModelViewMatrix()
	{
		jobject modelView = java::env->GetStaticObjectField(ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs["MODELVIEW"]);
		matrix m = FloatBuffer(modelView).GetMatrix();
		//java::env->DeleteLocalRef(modelView); // IClass derefs
		return m;
	}

	static ivec4 Viewport()
	{
		jobject viewport = java::env->GetStaticObjectField(ActiveRenderInfo::klass, ActiveRenderInfo::fieldIDs["MODELVIEW"]);

		//Class klass = java::env->GetObjectClass( modelView );
		//std::cout << klass.getName().ToString() << "\n";
		java::env->DeleteLocalRef(viewport); // IClass derefs
		return ivec4{};
	}

	STRUCTORS();
};

#undef ActiveRenderInfo