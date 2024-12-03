#include "EntityPlayer.h"
#include "../../../cache/cache.h"

MAKE_INITIALISER( EntityPlayer );

cache::PlayerData EntityPlayer::ToPlayerData()
{
	
	cache::PlayerData data = {};

	std::string str = this->getDisplayName().getUnformattedText().ToString();

	data.realname = this->getName().ToString();
	data.invalidName = fv::IsBotByName( data.realname );
	data.type = fv::PlayerType( str );
	data.pos = this->GetPos();
	data.lastTickPos = this->GetLastTickPos();
	data.health = this->getHealth();
	data.maxHealth = this->getMaxHealth();

	if ( &config::current.debug.displayNameHex )
	{
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

		data.name = str;
	}

	return data;
	
}
