#pragma once

#include "deque_.h"

namespace nstl
{
	
template<typename T, typename Container = deque<T>>
class queue
{
public:
	using container_type = Container;
	using value_type = container_type::value_type;
	using reference = container_type::reference;
	using size_type = container_type::size_type;

protected:
	container_type c;

public:
	bool empty()const { return c.empty(); }

	size_type size()const { return c.size(); }

	reference front() { return c.front(); }

	reference back() { return c.back(); }

	void push(const value_type& v) { c.push_back(v); }

	void pop() { c.pop_front(); }

};
}
