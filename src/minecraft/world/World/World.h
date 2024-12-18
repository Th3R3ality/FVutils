#pragma once
#include <IClass.h>

#include <vector>

#include "../../../java/util/List.h"
#include "../../entity/EntityPlayer/EntityPlayer.h"
#include "../../profiler/Profiler/Profiler.h"

#define CURRENTCLASSNAME World

_SETCLASSPATH( "net/minecraft/world", "World", "adm");

struct World : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		_GET_FIELD( "theProfiler",	"field_72984_F",	"B",	"Lnet/minecraft/profiler/Profiler;");

		_GET_FIELD( "playerEntities",	"field_73010_i",	"j",	"Ljava/util/List;" );
	}

	STRUCTORS();

	Profiler theProfiler(bool noderef = false)
	{
		if ( noDeref )
		{
			Profiler ret = TLSENV->GetObjectField( instance, World::fieldIDs[ "theProfiler" ] );;
			ret.noDeref = true;
			return ret;
		}
		else
			return TLSENV->GetObjectField( instance, World::fieldIDs[ "theProfiler" ] );
	}

	void playerEntities(std::vector<EntityPlayer>& out)
	{
		JNIEnv* env = TLSENV;

		List playerList = env->GetObjectField( this->instance, World::fieldIDs[ "playerEntities" ] );
		jobjectArray playerArray = playerList.toArray();
		if ( playerArray == nullptr ) return;

		jsize length = TLSENV->GetArrayLength( playerArray );
		out.reserve(length);

		for ( jsize idx = 0; idx < length; idx++ )
		{
			jobject playerObject = TLSENV->GetObjectArrayElement( playerArray, idx );
			if ( playerObject )
			{
				EntityPlayer ep = playerObject;
				ep.noDeref = true;
				out.emplace_back( ep );
			}
		}

		TLSENV->DeleteLocalRef( playerArray );
	}

};

#undef CURRENTCLASSNAME