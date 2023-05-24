#pragma once
#include <cassert>

#include "swap.h"
#include "min_max.h"
#include "allocator_.h"

namespace nstl
{
template<typename T, typename Alloc = Allocator<T>>
class devector
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
	using iterator = pointer;
	using const_iterator = const iterator;

	devector() = default;

	devector(size_type cap, size_type start)
	{
		if (cap == 0)
			return;
		first_ = alloc_.allocate(cap);
		last_ = first_ + cap;
		begin_ = first_ + start;
	}

	devector(const devector&) = delete;

	devector& operator=(const devector&) = delete;

	devector(devector&& c)
	{
		clear();
		swap(c);
	}

	~devector() { clear(); }

	iterator begin() { return begin_; }

	const_iterator begin()const { return begin_; }

	iterator end() { return end_; }

	const_iterator end()const { return end_; }

	size_type size()const { return end_ - begin_; }

	bool empty()const { return begin_ == end_; }

	size_type capacity() { return last_ - first_; }

	size_type front_spare() { return begin_ - first_; }

	size_type back_spare() { return last_ - end_; }

	reference front() { return *begin_; }

	reference back() { return *(end_ - 1); }

	void reserve(size_type n)
	{
		pointer new_first = alloc_.allocate(n);
		pointer new_begin = new_first + (n - size()) / 2;
		pointer new_end = new_begin;

		while (begin_!=end_)
		{
			*new_end++ = *begin_++;
		}

		if (first_ != nullptr);
			alloc_.deallocate(first_, size());

		first_ = new_first;
		begin_ = new_begin;
		end_ = new_end;
		last_ = first_ + n;
	}
	
	void push_front(const_reference x)
	{
		if (first_ == begin_)
			reserve(nstl::max(size() * 3, 8));
		assert(first_ != begin_);
		*--begin_ = x;
	}
	
	void push_back(const_reference x)
	{
		if (end_ == last_)
			reserve(nstl::max(size() * 3,8));
		assert(end_ != last_);
		*end_++ = x;
	}
	
	void pop_front()
	{
		assert(!empty());
		++begin_;
	}

	void pop_back()
	{
		assert(!empty());
		--end_;
	}
	
	void clear()
	{
		if (first_ == nullptr) return;

		alloc_.deallocate(first_, capacity());
		first_ =begin_ = end_ = last_ = nullptr;
	}
	
	void swap(devector& c)
	{
		nstl::swap(first_, c.first_);
		nstl::swap(begin_, c.begin_);
		nstl::swap(end_, c.end_);
		nstl::swap(last_, c.last_);
	}

	bool _invariants()const
	{
		if (first_ == nullptr) 
		{
			if (begin_ != nullptr)
				return false;
			if (end_ != nullptr)
				return false;
			if (last_ != nullptr)
				return false;
		}
		else 
		{
			if (begin_ < first_)
				return false;
			if (end_ < begin_)
				return false;
			if (last_ < end_)
				return false;
		}
		return true;
	}

private:
	pointer first_=nullptr;
	pointer begin_ = nullptr;
	pointer end_ = nullptr;
	pointer last_ = nullptr;
	Alloc alloc_;
};

}