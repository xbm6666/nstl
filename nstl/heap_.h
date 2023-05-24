#pragma once
#include<xstddef>

#include"vector_.h"

namespace nstl
{
template<typename T, typename Container = vector<T>,typename Compare =std::less<T>>
class heap
{
public:
	using container_type = Container;
	using value_type = container_type::value_type;
	using reference = container_type::reference;
	using size_type = container_type::size_type;

protected:
	container_type c_;
	Compare cmp_;

public:
	heap() = default;

	heap(container_type&& c)
	{
		c_.swap(c);
		make_heap();
	}

	bool empty()const { return c_.empty(); }

	size_type size()const { return c_.size(); }

	reference top() { return c_.front(); }

	void push(const value_type& v)
	{
		c_.push_back(v);
		percolateUp(size()-1);
	}

	void pop()
	{
		assert(!empty());

		c_.front() = c_.back();
		c_.pop_back();
		percolateDown(0);
	}

private:
	void make_heap()
	{
		for (int i = size() / 2; i >= 0; --i)
			percolateDown(i);
	}
	void percolateUp(size_type hole)
	{
		T tmp = c_[hole];
		for (; hole > 0 && cmp_(c_[hole / 2],tmp ); hole /= 2)
			c_[hole] = c_[hole / 2];
		c_[hole] = tmp;
	}

	void percolateDown(size_type hole)
	{
		if (size() < 2) return;

		T tmp = c_[hole];
		for(int child;hole*2<size();hole=child)
		{
			child = hole==0?1:hole * 2;
			if (child + 1 != size() && cmp_(c_[child], c_[child + 1]))
				++child;
			if (cmp_(tmp,c_[child] ))
				c_[hole] = c_[child];
			else
				break;
		}
		c_[hole] = tmp;
	}
};


}