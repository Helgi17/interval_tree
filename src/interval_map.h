#pragma once

#include "simpletree.h"
#include "interval.h"

namespace NSIntervalMap
{

template <typename Key, typename T, typename KeyOfValue, typename Compare>
class interval_map
{
public:
	
	typedef Key key_type;
	typedef T mapped_type;
	typedef Pair<const Key, T> pair_kv_type;
	typedef Compare key_compare;

	struct value_compare
	{
		friend class interval_map<Key, T, KeyOfValue, Compare>;
	protected:
		Compare comp;
		value_compare(Compare comp_): comp(comp_) {}
	public:
		bool operator()(const pair_kv_type& a, const pair_kv_type& b) {
			return comp(a.x, b.x);
		}
	};

	struct key_of_pair
	{
		friend class interval_map<Key, T, KeyOfValue, Compare>;
	protected:
		//KeyOfValue key_of_value;
		//explicit key_of_pair(KeyOfValue kov_): key_of_value(kov_) {}
	public:
		key_type operator()(const pair_kv_type& value_pair) {
			return value_pair.x;
		}
	};

private:
	typedef SimpleTree::Tree<key_type, pair_kv_type, 
			key_of_pair, key_compare> Tree_type;
	Tree_type tree;

public:
	typedef typename Tree_type::iterator iterator;

public:
	interval_map() {}
	~interval_map() = default;

	iterator begin() {
		return tree.begin();
	}

	iterator end() {
		return tree.end();
	}
	
#ifdef CONTAINER_METHODS
	bool empty() {
	}
#endif

#ifdef CONTAINER_SIZE
	size_type size() {
	}
#endif

	mapped_type& operator[](const key_type& k) {
		auto res = insert(pair_kv_type(k, mapped_type()));
		return (*res.x).y;
	}

	Pair<iterator, bool> insert(const key_type& k, const mapped_type& value) {
		typedef Pair<iterator, bool> Res;
		const pair_kv_type p(k, value);
		Pair<iterator, iterator> res = tree.find_place(k);
		if (nullptr == res.y.current) {
			return Res(tree.end(), false);
		}
		if (nullptr == res.x.current) {
			return tree.insert_at(res.x, res.y, p);

		} else {
			return tree.insert_at(res.x, res.y, p);
		}
	}

	Pair<iterator, bool> insert(const pair_kv_type& value_pair) {
		return tree.insert_unique(value_pair);
	}

	void erase(iterator pos) {
		if (pos != tree.end()) {
			tree.erase(pos);
		}
	}

#ifdef CONTAINER_METHODS
	key_compare
	key_comp() {
		
	}

	value_compare
	value_comp()
	{
	}
#endif

	iterator find(const key_type& k) {
		iterator it = tree.find(k);
		key_type p = (*it).x;
		if (p.leftborder == k.leftborder && 
			p.rightborder == k.rightborder) return it;
		if (k.leftborder == k.rightborder &&
			p.leftborder <= k.leftborder &&
			p.rightborder >= k.leftborder) return it; 
		return tree.end();
	}
};

}
