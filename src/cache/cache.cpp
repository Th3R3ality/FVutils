#include "cache.h"
#include "../minecraft/minecraft.h"

namespace cache
{
	void UpdateCache()
	{
		auto playerEntities = minecraft::world->playerEntities();

		int size = playerEntities.size();
		players.resize( size, { 0 } );

		for ( int i = 0; i < size; i++ )
		{
			players.at( i ) = PlayerData( playerEntities.at( 1 ) );
		}
	}
}
