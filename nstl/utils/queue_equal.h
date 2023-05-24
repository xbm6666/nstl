#pragma once

namespace nstl
{
template<typename Q1>
	requires requires(Q1 v1)
{
	v1.front();
}
auto get_first(Q1& q1)
{
	return q1.front();
}

template<typename Q1>
	requires requires(Q1 v1)
{
	v1.top();
}
auto get_first(Q1& q1)
{
	return q1.top();
}

template<typename Q1, typename Q2>
	requires requires(Q1 v1, Q2 v2)
{
	v1.empty();
	v1.pop();
	v1.size();

	v2.empty();
	v2.pop();
	v2.size();
}
bool operator==(const Q1& q1, const Q2& q2)
{
	auto& lhs = const_cast<Q1&>(q1);
	auto& rhs = const_cast<Q2&>(q2);
	if (lhs.size() != rhs.size()) return false;
	while (!lhs.empty())
	{
		if (get_first(lhs) != get_first(rhs))
			return false;
		lhs.pop();
		rhs.pop();
	}

	return true;
}

}