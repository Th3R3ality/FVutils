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
		jboolean isCopy;
		const char* nativeStr = TLSENV->GetStringUTFChars((jstring)this->instance, &isCopy);
		std::string ret = std::string(nativeStr);
		if ( nativeStr == nullptr )
		{
			printf( "Native Str NULL\n" );
			return ret;
		}
		TLSENV->ReleaseStringUTFChars((jstring)this->instance, nativeStr);
		return ret;
	}

	STRUCTORS();
};

#undef CURRENTCLASSNAME