#pragma once
#include <deque>

#include "benchmark/benchmark.h"

#include "generate_randow_container.h"
#include "vector_.h"
#include "_devector_.h"
#include "deque_.h"
#include "list_.h"

template<typename Deque>
static void BM_grow(benchmark::State& state)
{
	for (auto _ : state) {
		Deque deq;
		for (int i = 0; i < state.range(0); ++i) {
			deq.push_front(i);
			deq.push_back(i);
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_grow<std::deque<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_grow<nstl::devector<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_grow<nstl::list<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_grow<nstl::deque<int, nstl::devector<int*>>> )->Range(8, 8 << 20)->Complexity();

template<typename Deque>
static void BM_random(benchmark::State& state)
{
	for (auto _ : state) {
		auto randoms = nstl::generate_random_vector(-state.range(0), state.range(0));

		Deque deq;
		for (auto i : randoms) {
			if (i > 0)
			{
				if (deq.empty() || i % 2)
				{
					deq.push_back(i);
				}
				else
				{
					deq.pop_back();
				}
			}
			else
			{
				if (deq.empty() || i % 2)
				{
					deq.push_front(i);
				}
				else
				{
					deq.pop_front();
				}
			}
		}
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_random<std::deque<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_random<nstl::devector<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_random<nstl::list<int>>)->Range(8, 8 << 20)->Complexity();
BENCHMARK(BM_random<nstl::deque<int,nstl::devector<int*>>>)->Range(8, 8 << 20)->Complexity();

int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
}