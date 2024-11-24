#pragma once

namespace config
{
	struct Config
	{
		struct __debug
		{
			bool showIndicators = false;
			bool displayNameHex = false;
		} debug;

		struct __combat
		{
			struct __clicker
			{
				bool enabled = false;
				
				struct __lmb
				{
					bool enabled = true;
					int minCps = 12;
					int maxCps = 16;
				} left;

				struct __rmb
				{
					bool enabled = false;
					int minCps = 12;
					int maxCps = 16;
				} right;

			} clicker;
		} combat;

		struct __render
		{
			struct __players
			{
				bool name = true;

				struct __d3
				{
					bool master = false;
				} d3;

				struct __d2
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