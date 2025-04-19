#include <iostream>
#include <optional>
#include "simpletree.h"
#include "interval.h"

using Interval = NSInterval::Interval<int>;

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
	std::optional<Interval> interval1 = Interval::create(1, 10);
	std::optional<Interval> interval2 = Interval::create(21, 22);
	std::optional<Interval> interval3 = Interval::create(12, 19);

	SimpleTree::Tree<Interval, Interval,
			NSInterval::KeyOfValue<Interval>,
			NSInterval::Compare> intervalTree;
	
	if (interval1) intervalTree.insert(*interval1);
	if (interval2) intervalTree.insert(*interval2);
	if (interval3) intervalTree.insert(*interval3);

	// Find existing
	std::optional<Interval> i12 = Interval::create(12);
	auto itf = intervalTree.find(*i12);
	std::cout << "find " << (*itf).leftborder << ", " <<
		   (*itf).rightborder << std::endl;
	
	// Erase first
	intervalTree.erase(intervalTree.begin());
	
	// Get second
	Interval intervalt = *(++intervalTree.begin());
	
	std::cout << intervalt.leftborder << ", " <<
		   intervalt.rightborder << std::endl;

	return 0;
}
