#include "java.h"

namespace java
{
	jobject classLoader;
	jmethodID mid_findClass;

	void java::Init()
	{

		if ( ( java::envTlsIndex = TlsAlloc() ) == TLS_OUT_OF_INDEXES )
		{
			printf("TlsAlloc failed"); 
			return;
		}

		// Check if there is any Java VMs in the injected thread
		jsize count;
		if ( JNI_GetCreatedJavaVMs( &jvm, 1, &count ) != JNI_OK || count == 0 )
			return;


		jint res = jvm->GetEnv( ( void** )&env, JNI_VERSION_1_8 );

		if ( res == JNI_EDETACHED )
			res = jvm->AttachCurrentThread( ( void** )&env, nullptr );

		if ( res != JNI_OK )
			return;

		if ( env == nullptr )
			jvm->DestroyJavaVM();

		if ( !TlsSetValue( java::envTlsIndex, env ) )
		{
			printf( "TlsSetValue error" );
			return;
		}

		jvm->GetEnv( ( void** )&tienv, JVMTI_VERSION );




		jclass c_Thread = env->FindClass( "java/lang/Thread" );
		jclass c_Map = env->FindClass( "java/util/Map" );
		jclass c_Set = env->FindClass( "java/util/Set" );
		jclass c_ClassLoader = env->FindClass( "java/lang/ClassLoader" );

		jmethodID mid_getAllStackTraces = env->GetStaticMethodID( c_Thread, "getAllStackTraces", "()Ljava/util/Map;" );
		jmethodID mid_keySet = env->GetMethodID( c_Map, "keySet", "()Ljava/util/Set;" );
		jmethodID mid_toArray = env->GetMethodID( c_Set, "toArray", "()[Ljava/lang/Object;" );
		jmethodID mid_getContextClassLoader = env->GetMethodID( c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;" );
		mid_findClass = env->GetMethodID( c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;" );
		jmethodID mid_currentThread = env->GetStaticMethodID( c_Thread, "currentThread", "()Ljava/lang/Thread;" );

		jobject obj_stackTracesMap = env->CallStaticObjectMethod( c_Thread, mid_getAllStackTraces );
		jobject obj_threadsSet = env->CallObjectMethod( obj_stackTracesMap, mid_keySet );

		jobjectArray threads = ( jobjectArray )env->CallObjectMethod( obj_threadsSet, mid_toArray );
		jint szThreads = env->GetArrayLength( threads );

		for ( int i = 0; i < szThreads; i++ )
		{
			jobject thread = env->GetObjectArrayElement( threads, i );
			jobject classLoaderObj = env->CallObjectMethod( thread, mid_getContextClassLoader );

			if ( classLoaderObj )
			{

				jstring className = env->NewStringUTF( "net/minecraft/client/Minecraft" );
				jobject minecraftClass = env->CallObjectMethod( classLoaderObj, mid_findClass, className );

				if ( minecraftClass )
				{
					classLoader = classLoaderObj;

					env->DeleteLocalRef( minecraftClass );

					break;
				}
			}

			env->DeleteLocalRef( thread );
		}

		env->DeleteLocalRef( threads );
		env->DeleteLocalRef( obj_stackTracesMap );
		env->DeleteLocalRef( obj_threadsSet );
		env->DeleteLocalRef( c_Thread );
		env->DeleteLocalRef( c_Map );
		env->DeleteLocalRef( c_Set );
		env->DeleteLocalRef( c_ClassLoader );

		initialised = (classLoader != nullptr && mid_findClass != nullptr);

		if ( !initialised )
			return;

		for ( auto&& fn : classInitialisers )
		{
			fn();
		}
	}

	void Destroy()
	{
		jvm->DetachCurrentThread();

		TlsFree(java::envTlsIndex);
	}

	jclass FindClass( const char* klassPath )
	{
		jstring klassPath_ = TLSENV->NewStringUTF(klassPath);
		return (jclass)TLSENV->CallObjectMethod(classLoader, mid_findClass, klassPath_);
	}

	void TestTLS()
	{
		LPVOID lpvData;

		// Retrieve a data pointer for the current thread.
		lpvData = TlsGetValue(envTlsIndex); 
		if ( ( lpvData == 0 ) && ( GetLastError() != ERROR_SUCCESS ) )
		{
			printf( "ERROR TlsGetValue\n" );
			return;
		}

		// Use the data stored for the current thread. 
		printf("common: thread %d: lpvData=%lx\n", GetCurrentThreadId(), lpvData); 
	}
}
