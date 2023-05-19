#pragma once

#include <limits>
#include <cassert>
#include <algorithm>
#include <random>


#include "swap.h"
#include "allocator_.h"
#include "iterator_.h"



namespace nstl
{

template<typename T>
class _warp_iter
{
public:
	using iterator_type = T;
	using iterator_category = random_access_iterator_tag;
	using value_type = pointer_value_type<T>::value_type;
	using difference_type = unsigned int;
	using pointer = value_type*;
	using reference = value_type&;

private:
	iterator_type p;

public:
	_warp_iter(iterator_type rhs) :p(rhs) {};

	_warp_iter(const _warp_iter& rhs) :p(rhs.p) {};

	_warp_iter& operator=(const _warp_iter& rhs)
	{
		p = rhs.p;
		return *p;
	};

	reference operator*()const
	{
		return *p;
	}

	pointer operator->()
	{
		return p.operator->();
	}

	_warp_iter& operator++()
	{
		++p;
		return *this;
	}
	_warp_iter operator++(int)
	{
		_warp_iter tmp(*this);
		++(*this);
		return tmp;
	}

	_warp_iter& operator--()
	{
		--p;
		return *this;
	}
	_warp_iter operator--(int)
	{
		_warp_iter tmp(*this);
		--(*this);
		return tmp;
	}
	_warp_iter operator+(difference_type n)
	{
		_warp_iter tmp(*this);
		tmp += n;
		return tmp;
	}
	_warp_iter operator+=(difference_type n)
	{
		p += n;
		return *this;
	}
	_warp_iter& operator-(difference_type n)
	{
		_warp_iter tmp(*this);
		tmp -= n;
		return tmp;
	}
	_warp_iter operator-=(difference_type n)
	{
		p -= n;
		return *this;
	}
	reference operator[](difference_type n)
	{

		return p[n];
	}

	iterator_type base()const { return p; }

	auto operator<=>(const _warp_iter& rhs)const
	{
		return p <=> rhs.p;
	};


};

template<typename T>
bool operator==(const _warp_iter<T>& lhs, const _warp_iter<T>& rhs)
{
	return lhs.base() == rhs.base();
};

template<typename T>
bool operator!=(const _warp_iter<T>& lhs, const _warp_iter<T>& rhs)
{
	return !(lhs == rhs);
};

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
	using iterator = _warp_iter<pointer>;

	vector() = default;

	vector(const vector& rhs)
	{
		clear();
		reserve(rhs.size());
		for (T t : rhs)
			push_back(t);
	}

	vector(vector&& rhs)noexcept
	{
		clear();
		swap(rhs);
	}


	explicit vector(size_type n):vector(n,T{})
	{}

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

	~vector()
	{
		clear();
	}

	void swap(vector<value_type>& rhs)
	{
		nstl::swap(begin_, rhs.begin_);
		nstl::swap(end_, rhs.end_);
		nstl::swap(cap_, rhs.cap_);
	}

	iterator begin() { return iterator(begin_); };

	iterator end() { return iterator(end_); };

	void reserve(size_type n)
	{
		if (n <= capacity()) return;

		pointer new_begin = alloc_.allocate(n);
		for (int i = 0; i < size(); ++i) {
			new_begin[i] = begin_[i];
		}

		if (begin_ != nullptr);
		alloc_.deallocate(begin_, size());

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
		if (begin_ == nullptr) return;

		alloc_.deallocate(begin_, capacity());
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


	bool empty()const { return begin_ == end_; }

	bool _invariants()const
	{
		if (begin_ == nullptr)
		{
			if (end_ != nullptr || cap_ != nullptr)
				return false;
		}
		else
		{
			if (begin_ > end_)
				return false;
			if (end_ > cap_)
				return false;
		}
		return true;
	}

private:
	pointer begin_ = nullptr;
	pointer end_ = nullptr;
	pointer cap_ = nullptr;
	Alloc alloc_;
};

}