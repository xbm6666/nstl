#pragma once
#include<algorithm>
#include<vector>

namespace nstl
{
template<typename HashTable1, typename HashTable2>
	requires requires(HashTable1 v1, HashTable2 v2)
{
	v1.size();
	v1.begin();
	v1.end();

	v2.size();
	v2.begin();
	v2.end();
}
bool operator==(const HashTable1& lhs, const HashTable2& rhs)
{
	if (lhs.size() != rhs.size()) return false;
	std::vector<typename HashTable1::value_type>vec1, vec2;
	for ( auto& v : const_cast<HashTable1&>(lhs))
		vec1.push_back(v);
	for ( auto& v : const_cast<HashTable2&>(rhs))
		vec2.push_back(v);
	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());
	return vec1 == vec2;
}

}