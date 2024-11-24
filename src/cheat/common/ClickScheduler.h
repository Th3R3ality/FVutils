#pragma once
#include <array>

namespace ClickScheduler
{
	enum class ClickMethod
	{
		STABILISED
	};

	std::array<int, 20> Generate( ClickMethod method, int minCps, int maxCps );
}