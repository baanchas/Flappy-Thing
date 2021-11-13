#pragma once

namespace Engine {

	class Random 
	{
	public:
		static int RangedRandom(int range_min, int range_max)
		{
			return ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
		}
	};

}