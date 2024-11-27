#pragma once
#include <jni.h>
#include <jvmti.h>
#include <vector>
#include <Windows.h>

namespace java
{
	inline JavaVM* jvm = nullptr;
	inline JNIEnv* env = nullptr;
	inline DWORD envTlsIndex = NULL;
	inline jvmtiEnv* tienv = nullptr;
	inline bool initialised = false;

#define TLSENV ( ( JNIEnv* )TlsGetValue( java::envTlsIndex ) )

	inline std::vector <void( * )( )> classInitialisers;

	void Init();
	void Destroy();

	jclass FindClass( const char* klassPath );

	void TestTLS();
}