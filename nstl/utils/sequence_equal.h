#pragma once
namespace nstl
{
template<typename Vec1, typename Vec2>
	requires requires(Vec1 v1, Vec2 v2)
{
	v1.size();
	v1.begin();
	v1.end();

	v2.size();
	v2.begin();
	v2.end();
}
bool operator==(const Vec1& lhs, const Vec2& rhs)
{
	
	if (lhs.size() != rhs.size()) return false;
	auto beg1 = const_cast<Vec1&>(lhs).begin();
	auto end = const_cast<Vec1&>(lhs).end();
	auto beg2 = const_cast<Vec2&>(rhs).begin();
	while (beg1!=end)
	{
		if (*beg1++ != *beg2++)
			return false;
	}

	return true;
}

}