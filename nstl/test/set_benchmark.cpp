#pragma once
#include <unordered_set>
#include <iostream>

#include "benchmark/benchmark.h"

#include "generate_randow_container.h"
#include "vector_.h"
#include "set_.h"

template<typename Set>
static void BM_grow(benchmark::State& state)
{
	for (auto _ : state) {
		Set st;
		for (int i = 0; i < state.range(0); ++i) {
			st.insert(i);
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_grow<std::unordered_multiset<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_grow<nstl::unordered_multiset<int>>)->Range(8, 8 << 20)->Complexity();

template<typename Set>
static void BM_random(benchmark::State& state)
{
	for (auto _ : state) {
		auto randoms = nstl::generate_random_vector(-state.range(0), state.range(0));

		Set st;
		for (auto i : randoms) {
			if (i > 0)
			{
				st.insert(i);
			}
			else
			{
				st.erase(i);
			}
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_random<std::unordered_multiset<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_random<nstl::unordered_multiset<int>>)->Range(8, 8 << 20)->Complexity();

int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
}