#include <iostream>
#include "interval_map.h"
#include "interval.h"

using Interval = typename NSInterval::Interval<int>;
using KeyOfValue = typename NSInterval::KeyOfValue<int>;
using Compare = typename NSInterval::Compare;
using interval_map = NSIntervalMap::interval_map<Interval, int, KeyOfValue, Compare>;

void print(interval_map& m) {
	for (auto it=m.begin(); it != m.end(); ++it) {
		std::cout << (*it).y << " ";
	}
	std::cout << std::endl;
}

int main()
{
	interval_map imap;
	Interval i1(1, 10), i2(21,23), i3(0,0), i4(11, 20), i5(112);
	imap[i1] = 1;
	imap[{30, 32}] = -2;
	//imap.insert(i1, 1);
	imap.insert(i3, 3);
	imap.insert(i2, 2);
	imap.insert(i4, 5);
	imap.insert(i5, 6);
	std::cout << (imap.begin() == imap.end()) << std::endl;
	print(imap);

	std::cout << (*(++imap.begin())).y << std::endl;
	imap.erase((++imap.begin()));
	print(imap);

	imap.erase(imap.find({30, 32}));
	print(imap);

	imap.erase(imap.find(2));
	print(imap);

	imap.erase(imap.find(22));
	print(imap);
	return 0;
}
