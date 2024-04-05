#include <gtest/gtest.h>
#include "hash_table.cpp"
#include <stdexcept>
#include <iostream>

using namespace hash_table;
using namespace std;

TEST(UnorderedMapTest, HashTableInsert) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.print();
}

TEST(UnorderedMapTest, HashTableInsert2) {
	UnorderedMap <int, int> a(10);
	a.insert(1, 15);
	a.insert(1, 9);
	a.print(); 
}

TEST(UnorderedMapTest, HashTableSearch) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	int res = *a.search('N');
	EXPECT_EQ(res, 15);
}

TEST(UnorderedMapTest, HashTableInsertOrAssign) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 1);
	a.print();
	a.insert_or_assign('X', 14);
	cout << "------------" << endl;
	a.print();
}

TEST(UnorderedMapTest, HashTableInsertOrAssign2) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 1);
	a.print();
	a.insert_or_assign('M', 14);
	cout << "------------" << endl;
	a.print();
}

TEST(UnorderedMapTest, HashTableContains) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 14);
	a.insert('A', 1);
	EXPECT_TRUE(a.contains(1));
}

TEST(UnorderedMapTest, HashTableContains2) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 14);
	a.insert('A', 1);
	EXPECT_FALSE(a.contains(-66));
}

TEST(UnorderedMapTest, HashTableOperatorAssignments) {
	UnorderedMap <char, int> a;
	a.insert('N', 15);
	a.insert('M', 1);
	a.print();
	UnorderedMap<char, int> b = a;
	cout << "------------" << endl;
	b.print();
}

TEST(UnorderedMapTest, HashTableCount) {
	UnorderedMap<char, int> a(7);
	a.insert('A', 1);
	a.insert('B', 10);
	a.insert('C', 1);
	a.insert('W', 10);
	EXPECT_EQ(a.count('W'), 2);
}


TEST(UnorderedMapTest, HashTableCopy) {
	UnorderedMap<int, int> a(7);
	a.insert(1, 1);
	a.insert(2, 148);
	a.insert(3, 1);
	a.insert(4, 15);
	a.print();
	UnorderedMap<int, int> b(a);
	cout << "------------" << endl;
	b.print();
}

TEST(UnorderedMapTest, HashTableSize) {
	UnorderedMap<int, int> a(10);
	cout << a.size() << endl;
}

TEST(UnorderedMapTest, HashTableErase) {
	UnorderedMap<int, int> a;
	a.insert(1, 1);
	a.insert(2, 148);
	a.insert(3, -5);
	a.insert(4, 15);
	a.print();
	a.erase(2);
	cout << "------------" << endl;
	a.print();
}

TEST(UnorderedMapTest, HashTableErase2) {
	UnorderedMap<int, int> a;
	a.insert(1, 1);
	a.insert(2, 148);
	a.insert(3, -5);
	a.insert(4, 15);
	a.print();
	EXPECT_FALSE(a.erase(100));
}

TEST(HashPearsonTest, CompareHash) {
	string a = "blossom";
	string b = "blossom"; 
	EXPECT_TRUE(compareHashes(a, b));
}

TEST(HashPearsonTest, CompareHash2) {
	string a = "sunshine";
	string b = "blossom";
	EXPECT_FALSE(compareHashes(a, b));
}

TEST(UnorderedMapTest, HashTableCollision) {
	UnorderedMap<int, int> a(10);
	a.insert(1, 1);
	a.insert(2, 148);
	a.insert(41, 15);
	a.insert(4, -5);
	a.print();
}