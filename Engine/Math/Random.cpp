#include "Random.h"
#include <stdlib.h>

namespace MAC {

	float Random() {
		return rand() / static_cast<float>(RAND_MAX);
	}

	float RandomRange(float min, float max) {
		return min + (max - min) * Random();
	}
	void SeedRandom(unsigned int seed) {
		srand(seed);
	}

	int RandomInt() {
		return rand();
	}

	int RandomIntRange(int min, int max) {
		return min + rand() % (max - min);
	}
}