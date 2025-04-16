#pragma once

template <typename T, typename P>
struct Pair 
{
	Pair(T& x_, P&y_):x(x_), y(y_) { }

	T x;
	P y;
};
