#pragma once
#include "../minecraft/world/World/World.h"

#include <mutex>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace cache
{
	inline std::mutex dataMutex;

	struct PlayerData
	{
		PlayerData() = default;
		PlayerData( int i )
		{

		};

		PlayerData( EntityPlayer& player )
		{
			std::string str = player.getDisplayName().ToString();


			const char hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
			std::string result = "";

			for( int i = 0; i < str.length(); ++i )
			{
				const char byte = str.at(i);

				result += hex_chars[ ( byte & 0xF0 ) >> 4 ];
				result += hex_chars[ ( byte & 0x0F ) >> 0 ];
				result += " ";
			}


			//std::stringstream ss;
			//ss << std::hex << std::setfill( '0' );
			//for ( int i = 0; i < str.length(); i++ )
			//{
			//	ss << std::setw( 2 ) << static_cast< unsigned >(str.at(i));
			//}

			str = str + ": " + result + "\n";

			this->name = str;
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