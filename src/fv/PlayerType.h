#pragma once
#include <string>
#include "../imgui/imgui.h"
#include "../util/Color.h"

namespace fv
{

	enum class PlayerTypeEnum
	{
		normal,
		pvagt,
		cvagt,
		bvagt,
		avagt,
		officer,
		vice,
		inspektor,
		direktor
	};
	enum class PlayerRankEnum
	{
		none,
		madchem,
		legend,
		titan
	};

	struct PlayerType
	{
		PlayerRankEnum rank = PlayerRankEnum::none;
		PlayerTypeEnum type = PlayerTypeEnum::normal;

		PlayerType() = default;

		PlayerType( std::string displayName )
		{
			int rankCharOffset = 0;
			do // check titan
			{
				bool isTitan = true;
				const char TITAN[] = "\xC2\xA7\x62\xE2\xAD\x90";
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
					rankCharOffset = sizeof( TITAN );
					rank = PlayerRankEnum::titan;
					break;
				}
			} while ( false );


			do // A-Vagt
			{
				bool typeFound = true;
				const char AVAGT[] = "\xC2\xA7\x61";

				for ( int i = 0; i  < sizeof( AVAGT ) - 1; i++ )
				{
					if ( displayName.size() <= i || displayName.c_str()[ i ] != AVAGT[ i ] )
					{
						typeFound = false;
						break;
					}
				}
				if ( typeFound )
				{
					type = PlayerTypeEnum::avagt;
					break;
				}

			} while ( false );
		}

		PlayerRankEnum GetRank()
		{
			return rank;
		}
		PlayerTypeEnum GetType()
		{
			return type;
		}
		std::string GetTypeString()
		{
			switch ( type )
			{
			case PlayerTypeEnum::normal:
				return std::string( "Normal" );
			case PlayerTypeEnum::pvagt:
				return std::string("P-Vagt");
			case PlayerTypeEnum::cvagt:
				return std::string("C-Vagt");
			case PlayerTypeEnum::bvagt:
				return std::string("B-Vagt");
			case PlayerTypeEnum::avagt:
				return std::string("A-Vagt");
			case PlayerTypeEnum::officer:
				return std::string("Officer");
			case PlayerTypeEnum::vice:
				return std::string("Vice-Inspektor");
			case PlayerTypeEnum::inspektor:
				return std::string("Inspektor");
			case PlayerTypeEnum::direktor:
				return std::string("Direktor");
			default:
				return std::string( "error" );
			}
		}

		std::string GetRankString()
		{
			switch ( rank )
			{
			case PlayerRankEnum::none:
				return std::string( "Ingen" );
			case PlayerRankEnum::madchem:
				return std::string( "Mad Chemist" );
			case PlayerRankEnum::legend:
				return std::string( "Legend" );
			case PlayerRankEnum::titan:
				return std::string( "Titan" );

			default:
				return std::string( "error" );
			}
		}

		Color GetTypeColor()
		{
			switch ( type )
			{
			case PlayerTypeEnum::normal:
				return { 1.f, 1.f, 1.f };
			case PlayerTypeEnum::pvagt:
				return {};
			case PlayerTypeEnum::cvagt:
				return {};
			case PlayerTypeEnum::bvagt:
				return {};
			case PlayerTypeEnum::avagt:
				return {};
			case PlayerTypeEnum::officer:
				return {};
			case PlayerTypeEnum::vice:
				return {};
			case PlayerTypeEnum::inspektor:
				return {};
			case PlayerTypeEnum::direktor:
				return {};
			default:
				return { 0.f, 0.f, 0.f };
			}
		}
		Color GetRankColor()
		{
			switch ( rank )
			{
			case PlayerRankEnum::none:
				return { 1.f, 1.f, 1.f };
			case PlayerRankEnum::titan:
				return {0.7f, 1.f, 1.f };
			default:
				return { 0.f, 0.f, 0.f };
			}
		}


	};

	bool IsBotByName( std::string name );
}