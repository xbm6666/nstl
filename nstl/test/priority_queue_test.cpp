#include <queue>
#include <iostream>
#include "gtest/gtest.h"
#include "generate_randow_container.h"
#include "queue_equal.h"
#include "vector_.h"
#include "priority_queue_.h"

template<typename T>
class priority_queue_test :public testing::Test
{
};

using priority_queue_types = ::testing::Types<
	nstl::priority_queue<int>
>;
TYPED_TEST_SUITE(priority_queue_test, priority_queue_types);


TYPED_TEST(priority_queue_test, grow)
{
	nstl::vector<int>randoms = nstl::generate_random_vector(-1000000, 1000000);

	TypeParam  nqu;
	std::priority_queue<int>squ;

	for (int i : randoms) {
		nqu.push(i);
		squ.push(i);
	}

	EXPECT_TRUE(nqu == squ);
}


TYPED_TEST(priority_queue_test, random)
{
	nstl::vector<int>randoms = nstl::generate_random_vector(-1000000, 1000000);

	TypeParam  nqu;
	std::priority_queue<int>squ;

	for (int i : randoms) {
		if (i > 0 || nqu.empty())
		{
			nqu.push(i);
			squ.push(i);
		}
		else
		{
			nqu.pop();
			squ.pop();
		}
	}
	EXPECT_TRUE(nqu == squ);
}

int main(int argc, char** argv)
{

	const char* new_argv[] = { argv[0],
		"--gtest_repeat=10",
		"--gtest_color=yes"
	};
	int new_argc = std::end(new_argv) - std::begin(new_argv);


	::testing::InitGoogleTest(&new_argc, const_cast<char**>(new_argv));
	return RUN_ALL_TESTS();
}
