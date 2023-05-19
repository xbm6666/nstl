#pragma once
#include <iostream>
#include <vector>


#include "benchmark/benchmark.h"

#include "vector_.h"


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
BENCHMARK(BM_vector_grow)->Range(8, 8 << 20)->Complexity();

static void BM_myvector_grow(benchmark::State& state)
{
	for (auto _ : state) {
		nstl::vector<int>vec;
		for (int i = 0; i < state.range(0); ++i) {
			vec.push_back(i);
		}
	}
	state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_myvector_grow)->Range(8, 8 << 20)->Complexity();

static void BM_vector_size(benchmark::State& state)
{
	for (auto _ : state) {
		std::vector<int>vec(state.range(0),7);
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_vector_size)->Range(8, 8 << 20)->Complexity();

static void BM_myvector_size(benchmark::State& state)
{
	for (auto _ : state) {
		nstl::vector<int>vec(state.range(0), 7);
	}
	state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_myvector_size)->Range(8, 8 << 20)->Complexity();

int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	::benchmark::RunSpecifiedBenchmarks();
	::benchmark::Shutdown();
}