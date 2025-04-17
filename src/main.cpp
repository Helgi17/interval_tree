#include <iostream>
#include "simpletree.h"
#include "interval.h"

template <typename Key>
struct keyOfValue {
	template <typename Val>
	Key operator()(const Val& x){ 
			return static_cast<Key>(x);
	};
};

struct key_comp {
	template <typename T>
	bool operator()(const T& a, const T& b){ 
		return a < b; 
	};
};

int main()
{
	SimpleTree::Tree<int, int, 
			keyOfValue<int>,	
			key_comp > tree;
	if (tree.begin() != tree.end()) {
		std::cout << "asdf" << std::endl; //*(tree.begin()) << std::endl;
//		std::cout << tree.end() << std::endl;
	}
	std::cout << "insert " << *(tree.insert(1)) << std::endl;
	std::cout << "insert " << *(tree.insert(2)) << std::endl;
	std::cout << "insert " << *(tree.insert(4)) << std::endl;
	std::cout << "insert " << *(tree.insert(3)) << std::endl;
	if (tree.begin() != tree.end()) {
		std::cout << "fda" << std::endl;
		std::cout << *(tree.begin()) << std::endl << std::endl;
	}
	tree.erase(tree.begin());
	for (auto it = tree.begin(); it != tree.end(); ++it) {
		std::cout << *it << std::endl;
	}

	NSInterval::Interval<int> interval1(1, 10), interval2(21, 22),
			interval3(12, 19);
	std::cout << "intervals compare " << 
			NSInterval::Compare()(interval2, interval1) <<
			std::endl;
	SimpleTree::Tree<int, NSInterval::Interval<int>,
			NSInterval::KeyOfValue<int>,
			key_comp> intervalTree;
	intervalTree.insert(interval1);
	intervalTree.insert(interval2);
	intervalTree.insert(interval3);
	intervalTree.erase(intervalTree.begin());
	NSInterval::Interval<int> intervalt = *(++intervalTree.begin());
	std::cout << intervalt.leftborder << std::endl;

	return 0;
}
