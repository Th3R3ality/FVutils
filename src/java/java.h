#pragma once
#include <jni.h>
#include <jvmti.h>
#include <vector>

namespace java
{
	inline JavaVM* jvm = nullptr;
	inline JNIEnv* env = nullptr;
	inline jvmtiEnv* tienv = nullptr;
	inline bool initialised = false;

	inline std::vector <void( * )( )> classInitialisers;

	void Init();
	void Destroy();

	jclass FindClass( const char* klassPath );
}