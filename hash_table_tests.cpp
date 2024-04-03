#include <gtest/gtest.h>
#include "hash_table.cpp"
#include <stdexcept>
#include <iostream>

using namespace hash_table;
using namespace std;

TEST(UnorderedMapTest, HashTablePrint) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.print();
}

TEST(UnorderedMapTest, HashTableInsert) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	EXPECT_EQ(a.get_count(), 1);
}

TEST(UnorderedMapTest, HashTableSearch) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	int res = *a.search('N');
	EXPECT_EQ(res, 15);
}

TEST(UnorderedMapTest, HashTableInsertOrAssign) {
	UnorderedMap <char, int> a(3);
	a.insert('N', 15);
	a.insert('M', 1);
	a.print();
	a.insert_or_assign('M', 14);
	a.print();
}

TEST(UnorderedMapTest, HashTableContains) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 14);
	a.insert('A', 1);
	EXPECT_TRUE(a.contains(1));
}

TEST(UnorderedMapTest, HashTableOperatorAssignments) {
	UnorderedMap <char, int> a(3);
	a.insert('N', 15);
	a.insert('M', 1);
	a.print();
	UnorderedMap<char, int> b = a;
	cout << "------------" << endl;
	b.print();
}




 