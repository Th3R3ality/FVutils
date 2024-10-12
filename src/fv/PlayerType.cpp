#include "PlayerType.h"

bool fv::IsBotByName( std::string name )
{
	if ( name.length() < 3 || name.length() > 16 )
		return true;

	if ( name[ 0 ] == '\xC2' )
		return true;

	return false;
}
