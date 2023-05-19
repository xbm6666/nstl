#include <stack>
#include "gtest/gtest.h"
#include "generate_randow_container.h"
#include "sequence_equal.h"
#include "vector_.h"
#include "stack_.h"

TEST(stack, random)
{

	nstl::vector<int>randoms = nstl::generate_random_vector(-100000, 2000000);

	nstl::stack<int> nstk;
	std::stack<int> sstk;

	for (int n : randoms) {
		if (n > 0 || nstk.empty()) {
			nstk.push(n);
			sstk.push(n);
			continue;
		}
		else {
			nstk.pop();
			sstk.pop();
		}
	}
	nstl::vector<int> nvec;
	std::vector<int> svec;
	while (!nstk.empty()) {
		nvec.push_back(nstk.top());
		nstk.pop();
	}
	while (!sstk.empty()) {
		svec.push_back(sstk.top());
		sstk.pop();
	}
	EXPECT_TRUE(nvec == svec);

}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}