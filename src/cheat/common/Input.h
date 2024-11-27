#pragma once
#include <vector>

namespace Input
{
	using KeyCode = unsigned __int64;

	struct KeyStatePair
	{
		KeyCode keyCode;
		int state;
	};

	struct MouseStatePair
	{
		KeyCode keyCode;
		bool state;
	};

	inline std::vector<KeyStatePair> keyStates;
	inline std::vector<MouseStatePair> mouseStates;

	void DeltaKey(KeyCode keyCode, int delta);
	bool GetKey(KeyCode keyCode);

	void SetMouseState( KeyCode keyCode, bool state );
	bool GetMouseState( KeyCode keyCode );
}