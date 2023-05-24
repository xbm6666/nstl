#pragma once
#include "_hash_table_.h"

namespace nstl
{
template<typename T,
	typename Hash = hash<T>,
	typename Equal = std::equal_to<T>,
	typename alloc = Allocator<T>
>
using unordered_multiset = _hash_table<T, Hash, Equal, alloc>;
}
