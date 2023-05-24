#pragma once
#include "vector_.h"

namespace nstl
{
template<typename T,typename Container=vector<T>>
class stack
{
public:
	using container_type = Container;
	using value_type = container_type::value_type;
	using reference = container_type::reference;
	using size_type = container_type::size_type;

protected:
	container_type c_;

public:
	bool empty()const { return c_.empty(); }

	size_type size()const { return c_.size(); }

	reference top() { return c_.back(); }

	void push(const value_type& v) { c_.push_back(v); }

	void pop() { c_.pop_back(); }
};

}