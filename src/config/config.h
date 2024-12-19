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
				bool enabled = true;
				
				struct __lmb
				{
					bool enabled = true;
					int minCps = 14;
					int maxCps = 18;
				} left;

				struct __rmb
				{
					bool enabled = false;
					int minCps = 8;
					int maxCps = 12;
				} right;

			} clicker;
		} combat;

		struct __render
		{
			struct __esp
			{
				struct __names
				{
					bool enabled = true;
					bool health = true;
					bool absorption = true;
				} names;

				struct __d3
				{
					bool enabled = true;
					enum
					{
						ESP25d = 0,
						ESPbox = 1
					} mode = ESP25d;
					struct __d25
					{
						bool box = true;
						bool healthbar = true;
					} d25;
					struct __box
					{

					} box;

				} d3;

				struct __d2
				{
					bool enabled = false;
					bool healthbar = true;
					bool healthbarnumber = true;
				} d2;
				
				bool hideSelf = true;
				bool hideBots = true;
			} esp;
		} render;
	};

	inline Config current = {};
}