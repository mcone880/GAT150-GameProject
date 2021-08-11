#pragma once

namespace MAC {

	void SeedRandom(unsigned int seed);

	float Random();
	float RandomRange(float min, float max);

	int RandomInt();
	int RandomInt(int max);
	int RandomIntRange(int min, int max);
}