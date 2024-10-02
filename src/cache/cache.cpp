#include "cache.h"
#include "../minecraft/minecraft.h"

#include <iostream>
#include <mutex>
#include <string>

namespace cache
{
	void UpdateCache()
	{
		std::lock_guard<std::mutex> guard( dataMutex );

		std::vector<EntityPlayer> playerEntities;
		minecraft::world->playerEntities(playerEntities);

		int size = playerEntities.size();
		data.players.resize( size );

		for ( jint idx = 0; idx < size; idx++ )
		{
			cache::data.players.at(idx) = PlayerData(playerEntities.at( idx ));
		}
	}
}
