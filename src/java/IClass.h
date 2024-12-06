#pragma once
#include <jni.h>

#include <string>
#include <map>

#include <java.h>
#include <cassert>

#include "../util/initialiser_type.h"

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
{	if ( instance && !this->noDeref ) TLSENV->DeleteLocalRef( instance ); }



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

#define _SETCLASSPATH(PKGname, SRGname, OBFname) \
SETCLASSPATH(PKGname ## "/" ## SRGname)

#define INITIALISER_HEADER() \
if ( CURRENTCLASSNAME :: initialised ) { return; } \
CURRENTCLASSNAME :: klass = java::FindClass( CURRENTCLASSNAME :: klassPath ); \
printf("Class [" EXPANDSTR(CURRENTCLASSNAME) "]: %p\n", CURRENTCLASSNAME :: klass);

#define GET_METHOD(MCPname, SRGdesc) \
CURRENTCLASSNAME :: methodIDs[ MCPname ] = TLSENV->GetMethodID( CURRENTCLASSNAME :: klass, MCPname, SRGdesc ); \
printf("  Method ["##MCPname##"]: %p\n", CURRENTCLASSNAME :: methodIDs[ MCPname ]);

#define _GET_METHOD(MCPname, SRGname, OBFname, SRGdesc) GET_METHOD(MCPname, SRGdesc)

#define GET_STATIC_METHOD(MCPname, SRGdesc) \
CURRENTCLASSNAME :: methodIDs[ MCPname ] = TLSENV->GetStaticMethodID( CURRENTCLASSNAME :: klass, MCPname, SRGdesc ); \
printf("  Static Method ["##MCPname##"]: %p\n", CURRENTCLASSNAME :: methodIDs[ MCPname ]);

#define _GET_STATIC_METHOD(MCPname, SRGname, OBFname, SRGdesc) GET_STATIC_METHOD(MCPname, SRGdesc)


#define GET_FIELD(MCPname, SRGdesc) \
CURRENTCLASSNAME :: fieldIDs[ MCPname ] = TLSENV->GetFieldID( CURRENTCLASSNAME :: klass, MCPname, SRGdesc ); \
printf("  Field ["##MCPname##"]: %p\n", CURRENTCLASSNAME :: fieldIDs[ MCPname ]);

#define _GET_FIELD(MCPname, SRGname, OBFname, SRGdesc) GET_FIELD(MCPname, SRGdesc)

#define GET_STATIC_FIELD(MCPname, SRGdesc) \
CURRENTCLASSNAME :: fieldIDs[ MCPname ] = TLSENV->GetStaticFieldID( CURRENTCLASSNAME :: klass, MCPname, SRGdesc ); \
printf("  Static Field ["##MCPname##"]: %p\n", CURRENTCLASSNAME :: fieldIDs[ MCPname ]);

#define _GET_STATIC_FIELD(MCPname, SRGname, OBFname, SRGdesc) GET_STATIC_FIELD(MCPname, SRGdesc)



struct IClass
{
	static std::map<std::string, jmethodID> methodIDs;
	static std::map<std::string, jfieldID> fieldIDs;
	static jclass klass;
	static bool initialised;
	static const char* klassPath;

	jobject instance = 0;
	bool noDeref = false;
	bool global = false;

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
		if ( instance && !noDeref ) this->Deref();
	}
	void MakeGlobal()
	{
		assert( instance );

		TLSENV->NewGlobalRef( instance );
		global = true;
	}
	void Deref()
	{
		assert( instance );

		if ( global )
			TLSENV->DeleteGlobalRef( instance );
		else
			TLSENV->DeleteLocalRef( instance );

	}
};