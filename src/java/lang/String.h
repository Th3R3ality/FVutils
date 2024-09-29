#pragma once
#include "../../minecraft/IClass.h"

#include <string>

#define CURRENTCLASSNAME String

SETCLASSPATH( "java/lang/String" );

struct String : IClass
{
	using IClass::IClass;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	std::string ToString()
	{
		jstring jStr = (jstring)this->instance;
		const char* nativeStr = java::env->GetStringUTFChars(jStr, nullptr);
		std::string ret = std::string(nativeStr);
		java::env->ReleaseStringUTFChars(jStr, nativeStr);
		return ret;
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME