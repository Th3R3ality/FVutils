#include "cache.h"
#include "../minecraft/minecraft.h"

#include <mutex>
#include <string>

namespace cache
{
	void UpdateCache()
	{
		std::lock_guard<std::mutex> guard( dataMutex );

		auto playerEntities = minecraft::world->playerEntities();

		int size = playerEntities.size();
		data.players.resize( size );

		for ( jint idx = 0; idx < size; idx++ )
		{
			cache::data.players.at(idx) = playerEntities.at( idx );
		}
	}
}
