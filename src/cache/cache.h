#pragma once
#include "../minecraft/world/World/World.h"

namespace cache
{
	struct PlayerData
	{
		PlayerData( EntityPlayer player )
		{
			this->name = player.getName().ToString();
		}

		std::string name;
	};
	inline std::vector<PlayerData> players;

	void UpdateCache();
}