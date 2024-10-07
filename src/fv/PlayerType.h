#pragma once
#include <string>
#include "../cache/cache.h"
#include "../imgui/imgui.h"

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
	struct PlayerColor
	{
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;

		PlayerColor() = default;
		PlayerColor( float r, float g, float b, float a = 1.0f ) :
			r( r ), g( g ), b( b ), a( a )
		{};

		constexpr PlayerColor( const ImColor color ) { auto& col = color.Value; r = col.x; g = col.y; b = col.z; a = col.w; };
		operator ImColor() { return ImColor( r, g, b, a ); };
		operator ImVec4() const { return ImVec4( r, g, b, a ); }


	};
	struct PlayerType
	{
		PlayerTypeEnum id = PlayerTypeEnum::normal;

		PlayerType() = default;

		PlayerType( std::string displayName )
		{
			do // get player type
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
					id = PlayerTypeEnum::titan;
					break;
				}
			} while ( false );



		}

		PlayerTypeEnum GetId()
		{
			return id;
		}
		std::string GetString()
		{
			switch ( id )
			{
			case PlayerTypeEnum::normal:
				return std::string( "Normal" );
			case PlayerTypeEnum::titan:
				return std::string("Titan");
			case PlayerTypeEnum::vagt:
				return std::string("Vagt");
			case PlayerTypeEnum::officer:
				return std::string("Officer");
			case PlayerTypeEnum::direktor:
				return std::string("Direktor");
			case PlayerTypeEnum::vice:
				return std::string("Vice-Inspektor");
			case PlayerTypeEnum::inspektor:
				return std::string("Inspektor");
			}
		}
		PlayerColor GetColor()
		{
			switch ( id )
			{
			case PlayerTypeEnum::normal:
				return PlayerColor( 1.f, 1.f, 1.f );
			case PlayerTypeEnum::titan:
				return PlayerColor();
			case PlayerTypeEnum::vagt:
				return PlayerColor();
			case PlayerTypeEnum::officer:
				return PlayerColor();
			case PlayerTypeEnum::direktor:
				return PlayerColor();
			case PlayerTypeEnum::vice:
				return PlayerColor();
			case PlayerTypeEnum::inspektor:
				return PlayerColor();
			}
		}
	};
}