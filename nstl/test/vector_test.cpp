#pragma once
#include <iostream>
#include <vector>

#include "vector_.h"

#include "benchmark/benchmark.h"
#include "gtest/gtest.h"



TEST(vector, grow)
{
	nstl::vector<int> vec;
	for (int i = 0; i < 10000; ++i) {
		vec.push_back(i);
	}
}


static void BM_vector_grow(benchmark::State& state)
{
	for (auto _ : state) {
		std::vector<int>vec;
		for (int i = 0; i < state.range(0); ++i) {
			vec.push_back(i);
		}
	}
	state.SetComplexityN(state.range(0));
}

static void BM_myvector_grow(benchmark::State& state)
{
	for (auto _ : state) {
		nstl::vector<int>vec;
		for (int i = 0; i < state.range(0);++i) {
			vec.push_back(i);
		}
	}
	state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_myvector_grow)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_vector_grow)->Range(8, 8 << 20)->Complexity();


int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();


	std::cout << std::endl << std::endl;
	std::cout << "------------------------------------------------------------------------\n";
	std::cout << "------------------------------------------------------------------------\n";
	std::cout << std::endl << std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}