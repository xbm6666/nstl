#pragma once
#include <queue>

#include "benchmark/benchmark.h"

#include "generate_randow_container.h"
#include "vector_.h"
#include "priority_queue_.h"

template<typename Priority_queue>
static void BM_grow(benchmark::State& state)
{
	for (auto _ : state) {
		Priority_queue pq;
		for (int i = 0; i < state.range(0); ++i) {
			pq.push(i);
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_grow<std::priority_queue<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_grow<nstl::priority_queue<int>>)->Range(8, 8 << 20)->Complexity();

template<typename Priority_queue>
static void BM_random(benchmark::State& state)
{
	for (auto _ : state) {
		auto randoms = nstl::generate_random_vector(-state.range(0), state.range(0));
		Priority_queue pq;

		for (auto i : randoms) {
			if (pq.empty() || i % 2)
			{
				pq.push(i);
			}
			else
			{
				pq.pop();
			}
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_random<std::priority_queue<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_random<nstl::priority_queue<int>>)->Range(8, 8 << 20)->Complexity();



int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
}