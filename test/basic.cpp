#include <gtest/gtest.h>
#include "simpletree.h"

template <typename Key, typename Val>
struct KeyOfValue
{
	Key operator()(Val x) { return x; }
};

template <typename Key>
struct key_comp
{
	bool operator()(Key& a, Key& b) { return a < b; }
};

TEST(Basic, BeginEnd) {
	SimpleTree::Tree<int, int, KeyOfValue<int, int>, key_comp<int>> tree;
	EXPECT_EQ(tree.begin()!=tree.end(), false);
}
