#include <iostream>
#include "simpletree.h"
#include <map>

int main()
{
	std::map<int, int> m;
	SimpleTree::Tree<int> tree;
	if (tree.begin() != tree.end()) {
		std::cout << "asdf" << std::endl; //*(tree.begin()) << std::endl;
//		std::cout << tree.end() << std::endl;
	}
	return 0;
}
