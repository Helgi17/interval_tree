#pragma once

#include <optional>

namespace NSInterval
{
template <typename T>
class Interval
{
public:
	static::std::optional<Interval> create(T begin, T end) noexcept {
		if (begin > end) {
			return std::nullopt;
		}
		return Interval(begin, end);	
	}

	static::std::optional<Interval> create(T value) noexcept {
		return Interval(value, value);	
	}

	T leftborder;
	T rightborder;

private:
	Interval(T left, T right): leftborder(left), rightborder(right) {}

};

	struct Compare {
		template <typename T> 
		bool operator()(const Interval<T>& a, const Interval<T>& b) {
			return (a.rightborder < b.leftborder);
		}
	};

	template <typename Key>
	struct KeyOfValue {
		template <typename T>
		Key operator()(const Interval<T>& a){
			return static_cast<Key>(a);
		}
	};
}
