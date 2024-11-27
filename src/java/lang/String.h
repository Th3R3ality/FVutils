#pragma once
#include "IClass.h"

#include <string>

#define CURRENTCLASSNAME String

SETCLASSPATH( "java/lang/String" );

struct String : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

	}

	std::string ToString()
	{
		if ( this->instance == nullptr )
			return "ERROR < ToString > NO INSTANCE SET";
		jstring jStr = (jstring)this->instance;
		const char* nativeStr = TLSENV->GetStringUTFChars(jStr, nullptr);
		std::string ret = std::string(nativeStr);
		TLSENV->ReleaseStringUTFChars(jStr, nativeStr);
		return ret;
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME