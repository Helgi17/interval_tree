#pragma once

template <typename T, typename P>
struct Pair 
{
	Pair(): x(T()), y(P()) {}
	Pair(const T& x_, const P& y_): x(x_), y(y_) {}
	Pair(T&& x_, P&& y_): x(x_), y(y_) {}

	Pair& operator=(Pair& p) {
		x = p.x;
		y = p.y;
		return *this;
	}


	T x;
	P y;
};
