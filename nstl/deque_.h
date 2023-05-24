#pragma once

#include "iterator_.h"
#include "allocator_.h"
#include "_devector_.h"

namespace nstl
{
template<typename ValueType, typename DiffType>
struct _deque_block_size
{
	constexpr static DiffType value = sizeof(ValueType) < 256 ? 4096 / sizeof(ValueType) : 16;
};

template<typename ValueType,
	typename MapPointer,
	typename DiffType = int,
	DiffType BS = _deque_block_size<ValueType, DiffType>::value
	>
class _deque_iterator
{
public:
	using value_type = ValueType;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = DiffType;
	using iterator_category = random_access_iterator_tag;

private:
	MapPointer map_pointer_ = nullptr;
	pointer pointer_ = nullptr;

public:
	constexpr static DiffType _block_size = BS;

	_deque_iterator() = default;

	_deque_iterator(const _deque_iterator&) = default;

	explicit _deque_iterator(MapPointer mp, pointer p)
		:map_pointer_(mp), pointer_(p)
	{}

	reference operator*()const { return *pointer_; }

	pointer operator->()const { return pointer_; }

	_deque_iterator& operator++()
	{
		if (++pointer_ == *map_pointer_ + _block_size)
		{
			++map_pointer_;
			pointer_ = *map_pointer_;
		}
		return *this;
	}

	_deque_iterator operator++(int)
	{
		_deque_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	_deque_iterator& operator--()
	{
		if (pointer_ == *map_pointer_)
		{
			--map_pointer_;
			pointer_ = *map_pointer_ + _block_size;
		}
		--pointer_;
		return *this;
	}

	_deque_iterator operator--(int)
	{
		_deque_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	_deque_iterator& operator+=(difference_type n)
	{
		if (n == 0) return *this;

		n += pointer_ - map_pointer_;

		if (n > 0)
		{
			map_pointer_ += n / _block_size;
			pointer_ = *map_pointer_ + n % _block_size;
		}
		else
		{
			difference_type z = _block_size - 1 - n;
			map_pointer_ -= z / _block_size;
			pointer_ = *map_pointer_ + (_block_size - 1 - z % _block_size);
		}
		return *this;
	}

	_deque_iterator& operator-=(difference_type n)
	{
		return *this += -n;
	}

	_deque_iterator operator+(difference_type n)const
	{
		_deque_iterator tmp(*this);
		tmp += n;
		return tmp;
	}

	_deque_iterator operator-(difference_type n)const
	{
		_deque_iterator tmp(*this);
		tmp -= n;
		return tmp;
	}

	friend
		_deque_iterator operator+(difference_type n, const _deque_iterator& it)
	{
		return it + n;
	}

	friend
		difference_type operator-(const _deque_iterator& x, const _deque_iterator& y)
	{
		if (x == y) return 0;

		return (x.map_pointer_ - y.map_pointer_) * x._block_size +
			(x.pointer_ - *x.map_pointer_) -
			(y.pointer_ - *y.map_pointer_);
	}

	reference operator[](difference_type n)const
	{
		return*(*this + n);
	}

	friend
		bool operator==(const _deque_iterator& x, const _deque_iterator& y)
	{
		return x.pointer_ == y.pointer_;
	}

	friend
		bool operator!=(const _deque_iterator& x, const _deque_iterator& y)
	{
		return !(x == y);
	}

	auto operator<=>(const _deque_iterator& rhs)const
	{
		if(map_pointer_!=rhs.map_pointer_)
		{
			return map_pointer_ <=> rhs.map_pointer_;
		}
		return pointer_ <=> rhs.pointer_;
	}

};

template<
	typename T,
	typename Map=devector<T*>,
	typename alloc=Allocator<T>>
class deque
{
public:
	using value_type = T;
	using allocator_type = alloc;
	using size_type = allocator_type::size_type;
	using difference_type = allocator_type::difference_type;
	using pointer = allocator_type::pointer;
	using _pointer_allocator = rebind_alloc<alloc, pointer>;
	//using _map = devector< pointer, _pointer_allocator>;
	using _map = Map;
	using _map_alloc = _pointer_allocator;
	using _map_pointer = typename _map_alloc::pointer;

	using reference = value_type&;
	using iterator = _deque_iterator<value_type, _map_pointer, difference_type>;

	constexpr static difference_type _block_size = iterator::_block_size;
private:
	_map map_;
	size_type start_=0;
	size_type size_=0;
	alloc alloc_;

public:
	deque() { _init(); }

	iterator begin()
	{
		_map_pointer mp = map_.begin() + start_ / _block_size;
		pointer p = map_.empty() ? nullptr : *mp + start_ % _block_size;
		return iterator(mp, p);
	}

	iterator end()
	{
		size_type end = start_ + size();
		_map_pointer mp = map_.begin() + end / _block_size;
		pointer p = map_.empty() ? nullptr : *mp + end % _block_size;
		return iterator(mp, p);

	}

	bool empty()const { return size() == 0; }

	reference operator[](size_type n)
	{
		size_type p = start_ + n;
		return *(*(map_.begin() + p / _block_size) + p % _block_size);
	}

	reference front()
	{
		return *(*(map_.begin() + start_ / _block_size) + start_ % _block_size);
	}

	reference back()
	{
		size_type p = start_ + size() - 1;
		return *(*(map_.begin() + p / _block_size) + p % _block_size);
	}

	void push_front(const value_type& v)
	{
		if (_front_spare() == 0)
		{
			_add_front_capacity();
		}
		*--begin() = v;
		--start_;
		++size_;
	}
	void push_back(const value_type& v)
	{
		if (_back_spare() == 0)
		{
			_add_back_capacity();
		}
		*end() = v;
		++size_;
	}
	void pop_front()
	{
		assert(!empty());
		++start_;
		--size_;
	}
	void pop_back()
	{
		assert(!empty());
		--size_;
	}

	size_type capacity() const
	{
		return map_.empty() ? 0 : map_.size() * _block_size - 1;
	}

	size_type size()const { return size_; }

	void clear()
	{
		_clear();
		_init();
	}

	~deque()
	{
		_clear();
	}

	bool _invariants()const
	{
		if (!map_._invariants()) return false;

		if (map_.size() >= size_type(-1) / _block_size) return false;

		for (auto p : map_)
			if (p == nullptr)
				return false;

		if(map_.size()!=0)
		{
			if (size() >= map_.size() * _block_size)
				return false;

			if (start_ >= map_.size() * _block_size - size())
				return false;
		}
		else
		{
			if (size() != 0)
				return false;
			if (start_ != 0)
				return false;
		}
		return true;
	}

private:
	void _init()
	{
		_add_back_capacity();
		start_ = _block_size / 2;
		size_ = 0;
	}

	size_type _front_spare()
	{
		return start_;
	}

	size_type _back_spare()
	{
		return capacity() - (start_ + size());
	}

	void _add_front_capacity()
	{
		map_.push_front(alloc_.allocate(_block_size));
		start_ += _block_size;
	}

	void _add_back_capacity()
	{
		map_.push_back(alloc_.allocate(_block_size));
	}

	void _clear()
	{
		for (pointer p : map_)
		{
			alloc_.deallocate(p, _block_size);
		}
		map_.clear();
		start_ = size_ = 0;
	}
};

}
