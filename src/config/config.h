#pragma once

namespace config
{
	struct Config
	{
		struct
		{
			bool indicators;

		} debug;
	};

	inline Config current = {};
}