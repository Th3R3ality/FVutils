#include "ClickScheduler.h"
#include <random>

namespace ClickScheduler
{
	std::random_device rd;
	std::mt19937 gen( rd() );

	std::array<int, 20> GenStabilised( int minCps, int maxCps )
	{

		std::uniform_int_distribution distrib( minCps, maxCps );
		int clicks = distrib( gen );

		auto clickArray = std::array<int, 20>{0};

		int interval = clickArray.size() / clicks;
		int remainder = clickArray.size() % clicks;

		int currentIndex = 0;

		for ( int i = 0; i < clicks; i++ )
		{
			if ( remainder > 0 )
			{
				clickArray[ currentIndex ]++;
				currentIndex += interval;
				currentIndex++;
				remainder--;
				continue;
			}

			// Choose random index
			int indexWithLeastClicks = 0;
			for ( int j = 1; j < clickArray.size(); j++ )
			{
				if ( clickArray[ j ] < clickArray[ j - 1 ] )
				{
					indexWithLeastClicks = j;
				}
			}
			clickArray[ indexWithLeastClicks ]++;
		}

		return clickArray;
	}

	std::array<int, 20> Generate( ClickMethod method, int minCps, int maxCps )
	{
		switch ( method )
		{
		case ClickMethod::STABILISED:
			return GenStabilised( minCps, maxCps );

		default:
			return std::array<int, 20>();
		}
	}
}
