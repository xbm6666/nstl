#pragma once
#include <cassert>
#include <iostream>
#include "iterator_.h"
#include "allocator_.h"

namespace nstl
{
template<typename T>
struct _Node
{
	T value;
	_Node* previous = nullptr;
	_Node* next = nullptr;
};

template<
	typename ValueType,
	typename DiffType = int
>
class _list_iterator
{
public:
	using value_type = ValueType;
	using pointer = value_type*;
	using reference = value_type&;
	using difference_type = DiffType;
	using iterator_category = bidirectional_iterator_tag;

protected:
	_Node<value_type>* current = nullptr;

public:
	_list_iterator(const _list_iterator& rhs) :current(rhs.current) {};

	_list_iterator(_Node<value_type>* ptr) :current(ptr) {};

	_Node<value_type>* get_node() { return current; }

	reference operator*() { return current->value; }

	pointer  operator->() { return &current->value; }

	_list_iterator& operator++()
	{
		current = current->next;
		return *this;
	}

	_list_iterator operator++(int)
	{
		_list_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	_list_iterator& operator--()
	{
		current = current->previous;
		return *this;
	}

	_list_iterator operator--(int)
	{
		_list_iterator tmp(*this);
		--(*this);
		return tmp;
	}

	friend 
	bool operator==(const _list_iterator& lhs,const _list_iterator& rhs)
	{
		return lhs.current == rhs.current;
	}

};


template<
	typename T,
	typename Alloc = Allocator<_Node<T>>
	>
class list
{
	using node_type = _Node<T>;
public:
	using value_type = T;
	using reference = value_type&;
	using pointer = value_type*;
	using size_type = Alloc::size_type;
	using difference_type = Alloc::difference_type;
	using iterator = _list_iterator<value_type>;

private:
	size_type size_=0;
	node_type node_;
	Alloc alloc_;

public:
	list()
	{
		init();
	}

	list(const list&rhs)
	{
		clear();
		for (auto& v : rhs)
			push_back(v);
	}

	list& operator=(const list& rhs)
	{
		clear();
		for (const auto& v :const_cast<list&>(rhs))
			push_back(v);
		return *this;
	}

	~list()
	{
		clear();
	}

	size_type size()const { return size_; }

	bool empty()const { return size() == 0; }

	iterator begin()
	{
		return iterator(node_.next);
	}

	iterator end()
	{
		return iterator(&node_);
	}

	reference front()
	{
		assert(!empty());
		return node_.next->value;
	}

	reference back()
	{
		assert(!empty());
		return node_.previous->value;
	}

	void insert(iterator it,const value_type&x)
	{
		auto cur = it.get_node();
		node_type* nd = alloc_.allocate(1);
		nd->value = x;
		nd->next = cur;
		nd->previous = cur->previous;
		cur->previous->next = nd;
		cur->previous = nd;
		++size_;
	}
	void push_front(const value_type& x)
	{
		insert(begin(), x);
	}
	void push_back(const value_type& x)
	{
		insert(end(), x);
	}
	iterator erase(iterator it)
	{
		auto cur = it.get_node();
		cur->previous->next = cur->next;
		cur->next->previous = cur->previous;
		iterator ret(cur->next);
		alloc_.deallocate(cur, 1);
		--size_;
		return ret;
	}
	void pop_front()
	{
		assert(!empty());
		erase(begin());
	}

	void pop_back()
	{
		assert(!empty());
		erase(--end());
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	bool _invariants()
	{
		size_type sz = size();
		for(auto  &_:*this)
		{
			--sz;
		}
		return sz == 0;
	}

private:
	void init()
	{
		node_.next = &node_;
		node_.previous = &node_;
		node_.value = value_type{};
	}
};

}