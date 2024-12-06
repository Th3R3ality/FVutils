#pragma once
#include <vector>

namespace modules
{
	inline std::vector<void( * )( )> moduleInitialisers = {};

	// if callback returns true original method will be cancelled
	inline std::vector<bool( * )( )> preRunTickCallbacks = {};

	inline std::vector<void( * )( )> postRunTickCallbacks = {};

	void Init();
}