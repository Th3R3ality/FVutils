#pragma once
#include <IClass.h>

#include <vector>

#include "../../../java/util/List.h"
#include "../../entity/EntityPlayer/EntityPlayer.h"

#define CURRENTCLASSNAME World

SETCLASSPATH( "net/minecraft/world/World" );

struct World : IClass
{
	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD( "playerEntities", "Ljava/util/List;" );
	}

	STRUCTORS();

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
				out.push_back( playerObject );
			}
		}

		TLSENV->DeleteLocalRef( playerArray );
	}

};

#undef CURRENTCLASSNAME