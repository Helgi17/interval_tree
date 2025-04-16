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
		return x;	
	}
	
	TreeNodeBase* tree_decrement(TreeNodeBase* x) {
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

		friend bool operator!=(const Self& x, const Self& y) {
			return x.current != y.current;
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
			header.parent = 0;
			header.left = &header;
			header.right = &header;
		}
	};

	template <typename T>
	class Tree {
	protected:
		typedef T value_type;
		typedef TreeNode<T>* node_ptr;
		typedef TreeNodeBase* base_ptr;
		typedef Iterator<T> iterator;

	public:
		iterator begin() { 
			return iterator(this->header.header.left); 
		}
		iterator end() { 
			return iterator(&this->header.header); 
		}

		iterator insert(T val) {
			return iterator(&this->header.header);
		}		
	
	protected:
		node_ptr get_node() {
			return new TreeNode<T>();
		}

		void del_node(node_ptr p) {
			delete p;
		}

		void construct_node(node_ptr node, const value_type& value) {
			node->value = value;
		}

		Pair<base_ptr, base_ptr> get_insert_pos(const value_type& value) {
			Pair<base_ptr, base_ptr> p(nullptr, nullptr);			
			return p;
		}

	private:
		node_ptr root;
		TreeHeader header;
	};

}
