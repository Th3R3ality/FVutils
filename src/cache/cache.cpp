#include "cache.h"
#include "../minecraft/minecraft.h"

#include <mutex>
#include <string>

namespace cache
{
	void UpdateCache()
	{
		//std::lock_guard<std::mutex> guard( dataMutex );

		//auto playerEntities = minecraft::world->playerEntities();

		//int size = playerEntities.size();
		//data.players.resize( size );


		
		auto list = minecraft::world->playerEntities();
		for ( auto&& ep : list )
		{
			printf( "instance: %p\n", ep.instance );
			jobject obj_name = java::env->CallObjectMethod( ep.instance, Entity::methodIDs[ "getName" ] );
			printf( "   obj_name: %p\n", obj_name );
			if ( obj_name == nullptr )
				continue;

			jstring jStr = ( jstring )obj_name;
			const char* nativeStr = java::env->GetStringUTFChars( jStr, nullptr );
			printf( "   nativeStr: %p\n", nativeStr );
			java::env->ReleaseStringUTFChars( jStr, nativeStr );

			printf( "final: %s\n", std::string( nativeStr ).c_str() );

		}
		


		jobject playerEntitiesList = java::env->GetObjectField( minecraft::world->instance, World::fieldIDs[ "playerEntities" ] );
		printf( "playerEntitiesList: %p\n", playerEntitiesList );

		//jobjectArray playerEntities = ( jobjectArray )java::env->CallObjectMethod( playerEntitiesList, List::methodIDs[ "toArray" ] );
		jobjectArray playerEntities = List(playerEntitiesList).toArray();
		printf( "playerEntities: %p\n", playerEntities );

		int size = java::env->GetArrayLength( playerEntities );
		printf( "size: %i\n", size );

		for ( int i = 0; i < size; i++ )
		{
			jobject obj_player = java::env->GetObjectArrayElement( playerEntities, i );
			printf( "   obj_player: %p\n", obj_player );
			printf( "   list_player: %p\n", list.at( i ).instance );
			if ( !obj_player ) continue;

			jobject obj_name = java::env->CallObjectMethod( obj_player, Entity::methodIDs[ "getName" ] );
			printf( "   obj_name: %p\n", obj_name );

			jstring jStr = ( jstring )obj_name;
			const char* nativeStr = java::env->GetStringUTFChars( jStr, nullptr );
			printf( "   nativeStr: %p\n", nativeStr );
			java::env->ReleaseStringUTFChars( jStr, nativeStr );

			printf( "final: %s\n", std::string( nativeStr ).c_str() );
		}

		//java::env->DeleteLocalRef( playerEntitiesList );
		java::env->DeleteLocalRef( playerEntities );
	}
}
