#pragma once
#include "../../IClass.h"

#include <vector>

#include "../../../java/util/List.h"
#include "../../entity/EntityPlayer/EntityPlayer.h"

#define CURRENTCLASSNAME World

SETCLASSPATH( "net/minecraft/world/World" );

struct CURRENTCLASSNAME : IClass
{
	using IClass::IClass;

	STATICS();

	static void Initialise()
	{
		INITIALISER_HEADER();

		GET_FIELD( "playerEntities", "Ljava/util/List;" );
	}

	std::vector<EntityPlayer> playerEntities()
	{
		List playerList = List( java::env->GetObjectField( instance, fieldIDs[ "playerEntities" ] ) );
		jobjectArray playerArray = playerList.toArray();

		std::vector<EntityPlayer> out;

		jsize length = java::env->GetArrayLength( playerArray );
		for ( jsize idx = 0; idx < length; idx++ )
		{
			EntityPlayer player = EntityPlayer( java::env->GetObjectArrayElement( playerArray, idx ) );

			if ( player.instance )
				out.emplace_back( player );
		}

		java::env->DeleteLocalRef( playerArray );

		return out;
	}

	STRUCTORS();
};


#undef CURRENTCLASSNAME