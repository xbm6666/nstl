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

template<class T>
struct pointer_value_type
{
	using value_type = T;
};

template<class T>
struct pointer_value_type<T*>
{
	using value_type = T;
};


}
