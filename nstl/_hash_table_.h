#pragma once
#include <xstddef>
#include <tuple>

#include "iterator_.h"
#include "allocator_.h"
#include "vector_.h"
#include "list_.h"

namespace nstl
{
static vector<int> primes{
	7,17,37,79,163,331,673,1361,2729,5471,10949,21911,43853,87719,175447,
	350899,701819,1403641,2807303,5614657,11229331,22458671,44917381,89834777
};

	int get_size(int n)
{
	for (int v : primes)
		if (v >= n)
			return v;
	return -1u;
}
template<typename T>
struct hash
{
	
};

	template<>
struct hash<int>
{
	int operator()(int n,int sz)const
	{
		int ret= n % sz;
		if (ret < 0)
			ret += sz;
		assert(ret >= 0);
		assert(ret < sz);
		return ret;
	}
};

template<typename  VecIt,typename LstIt>
class _hash_table_iterator
{
public:
	using iterator_category = forward_iterator_tag;
	using value_type =typename LstIt::value_type;
	using reference = value_type&;
	using pointer = value_type*;
	using difference_type = typename LstIt::difference_type;

	_hash_table_iterator(const _hash_table_iterator&) = default;

	_hash_table_iterator(VecIt vi,LstIt li, VecIt ei):vi_(vi),li_(li),ei_(ei)
	{}

	reference operator*()
	{
		return *li_;
	}

	pointer operator->()
	{
		return li_;
	}

	_hash_table_iterator&operator++()
	{
		if (vi_!=ei_)
		{
			++li_;
			if(li_!=vi_->end())
			{
				return *this;
			}
			while (++vi_ != ei_)
			{
				if(!vi_->empty())
				{
					li_ = vi_->begin();
					return *this;
				}
			}
		}
		return *this;
	}

	_hash_table_iterator operator++(int)
	{
		_hash_table_iterator tmp(*this);
		++(*this);
		return tmp;
	}

	bool operator==(const _hash_table_iterator&) const
	{
		return vi_ == ei_;
	}

private:
	VecIt vi_;
	LstIt li_;
	VecIt ei_;
};

template<typename T,
	typename Hash=hash<T>,
	typename Equal=std::equal_to<T>,
	typename alloc=Allocator<T>
	>
class _hash_table
{
public:
	using value_type = T;
	using hasher = Hash;
	using key_equal = Equal;
	using allocator_type = alloc;
	using reference = value_type&;
	using pointer = alloc::pointer;
	using size_type = alloc::size_type;
	using difference_type = alloc::difference_type;
	using iterator =
		_hash_table_iterator<
		typename vector<list<T>>::iterator,
		typename list<T>::iterator
		>;

private:
	size_type size_ = 0;
	constexpr static double max_load_factor = 1;
	hasher hash_fun_;
	Equal equal_;
	alloc alloc_;

	vector<list<value_type>> table_;

public:
	_hash_table() { init(); }

	~_hash_table()
	{
		for (auto& v : table_)
			v.clear();
		table_.clear();
	}

	size_type size()const { return size_; }

	bool empty()const { return size() == 0; }

	void clear()
	{
		for (auto& v : table_)
			v.clear();
		table_.clear();

		init();
	}

	iterator begin()
	{
		if (empty())
			return end();
		for(auto beg=table_.begin(),end=table_.end();beg!=end;++beg)
		{
			if (!beg->empty())
				return iterator(beg, beg->begin(), table_.end());
		}
		return end();
	}

	iterator end()
	{
		auto it = table_.end();
		return iterator(it, it->end(), it);
	}

	iterator find(const value_type&v)
	{
		auto idx = _get_idx(v);
		for(auto beg=table_[idx].begin(),end=table_[idx].end();beg!=end;++beg)
		{
			if (*beg == v)
				return iterator(table_.begin() + idx, beg, table_.end());
		}
		return end();
	}

	std::pair<iterator,bool>insert(const value_type&value)
	{
		if (max_load_factor * table_.size() <= size())
			_rehash(table_.size() * 2);
		++size_;
		return _insert(value);
	}

	size_type erase(const value_type&v)
	{
		auto idx = _get_idx(v);
		for(auto beg=table_[idx].begin(),end=table_[idx].end();beg!=end;++beg)
		{
			if(*beg==v)
			{
				table_[idx].erase(beg);
				--size_;
				return 1;
			}
		}
		return 0;
	}

	bool _invariants()
	{
		size_type sz = size();
		for (auto& _ : *this)
			--sz;
		return sz == 0;
	}

private:
	size_type _get_idx(const value_type& n)
	{
		assert(table_.size());
		return hash_fun_(n, table_.size());
	}

	void init()
	{
		_rehash(1);
	}

	void _rehash(int n)
	{
		if (n <= size())
			return ;
		size_type new_size = get_size(n);
		vector<list<value_type>> new_table;
		new_table.resize(new_size);
		new_table.swap(table_);
		for (list<value_type>& lst : new_table)
			for (value_type v : lst)
				_insert(v);

		
	}

	std::pair<iterator, bool> _insert(value_type v)
	{
		auto idx = _get_idx(v);
		table_[idx].push_front(v);
		return {
			iterator(
			table_.begin() + idx,
			table_[idx].begin(),
			table_.end()
			),
		true };
	}
	
};
}
