#pragma once
#include <random>
#include "vector_.h"
namespace nstl
{
template<typename T = int>
vector<T>generate_random_vector(T min, T max, T step = 1)
{
	vector<T>randoms;
	for (T i = min; i < max; i += step) {
		randoms.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(randoms.begin(), randoms.end(), g);
	return randoms;
}
}