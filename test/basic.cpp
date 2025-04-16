#include <gtest/gtest.h>
#include "simpletree.h"


TEST(Basic, BeginEnd) {
	SimpleTree::Tree<int> tree;
	EXPECT_EQ(tree.begin()!=tree.end(), false);
}
