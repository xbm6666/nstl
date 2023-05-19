#pragma once
#include <stdlib.h>

namespace nstl
{

template<typename T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = unsigned int;
	using difference_type = int;

	Allocator() = default;
	~Allocator() = default;

	pointer allocate(size_type num)
	{
		return static_cast<pointer>(malloc(sizeof(T) * num));
	}

	void deallocate(pointer p, size_type num)
	{
		free(p);
	}

	template<typename U>
	struct rebind { using other = Allocator<U>; };
};

template<typename Traits, typename T>
using rebind_alloc =typename Traits::template rebind<T>::other;

}