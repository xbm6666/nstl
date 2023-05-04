#pragma once
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "vector_.h"


TEST(vector, grow)
{
	nstl::vector<int> nvec;
	std::vector<int> svec;
	for (int i = 0; i < 1000000; ++i) {
		nvec.push_back(i);
		svec.push_back(i);
	}
	EXPECT_EQ(nvec, svec);
}

TEST(vector, logic)
{
	nstl::vector<int> nvec;
	std::vector<int> svec;
	nvec.push_back(5);
	nvec.push_back(2);
	nvec.push_back(3);
	nvec.pop_back();
	svec.push_back(5);
	svec.push_back(2);
	svec.push_back(3);
	svec.pop_back();
	EXPECT_EQ(nvec, svec);
	nvec.clear();
	svec.clear();
	EXPECT_EQ(nvec, svec);
}

TEST(vector, random)
{
	
	nstl::vector<int>randoms= nstl::random_vector(-100000, 2000000);

	nstl::vector<int> nvec;
	std::vector<int> svec;

	for (int n : randoms) {
		if (n>0||nvec.empty()) {
			nvec.push_back(n);
			svec.push_back(n);
			continue;
		}
		else {
			nvec.pop_back();
			svec.pop_back();
		}
	}
	EXPECT_EQ(nvec, svec);
}

TEST(vector, size)
{
	nstl::vector<int> nvec(10000,3);
	std::vector<int> svec(10000, 3);
	
	EXPECT_EQ(nvec, svec);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}