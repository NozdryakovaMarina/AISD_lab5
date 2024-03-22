#pragma once

#include <iostream>
#include <stdexcept>
#include <random>

using namespace std;

namespace hash_table {

	template<typename K, typename V>
	class HashTable {
	private:
		struct Pair {
			K key;
			V val;
			Pair() : key(K()), val(V()) {}
			Pair(K k, V v) : key(k), val(v) {}
		};
	};
}