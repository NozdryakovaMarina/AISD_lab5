#include <gtest/gtest.h>
#include "hash_table.cpp"
#include <stdexcept>
#include <iostream>

using namespace hash_table;
using namespace std;

TEST(UnorderedMapTest, HashTablePrint) {
	UnorderedMap <char, int> a;
	a.print();
}

 