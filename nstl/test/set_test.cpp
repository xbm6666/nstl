#include <unordered_set>

#include "gtest/gtest.h"
#include "generate_randow_container.h"
#include "hash_table_equal.h"
#include "set_.h"

template<typename T>
class set_test :public testing::Test
{
};

using set_types = ::testing::Types<
	nstl::unordered_multiset<int>
>;
TYPED_TEST_SUITE(set_test, set_types);


TYPED_TEST(set_test, grow)
{
	nstl::vector<int>randoms = nstl::generate_random_vector(-1000000, 1000000);

	TypeParam  nset;
	std::unordered_multiset<int>sset;

	for (int i : randoms) {
		if (i > 0)
		{
			nset.insert(i);
			sset.insert(i);
		}
		else
		{
			i = -i;
			EXPECT_TRUE(nset.erase(i) == sset.erase(i));
		}
	}
	EXPECT_TRUE(nset._invariants());
	EXPECT_TRUE(nset == sset);
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
