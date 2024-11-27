#include "Input.h"

namespace Input
{
	void DeltaKey( KeyCode keyCode, int delta )
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
	bool GetKey( KeyCode keyCode )
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

	//void SetMouseState( KeyCode keyCode, bool state )
	//{
	//	for ( auto&& pair : mouseStates )
	//	{
	//		if ( pair.keyCode == keyCode )
	//		{
	//			pair.state = state;
	//			return;
	//		}
	//	}

	//	mouseStates.emplace_back( MouseStatePair{keyCode, state} );
	//}
	//bool GetMouseState( KeyCode keyCode )
	//{
	//	for ( auto&& pair : mouseStates )
	//	{
	//		if ( pair.keyCode == keyCode )
	//		{
	//			return pair.state;
	//		}
	//	}
	//	return false;
	//}
}