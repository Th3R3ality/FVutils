#pragma once
#include "../minecraft/world/World/World.h"

#include <mutex>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "../fv/PlayerType.h"
#include "../util/math/vec.h"

namespace cache
{
	inline std::mutex dataMutex;

	struct PlayerData
	{
		PlayerData() = default;
		PlayerData( int i ){};

		std::string name = "";
		fv::PlayerType type = fv::PlayerType::normal;
		fvec3 pos = { 0.f };
		fvec3 lastTickPos = { 0.f };
		float health = 0;
		float maxHealth = 0;

		PlayerData( EntityPlayer& player )
		{
			std::string str = player.getDisplayName().ToString();

			type = fv::GetPlayerType( str );
			pos = player.GetPos();
			lastTickPos = player.GetLastTickPos();
			health = player.getHealth();
			maxHealth = player.getMaxHealth();

			const char hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
			std::string result = "";

			for( int i = 0; i < str.length(); ++i )
			{
				const char byte = str.at(i);

				result += hex_chars[ ( byte & 0xF0 ) >> 4 ];
				result += hex_chars[ ( byte & 0x0F ) >> 0 ];
				result += " ";
			}

			str = str + ": " + result + "\n";

			this->name = str;

			
		}
	};

	struct CacheData
	{
		std::vector<PlayerData> players;
		float renderPartialTicks;
		matrix modelView;
		matrix projection;
		ivec4 viewport;
		
	};
	inline CacheData data = {};

	void UpdateCache();
}