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

	int height(TreeNodeBase* node) {
		if (nullptr == node) return 0;
		return node->height;
	}

	void update_height(TreeNodeBase* node) {
		node->height = 
			std::max(height(node->left), height(node->right)) + 1;
	}

	int bf(TreeNodeBase* node) {
		if (nullptr == node) return 0;
		return height(node->left) - height(node->right);
	}

	TreeNodeBase* rotateRight(TreeNodeBase* node) {
		if (nullptr == node || nullptr == node->left) return node;
		TreeNodeBase* tmp = node->left;
		tmp->parent = node->parent;
		node->parent = tmp;
		node->left = tmp->right;
		if (nullptr != tmp->right) {
			tmp->right->parent = node;
		}
		tmp->right = node;

		update_height(tmp);
		update_height(node);

		return tmp;
	}

	TreeNodeBase* rotateLeft(TreeNodeBase* node) {
		if (nullptr == node || nullptr == node->right) return node;
		TreeNodeBase* tmp = node->right;
		tmp->parent = node->parent;
		node->parent = tmp;
		node->right = tmp->left;
		if (nullptr != tmp->left) {
			tmp->left->parent = node;
		}
		tmp->left = node;

		update_height(tmp);
		update_height(node);

		return tmp;
	}		

	TreeNodeBase* balance(TreeNodeBase* node) {
		if (nullptr == node) return node;
		update_height(node);

		if (bf(node) == 2) {
			if (bf(node->left) < 0) {
				node->left = rotateLeft(node->left);
			}	
			return rotateRight(node);
		} else if (bf(node) == -2) {
			if (bf(node->right) > 0) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		}
		return node;
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

		while (x != root) {
			if (x->parent->left == x) {
				x = balance(x);
				x->parent->left = x;
			} else {
				x = balance(x);
				x->parent->right = x;
			}
			x = x->parent;
		}
		x = balance(x);
		header.parent = x;
	}

	TreeNodeBase* get_min(TreeNodeBase* node) {
		while (nullptr != node->left) {
			node = node->left;
		}
		return node;
	}

	TreeNodeBase* rebalance_for_erase(
					TreeNodeBase* const z, TreeNodeBase& header) {

		TreeNodeBase* parent = z->parent;
		TreeNodeBase* left = z->left;
		TreeNodeBase* right = z->right;
		TreeNodeBase*& leftmost = header.left;
		TreeNodeBase*& rightmost = header.right;

		if (nullptr == left && 
			nullptr == right && 
			parent == &header) {
			header.parent = nullptr;
			header.left = &header;
			header.right = &header;
			return z;
		}

		TreeNodeBase* min = nullptr;
		if (nullptr == right) {
			min = left;
			if (nullptr != left) {
				left->parent = parent;
			}
		} else {
			min = get_min(right);

			if (min != right) {
				min->parent->left = min->right;
				if (nullptr != min->right) {
					min->right->parent = min->parent;
				} 
				right->parent = min;
				min->right = right;
			}
			
			if (nullptr != left)
				left->parent = min;	
			min->left = left;
			
			TreeNodeBase* x = min->parent;
			if (min != right) {
				while (x != right) {
					x = balance(x);
					x->parent->left = x;
					x = x->parent;
				}
			}
			min->parent = parent;
			balance(min);
		}

		if (parent != &header) {
			if (z == parent->left)
				parent->left = min;
			else
				parent->right = min;
		} else {
			parent->parent = min;
		}
		header.right = TreeNodeBase::sMaximum(header.parent);
		header.left = TreeNodeBase::sMinimum(header.parent);

		if (nullptr == min) min = parent; // only if right == nullptr
		while (min != header.parent) {
			if (min->parent->left == min) {
				min = balance(min);
				min->parent->left = min;
			} else {
				min = balance(min);
				min->parent->right = min;
			}
			min = min->parent;
		}
		min = balance(min);
		header.parent = min;

		return z;
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
	
	public:
		typedef Iterator<Val> iterator;
	
	private:
		node_ptr get_node() {
			std::allocator<TreeNode<Val>> alloc;
			return std::allocator_traits<std::allocator<TreeNode<Val>>>::
					allocate(alloc, 1);
		}

		void drop_node(node_ptr p) {
			std::allocator<TreeNode<Val>> alloc;
			std::allocator_traits<std::allocator<TreeNode<Val>>>::
					deallocate(alloc, p, 1);
		}

		void construct_node(node_ptr node, const value_type& value) {
			if constexpr (!std::is_trivially_destructible_v<value_type>) {
				node->value.~value_type();
			}
			new (&node->value) value_type(value);
			node->height = 0;
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

	public:
		Pair<typename Tree<Key, Val, KeyOfValue, Compare>::iterator, bool> 
			insert_unique(const value_type& value) {
			typedef Pair<iterator, bool> Res;
			Pair<base_ptr, base_ptr> res = get_insert_pos(KeyOfValue()(value));
			if (res.y) {
				return Res(insert_node(res.x, res.y, value), true);
			}
			return Res(iterator(res.x), false);
		}

		Pair<typename Tree<Key, Val, KeyOfValue, Compare>::iterator, bool> 
		insert_at(iterator x, iterator p, const value_type& value) {
			typedef Pair<iterator, bool> Res;
			if (nullptr != p.current) {
				return Res(insert_node(x.current, p.current, value), true);
			}
			return Res(x, false);
		}
	
	public:
		

	public:
		iterator begin() { 
			return iterator(this->header.header.left); 
		}
		iterator end() { 
			return iterator(&this->header.header); 
		}

		iterator find(const Key& key) {
			Pair<base_ptr, base_ptr> res = get_insert_pos(key);
			if (nullptr != res.x) return iterator(res.x);
			return end();
		}

		Pair<iterator, iterator> find_place(const Key& key) {
			Pair<base_ptr, base_ptr> res = get_insert_pos(key);
			return Pair(iterator(res.x), iterator(res.y));
		}

		iterator insert(Val val) {
			return insert_unique(val).x;
		}		

		void erase(iterator position) {
			node_ptr y = static_cast<node_ptr>(
					rebalance_for_erase(position.current,
					this->header.header));
			drop_node(y);
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
