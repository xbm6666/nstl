#pragma once

namespace nstl
{
struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag :public input_iterator_tag {};

struct bidirectional_iterator_tag :public forward_iterator_tag {};

struct random_access_iterator_tag :public bidirectional_iterator_tag {};

template<typename Category, typename Type>
struct iterator
{
	using iterator_category = Category;
	using value_type = Type;
	using difference_type = unsigned int;
	using pointer = value_type*;
	using reference = value_type&;
};

template<typename T>
class __warp_iter
{
public:
	using iterator_type = T;
	using iterator_category = random_access_iterator_tag;
	using value_type = decltype(*T);
	using difference_type = unsigned int;
	using pointer = value_type*;
	using reference = value_type&;

private:
	iterator_type p;

public:
	__warp_iter(iterator_type rhs) :p(rhs) {};

	__warp_iter(const __warp_iter& rhs) :p(rhs->p) {};

	__warp_iter& operator=(const __warp_iter& rhs)
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

	__warp_iter& operator++()
	{
		++p;
		return *this;
	}
	__warp_iter operator++(int)
	{
		__warp_iter tmp(*this);
		++(*this);
		return tmp;
	}

	__warp_iter& operator--()
	{
		--p;
		return *this;
	}
	__warp_iter operator--(int)
	{
		__warp_iter tmp(*this);
		--(*this);
		return tmp;
	}
	__warp_iter& operator+(difference_type n)
	{
		__warp_iter tmp(*this);
		tmp += n;
		return tmp;
	}
	__warp_iter operator+=(difference_type n)
	{
		p += n;
		return *this;
	}
	__warp_iter& operator-(difference_type n)
	{
		__warp_iter tmp(*this);
		tmp -= n;
		return tmp;
	}
	__warp_iter operator-=(difference_type n)
	{
		p -= n;
		return *this;
	}
	reference operator[](difference_type n)
	{

		return p[n];
	}

	iterator_type base() { return p; }

	auto operator<=>(const __warp_iter<T>& rhs)const
	{
		return p <=> rhs.p;
	};


};

template<typename T>
bool operator==(const __warp_iter<T>& lhs, const __warp_iter<T>& rhs)
{
	return lhs.base() == rhs.base();
};

template<typename T>
bool operator!=(const __warp_iter<T>& lhs, const __warp_iter<T>& rhs)
{
	return !(lhs == rhs);
};


}
