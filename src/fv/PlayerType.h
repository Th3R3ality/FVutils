#pragma once
#include <string>
#include "../cache/cache.h"

namespace fv
{
	enum class PlayerType
	{
		normal,
		titan,
		vagt,
		officer,
		direktor,
		vice,
		inspektor
	};

	inline PlayerType GetPlayerType( std::string displayName )
	{
		bool isTitan = true;
		const char TITAN[] = "\xC2\xA7\x62\xE2\xAD\x90";
		int idx = 0;
		for ( int i = 0; i < sizeof(TITAN) - 1; i++ )
		{
			if ( displayName.size() <= i || displayName.c_str()[i] != TITAN[ i ] )
			{
				isTitan = false;
				break;
			}
		}
		if ( isTitan ) return PlayerType::titan;



		return PlayerType::normal;
	}
}