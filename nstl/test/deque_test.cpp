#include <deque>
#include <iostream>
#include "gtest/gtest.h"
#include "generate_randow_container.h"
#include "sequence_equal.h"
#include "vector_.h"
#include "_devector_.h"
#include "deque_.h"
#include "list_.h"

template<typename T>
class deque_test:public testing::Test
{};

using deque_types = ::testing::Types<
	nstl::list<int>,
	nstl::devector<int>,
	nstl::deque<int>
>;
TYPED_TEST_SUITE(deque_test, deque_types);


TYPED_TEST(deque_test, grow)
{
	nstl::vector<int>randoms = nstl::generate_random_vector(-1000000, 1000000);

	TypeParam  ndeq;
	std::deque<int>sdeq;

	for (int i : randoms) {
		if (i > 0)
		{
			ndeq.push_back(i);
			sdeq.push_back(i);
		}
		else
		{
			ndeq.push_front(i);
			sdeq.push_front(i);
		}
	}
	EXPECT_TRUE(sdeq == ndeq);
	EXPECT_TRUE(ndeq._invariants());
}


TYPED_TEST(deque_test, random)
{
	nstl::vector<int>randoms = nstl::generate_random_vector(-1000000, 1000000);

	TypeParam ndeq;
	std::deque<int>sdeq;

	for (int i : randoms) {
		if (i > 0 )
		{
			if (ndeq.empty() || i % 2)
			{
				ndeq.push_back(i);
				sdeq.push_back(i);
			}
			else
			{
				ndeq.pop_back();
				sdeq.pop_back();
			}
		}
		else
		{
			if (ndeq.empty() || i % 2)
			{
				ndeq.push_front(i);
				sdeq.push_front(i);
			}
			else
			{
				ndeq.pop_front();
				sdeq.pop_front();
			}
		}
	}
	EXPECT_TRUE(sdeq == ndeq);
	EXPECT_TRUE(ndeq._invariants());

	sdeq.clear();
	ndeq.clear();
	EXPECT_TRUE(sdeq == ndeq);
	EXPECT_TRUE(ndeq._invariants());
}

int main(int argc, char** argv)
{
	
	const char* new_argv[] ={ argv[0],
		"--gtest_repeat=10",
		"--gtest_color=yes"
	};
	int new_argc = std::end(new_argv) - std::begin(new_argv);


	::testing::InitGoogleTest(&new_argc, const_cast<char**>(new_argv));
	return RUN_ALL_TESTS();
}
