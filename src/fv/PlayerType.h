#pragma once
#include <string>
#include "../cache/cache.h"

namespace fv
{
	enum class PlayerTypeEnum
	{
		normal,
		titan,
		vagt,
		officer,
		direktor,
		vice,
		inspektor
	};
	struct PlayerType
	{
		PlayerTypeEnum id;
	};

	inline PlayerType GetPlayerType( std::string displayName )
	{
		PlayerType out;

		do // get player type
		{
			bool isTitan = true;
			const char TITAN[] = "\xC2\xA7\x62\xE2\xAD\x90";
			int idx = 0;
			for ( int i = 0; i < sizeof( TITAN ) - 1; i++ )
			{
				if ( displayName.size() <= i || displayName.c_str()[ i ] != TITAN[ i ] )
				{
					isTitan = false;
					break;
				}
			}
			if ( isTitan )
			{
				out.id = PlayerTypeEnum::titan;
				break;
			}
		} while ( false );


		return out;
	}
}