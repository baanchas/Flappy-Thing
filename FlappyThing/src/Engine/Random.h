#pragma once

namespace Engine {

	class Random 
	{
	public:
		static void Init()
		{
			srand(static_cast<unsigned>(time(0)));
		}

		// Get ranged random int number 

		static int RangedRandom(int range_min, int range_max)
		{
			return ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
		}
	};

}