#include "Input.h"

namespace Input
{
	void DeltaKey( unsigned __int64 keyCode, int delta )
	{
		for ( auto&& pair : keyStates )
		{
			if ( pair.keyCode == keyCode )
			{
				pair.state += delta;
				return;
			}
		}

		if ( delta < 0 ) delta = 0;
		keyStates.emplace_back( KeyStatePair{keyCode, delta} );
	}
	bool GetKey( unsigned __int64 keyCode )
	{
		for ( auto&& pair : keyStates )
		{
			if ( pair.keyCode == keyCode )
			{
				return pair.state;
			}
		}

		return false;
	}
}