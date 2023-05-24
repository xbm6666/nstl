#pragma once
#include <vector>

#include "gtest/gtest.h"

#include "generate_randow_container.h"
#include "sequence_equal.h"
#include "vector_.h"


TEST(vector, grow)
{
	nstl::vector<int> nvec;
	std::vector<int> svec;
	for (int i = 0; i < 1000000; ++i) {
		nvec.push_back(i);
		svec.push_back(i);
	}
	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());
}

TEST(vector, random)
{
	nstl::vector<int>randoms= nstl::generate_random_vector(-100000, 2000000);

	nstl::vector<int> nvec;
	std::vector<int> svec;

	for (int n : randoms) {
		if (n>0||nvec.empty()) {
			nvec.push_back(n);
			svec.push_back(n);
		}
		else {
			nvec.pop_back();
			svec.pop_back();
		}
	}
	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());
}

TEST(vector, size)
{
	nstl::vector<int> nvec(10000);
	std::vector<int> svec(10000);
	
	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());

	nvec.clear();
	svec.clear();

	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());

	nstl::vector<int> nvec1(10000, 3);
	std::vector<int> svec1(10000, 3);

	EXPECT_TRUE(nvec1 == svec1);
	EXPECT_TRUE(nvec1._invariants());

}
TEST(vector, init)
{
	nstl::vector<int> nvec{1,4,55,7,9,0,4};
	std::vector<int> svec{ 1,4,55,7,9,0,4 };
	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());

	nvec.clear();
	svec.clear();
	EXPECT_TRUE(nvec == svec);
	EXPECT_TRUE(nvec._invariants());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}