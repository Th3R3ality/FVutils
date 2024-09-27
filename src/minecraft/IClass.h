#pragma once
#include <jni.h>

#include <string>
#include <map>

#include "../java/java.h"

#define STATICS() \
static std::map<std::string, jmethodID> methodIDs; \
static std::map<std::string, jfieldID> fieldIDs; \
static jclass klass; \
static bool initialised; \
static const char* klassPath; \

#define STRUCTORS( )\
CURRENTCLASSNAME ( INITIALISER_TYPE ) \
{ \
	java::classInitialisers.push_back(&Initialise); \
} \
CURRENTCLASSNAME ( jobject _instance ) \
{ \
	instance = _instance; \
} \
 \
~ CURRENTCLASSNAME () \
{ \
	if ( instance ) \
		java::env->DeleteLocalRef( instance ); \
}

#define EXPAND(x) x

#define MAKE_INITIALISER(_klassName) \
std::map<std::string, jmethodID> _klassName :: methodIDs = {}; \
std::map<std::string, jfieldID> _klassName :: fieldIDs = {}; \
const char* _klassName :: klassPath = EXPAND(_klassName) ## _klasspath ;\
jclass _klassName :: klass = 0; \
bool _klassName :: initialised = false; \
static _klassName EXPAND(_klassName) ## _initialiser_ = _klassName (INITIALISER_TYPE{});

#define STR(x) #x
#define EXPANDSTR(x) STR(x)

#define SETCLASSPATH(path) \
inline constexpr const char* EXPAND(CURRENTCLASSNAME)##_klasspath = path;

#define INITIALISER_HEADER() \
if ( CURRENTCLASSNAME :: initialised ) { return; } \
CURRENTCLASSNAME :: klass = java::FindClass( CURRENTCLASSNAME :: klassPath ); \
printf("Class [" EXPANDSTR(CURRENTCLASSNAME) "]: %p\n", CURRENTCLASSNAME :: klass);

#define METHOD(name, sig) \
CURRENTCLASSNAME :: methodIDs[ name ] = java::env->GetMethodID( CURRENTCLASSNAME :: klass, name, sig ); \
printf("  Method ["##name##"]: %p\n", CURRENTCLASSNAME :: methodIDs[ name ]);

struct INITIALISER_TYPE
{

};
struct IClass
{
	static std::map<std::string, jmethodID> methodIDs;
	static std::map<std::string, jfieldID> fieldIDs;
	static jclass klass;
	static bool initialised;
	static const char* klassPath;

	jobject instance = 0;


	IClass()
	{

	}
	static void Initialise() {}

	IClass( INITIALISER_TYPE )
	{
		java::classInitialisers.push_back( &Initialise );
	} IClass( jobject _instance )
	{
		instance = _instance;
	} ~IClass()
	{
		if ( instance ) java::env->DeleteLocalRef( instance );
	}


	//IClass( INITIALISER_TYPE )
	//{
	//	initialised = false;
	//	java::classInitialisers.push_back(&Initialise);
	//}


	//IClass( jobject _instance )
	//{
	//	instance = _instance;
	//}

	static jclass GetClass()
	{
		return IClass::klass;
	}
};