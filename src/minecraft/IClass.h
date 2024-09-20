#pragma once
#include <jni.h>

#include <string>
#include <map>

#include "../java/java.h"

#define STRUCTORS( klassName )\
klassName( jobject _instance ) \
{ \
	instance = _instance; \
	klass = java::FindClass( klassPath ); \
} \
 \
~klassName() \
{ \
	java::env->DeleteLocalRef( klass ); \
	if ( instance ) \
		java::env->DeleteLocalRef( instance ); \
}

struct IClass
{
	std::map<std::string, jmethodID> methodIDs;
	std::map<std::string, jfieldID> fieldIDs;

	jobject instance = 0;
	jclass klass = 0;
	const char* klassPath = nullptr;

	IClass()
	{
		klass = java::FindClass( klassPath );
	}

	IClass( jobject _instance )
	{
		instance = _instance;
		klass = java::FindClass( klassPath );
	}

	~IClass()
	{
		java::env->DeleteLocalRef( klass );
		if ( instance )
			java::env->DeleteLocalRef( instance );
	}

	jclass GetClass()
	{
		return klass;
	}
};