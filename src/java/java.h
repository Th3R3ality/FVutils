#pragma once
#include <jni.h>
#include <jvmti.h>
namespace java
{
	inline JavaVM* jvm = nullptr;
	inline JNIEnv* env = nullptr;
	inline jvmtiEnv* tienv = nullptr;
	inline bool initialised = false;

	void Init();
	void Destroy();

	jclass FindClass(const char* klassPath);
}