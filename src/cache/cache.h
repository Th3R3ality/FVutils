#pragma once
#include "../minecraft/world/World/World.h"

#include <mutex>

namespace cache
{
	inline std::mutex dataMutex;

	struct PlayerData
	{
		PlayerData() = default;

		PlayerData( EntityPlayer player )
		{
			auto Str = player.getName();
			
			this->name = Str.ToString();
			//this->name = player.getName().ToString();
		}

		std::string name = "";
	};

	struct CacheData
	{
		std::vector<PlayerData> players;

	};
	inline CacheData data = {};

	void UpdateCache();
}