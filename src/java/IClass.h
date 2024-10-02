#pragma once
#include <jni.h>

#include <string>
#include <map>

#include <java.h>

#define STATICS() \
static std::map<std::string, jmethodID> methodIDs; \
static std::map<std::string, jfieldID> fieldIDs; \
static jclass klass; \
static bool initialised; \
static const char* klassPath; \

#define STRUCTORS( )\
CURRENTCLASSNAME() = default; \
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
{	if ( instance && !this->noDeref ) java::env->DeleteLocalRef( instance ); }

//
//

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

#define GET_METHOD(name, sig) \
CURRENTCLASSNAME :: methodIDs[ name ] = java::env->GetMethodID( CURRENTCLASSNAME :: klass, name, sig ); \
printf("  Method ["##name##"]: %p\n", CURRENTCLASSNAME :: methodIDs[ name ]);

#define GET_STATIC_METHOD(name, sig) \
CURRENTCLASSNAME :: methodIDs[ name ] = java::env->GetStaticMethodID( CURRENTCLASSNAME :: klass, name, sig ); \
printf("  Static Method ["##name##"]: %p\n", CURRENTCLASSNAME :: methodIDs[ name ]);

#define GET_FIELD(name, sig) \
CURRENTCLASSNAME :: fieldIDs[ name ] = java::env->GetFieldID( CURRENTCLASSNAME :: klass, name, sig ); \
printf("  Field ["##name##"]: %p\n", CURRENTCLASSNAME :: fieldIDs[ name ]);

#define GET_STATIC_FIELD(name, sig) \
CURRENTCLASSNAME :: fieldIDs[ name ] = java::env->GetStaticFieldID( CURRENTCLASSNAME :: klass, name, sig ); \
printf("  Static Field ["##name##"]: %p\n", CURRENTCLASSNAME :: fieldIDs[ name ]);


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
	bool noDeref = false;

	static void Initialise() {}

	IClass() = default;
	IClass( INITIALISER_TYPE )
	{
		java::classInitialisers.push_back( &Initialise );
	} IClass( jobject _instance )
	{
		instance = _instance;
	} ~IClass()
	{
		if ( instance && !noDeref ) java::env->DeleteLocalRef( instance );
	}
	void Deref()
	{
		if ( instance ) java::env->DeleteLocalRef( instance );
	}
};