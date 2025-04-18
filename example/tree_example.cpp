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
	NSInterval::Interval<int> interval1(1, 10), 
			interval2(21, 22),
			interval3(12, 19);

	SimpleTree::Tree<NSInterval::Interval<int>, NSInterval::Interval<int>,
			NSInterval::KeyOfValue<NSInterval::Interval<int>>,
			NSInterval::Compare> intervalTree;
	
	intervalTree.insert(interval1);
	intervalTree.insert(interval2);
	intervalTree.insert(interval3);

	// Find existing
	auto itf = intervalTree.find(12);
	std::cout << "find " << (*itf).leftborder << ", " <<
		   (*itf).rightborder << std::endl;
	
	// Erase first
	intervalTree.erase(intervalTree.begin());
	
	// Get second
	NSInterval::Interval<int> intervalt = *(++intervalTree.begin());
	
	std::cout << intervalt.leftborder << ", " <<
		   intervalt.rightborder << std::endl;

	return 0;
}
