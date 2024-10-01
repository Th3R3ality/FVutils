#pragma once
#include "../../IClass.h"

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

	std::vector<EntityPlayer> playerEntities()
	{
		std::vector<EntityPlayer> out;

		jobject playerList = java::env->GetObjectField( instance, fieldIDs[ "playerEntities" ] );
		jobjectArray playerArray = List(playerList).toArray();

		jsize length = java::env->GetArrayLength( playerArray );
		for ( jsize idx = 0; idx < length; idx++ )
		{
			EntityPlayer player = java::env->GetObjectArrayElement( playerArray, idx );

			if ( player.instance )
				out.push_back( player );
		}

		java::env->DeleteLocalRef( playerList );
		java::env->DeleteLocalRef( playerArray );

		return out;
	}

};

#undef CURRENTCLASSNAME