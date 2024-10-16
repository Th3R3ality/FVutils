#pragma once

namespace config
{
	struct Config
	{
		struct
		{
			bool showIndicators = false;
			bool displayNameHex = false;
		} debug;

		struct
		{
			struct
			{
				bool name = true;

				struct
				{
					bool master = false;
				} d3;

				struct
				{
					bool master = true;
					bool healthbar = true;
					bool healthbarnumber = true;
				} d2;
				
				bool hideSelf = true;
				bool hideBots = true;
			} players;
		} render;
	};

	inline Config current = {};
}