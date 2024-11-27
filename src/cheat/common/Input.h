#pragma once
#include <vector>

namespace Input
{
	struct KeyStatePair
	{
		unsigned __int64 keyCode;
		int state;
	};

	inline std::vector<KeyStatePair> keyStates;

	void DeltaKey(unsigned __int64 keyCode, int delta);
	bool GetKey(unsigned __int64 keyCode);
}