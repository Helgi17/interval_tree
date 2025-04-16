#pragma once

struct TreeNodeBase
{
	typedef TreeNodeBase* base_ptr;

	base_ptr parent;
	base_ptr left;
	base_ptr right;	

	static base_ptr sMinimum(base_ptr x) {
		while (x->left != nullptr) x = x->left;
		return x;
	}

	static base_ptr sMaximum(base_ptr x) {
		while (x->right != nullptr) x = x->right;
		return x;
	}
};
