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
		List playerList = java::env->GetObjectField( instance, World::fieldIDs[ "playerEntities" ] );
		jobjectArray playerArray = playerList.toArray();
		if ( playerArray == nullptr ) return;

		jsize length = java::env->GetArrayLength( playerArray );
		out.reserve(length);

		for ( jsize idx = 0; idx < length; idx++ )
		{
			EntityPlayer player = java::env->GetObjectArrayElement( playerArray, idx );
			if ( player.instance )
			{
				out.emplace_back( player );
			}
			player.noDeref = true;
		}

		java::env->DeleteLocalRef( playerArray );
	}

};

#undef CURRENTCLASSNAME