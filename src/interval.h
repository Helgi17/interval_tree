#pragma once

namespace NSInterval
{
template <typename T>
class Interval
{
public:
	Interval(T left, T right): leftborder(left), rightborder(right) {}
	Interval(): leftborder(0), rightborder(0) {};

	T leftborder;
	T rightborder;
};

	struct Compare {
		template <typename T> 
		bool operator()(Interval<T>& a, Interval<T>b) {
			return (a.leftborder < b.leftborder);
		}
	};

	template <typename Key>
	struct KeyOfValue {
		template <typename T>
		Key operator()(const Interval<T>& a){
			return static_cast<Key>(a.leftborder);
		}
	};
}
