#include <iostream>
#include "interval_map.h"
#include "interval.h"

using Interval = typename NSInterval::Interval<int>;
using KeyOfValue = typename NSInterval::KeyOfValue<int>;
using Compare = typename NSInterval::Compare;
using interval_map = NSIntervalMap::interval_map<Interval, int, KeyOfValue, Compare>;

int main()
{
	interval_map imap;
	Interval i1(1, 20), i2(21,23), i3(0,0);
	imap[i1] = 1;
	imap[{30, 32}] = -2;
	//imap.insert(i1, 1);
	imap.insert(i3, 3);
	imap.insert(i2, 2);
	std::cout << (imap.begin() == imap.end()) << std::endl;
	for (auto it = imap.begin(); it != imap.end(); ++it) {
		std::cout << (*it).y << std::endl;
	}
	return 0;
}
