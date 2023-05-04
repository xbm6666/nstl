#pragma once

#include <limits>
#include <cassert>
#include <algorithm>
#include <random>

#include "allocator_.h"
#include "iterator_.h"



namespace nstl
{
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	using value_type = T;
	using allocator_type = Alloc;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = Alloc::size_type;
	using difference_type = Alloc::difference_type;
	using pointer = Alloc::pointer;
	using const_pointer = Alloc::const_pointer;
	using iterator = __warp_iter<pointer>;

	vector() = default;

	vector(const vector&) = default;

	explicit vector(size_type n)
	{
		reserve(n);
	}

	vector(size_type n, const value_type& x)
	{
		reserve(n);
		for (int i = 0; i < n; ++i)
			begin_[i] = x;
		end_ = begin_ + n;
	}

	template<typename InputIterator>
	requires InputIterator::iterator_category
	vector(InputIterator first, InputIterator end)
	{
		while (first != end)
			push_back(*first++);
	}

	iterator begin() { return iterator(begin_); };

	iterator end() { return iterator(end_); };

	void reserve(size_type n)
	{
		if (n <= capacity()) return;
		pointer new_begin = alloc.allocate(n);
		for (int i = 0; i < size(); ++i) {
			new_begin[i] = begin_[i];
		}

		alloc.deallocate(begin_, size());
		cap_ = new_begin + n;
		end_ = new_begin + size();
		begin_ = new_begin;
	}

	reference operator[](const size_type n)const noexcept
	{
		return begin_[n];
	}

	size_type max_size() { return std::numeric_limits<size_type>::max(); }

	size_type size()const { return end_ - begin_; }

	size_type capacity() { return cap_ - begin_; }

	reference front()
	{
		assert(!empty());
		return begin_[0];
	}

	reference back()
	{
		assert(!empty());
		return *(end_ - 1);
	}

	value_type* data()
	{
		return begin_;
	}

	void clear()
	{
		alloc.deallocate(begin_, capacity());
		begin_ = end_ = cap_ = nullptr;
	}

	void resize(size_type count)
	{
		if (count > capacity()) {
			reserve(count);
		}
		else {
			end_ = begin_ + count;
		}
	}

	void push_back(const value_type& value)
	{
		if (capacity() == 0)reserve(8);
		else if (end_ == cap_)reserve(capacity() * 2);
		*end_++ = value;
	}

	void pop_back()
	{
		assert(!empty());
		--end_;
	}


	bool empty() { return begin_ == end_; }

private:
	pointer begin_ = nullptr;
	pointer end_ = nullptr;
	pointer cap_ = nullptr;
	Alloc alloc;
};

template<typename Vec1,typename Vec2>
	requires requires(Vec1 v1, Vec2 v2)
{
	v1[0];
	v2[0];
	v1.size();
	v2.size();
}
bool operator==(const Vec1& lhs,const Vec2& rhs)
{
	if (lhs.size() != rhs.size()) return false;
	for (int i = 0; i < lhs.size();++i)
		if (lhs[i] != rhs[i])
			return false;
	return true;
}

template<typename T=int>
vector<T>random_vector(T min, T max, T step=1)
{
	vector<T>randoms;
	for (T i = min; i < max; i+=step) {
		randoms.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(randoms.begin(), randoms.end(), g);
	return randoms;
}

}