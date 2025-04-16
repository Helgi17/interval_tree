#pragma once

#include "tree.h"
#include "pair.h"

namespace SimpleTree
{

	template <typename T>
	struct TreeNode: public TreeNodeBase
	{
		typedef TreeNodeBase* base_ptr;
	
		T value;
		T* valptr() { return std::__addressof(value); }
	
	};

	TreeNodeBase* tree_increment(TreeNodeBase* x) {
		if (x->right != nullptr)
		{
			x = x->right;
			while(x->left != nullptr) {
				x = x->left;
			} 
		} else {
			TreeNodeBase* y = x->parent;
			while (x == y->right) {
				x = y;
				y = y->parent;
			}
			if (x->right != y) {
				x = y;
			}
		}
		return x;	
	}
	
	TreeNodeBase* tree_decrement(TreeNodeBase* x) {
		if (x->left != nullptr) {
			TreeNodeBase* y = x->left;
			while (y->right) {
				y = y->right;
			}
			x = y;
		} else {
			TreeNodeBase* y = x->parent;
			while (x == y->left) {
				x = y;
				y = y->parent;
			}	
			x = y;
		}
		return x;
	}

	void insert_and_rebalance(const bool insert_left,
					TreeNodeBase* x,
					TreeNodeBase* p,
					TreeNodeBase& header) {
		TreeNodeBase*& root = header.parent;
		x->parent = p;
		x->left = nullptr;
		x->right = nullptr;

		if (insert_left) {
			p->left = x;
			if (p == &header) {
				header.parent = x;
				header.right = x;
			} else if (p == header.left) {
				header.left = x;
			}
		} else {
			p->right = x;
			if (p == header.right) {
				header.right = x;
			}
		}

	}

	template <typename T>
	struct Iterator {
		typedef TreeNodeBase* base_ptr;
		typedef TreeNode<T>* node_ptr;
		typedef Iterator<T> Self;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;

		Iterator(): current() {}
		explicit Iterator(base_ptr x): current(x) {}

		reference operator*() const {
			return *static_cast<node_ptr>(current)->valptr();
		}

		pointer operator->() const {
			return static_cast<node_ptr>(current)->valptr();
		}

		Self& operator++() {
			current = tree_increment(current);
			return *this;
		}

		Self& operator--() {
			current = tree_decrement(current);
			return *this;
		}

		friend bool operator!=(const Self& x, const Self& y) {
			return x.current != y.current;
		}

		friend bool operator==(const Self& x, const Self& y) {
			return x.current == y.current;
		}


		base_ptr current;
	};

	struct TreeHeader
	{
		TreeNodeBase header;
		TreeHeader() {
			reset();
		}
		explicit TreeHeader(TreeHeader&& x) {
			if (x.header.parent != nullptr) {
				move_data(x);
			} else {
				reset();
			}
		}
		void move_data(TreeHeader& from) {
			header.parent = from.header.parent;
			header.left = from.header.left;
			header.right = from.header.right;
			header.parent->parent = &header;

			from.reset();
		}
		
		void reset() {
			header.parent = nullptr;
			header.left = &header;
			header.right = &header;
		}
	};

	template <typename Key, typename Val, typename KeyOfValue,
			 typename Compare>
	class Tree {
	protected:
		typedef Key key_type;
		typedef Val value_type;
		typedef TreeNode<Val>* node_ptr;
		typedef const TreeNode<Val>* const_node_ptr;
		typedef TreeNodeBase* base_ptr;
		typedef const TreeNodeBase* const_base_ptr;
		typedef Iterator<Val> iterator;
	
	private:
		node_ptr get_node() {
			return new TreeNode<Val>();
		}

		void del_node(node_ptr p) {
			delete p;
		}

		void construct_node(node_ptr node, const value_type& value) {
			node->value = value;
		}

	
	private:
		node_ptr _begin() {
			return static_cast<node_ptr>(this->header.header.parent);
		}

		base_ptr _end() {
			return &this->header.header;
		}

		key_type node_key(base_ptr x) {
			return KeyOfValue()(*(static_cast<node_ptr>(x)->valptr()));
		}

	private:

		key_type keyof(value_type& value) {
			return KeyOfValue()(value);
		}

		node_ptr get_left(base_ptr x) {
			return static_cast<node_ptr>(x->left);
		}
	
		node_ptr get_right(base_ptr x) {
			return static_cast<node_ptr>(x->right);
		}


		Tree<Key, Val, KeyOfValue, Compare>::iterator 
			insert_node(base_ptr x, base_ptr p, value_type value) {
			bool insert_left = (x != nullptr || p == _end()	||
							Compare()(KeyOfValue()(value), node_key(p)));
			node_ptr z = get_node();
			construct_node(z, value);
			insert_and_rebalance(insert_left, z, p, this->header.header);
			return iterator(z);
		}

		Pair<typename Tree<Key, Val, KeyOfValue, Compare>::iterator, bool> 
			insert_unique(value_type& value) {
			typedef Pair<iterator, bool> Res;
			Pair<base_ptr, base_ptr> res = get_insert_pos(KeyOfValue()(value));
			if (res.y) {
				return Res(insert_node(res.x, res.y, value), true);
			}
			iterator it(res.x);
			bool bres = false;
			return Res(it, bres);
		}
	
	public:
		

	public:
		iterator begin() { 
			return iterator(this->header.header.left); 
		}
		iterator end() { 
			return iterator(&this->header.header); 
		}

		iterator insert(Val val) {
			return insert_unique(val).x;
		}		
	
	protected:
		Pair<base_ptr, base_ptr> get_insert_pos(const key_type k) {
			typedef Pair<base_ptr, base_ptr> Res;			
			node_ptr x = _begin();
			auto y = _end();
			bool comp = true;
			while (x != nullptr) {
				y = x;
				comp = Compare()(k, node_key(x));
				x = comp ? get_left(x) : get_right(x);
			}
			iterator j = iterator(y);
			if (comp) {
				if (j == begin()) {
					return Res(x, y);
				} else {
					--j;
				}
			}
			if (Compare()(node_key(j.current), k)) {
				return Res(x, y);
			}

			return Res(j.current, 0);
		}

	private:
		node_ptr root;
		TreeHeader header;
	};

}
