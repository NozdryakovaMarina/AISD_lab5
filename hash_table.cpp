#pragma once

#include <iostream>
#include <stdexcept> 
#include <vector>
#include <random>

using namespace std;

namespace hash_table {

	template <typename K, typename V>
	class UnorderedMap {
	private:
		const int _default_size = 15;
		enum State { empty = 0, exist = 1, deleted = 2 };

		template <typename K, typename V>
		struct Pair {
			K key;
			V val;
			State state;
			Pair() : key(K()), val(V()), state(empty) {}
			void print() const {
				if (state == exist)
					cout << "Key: " << key << " | Value: " << val << endl; 
			} 
		};

		vector<Pair<K, V>> _data;
		size_t _count;
		double loadFactor = 0.7;

		size_t hash(K key) const {
			return key % _data.size();
		}

		void rehash() {
			vector<Pair<K, V>> newData;
			newData.resize((int)(_data.size() * 2 + 1));
			for (auto& c : _data) insert(c.key, c.val);
			_data = newData;
		}
	public:
		UnorderedMap(): _count(0) {
			_data.resize(_default_size);
		}

		UnorderedMap(size_t size): _count(0) {
			_data.resize(size); 
		}

		UnorderedMap(const UnorderedMap<K, V>& other) : _data(other._data), _count(other._count) {}

		~UnorderedMap() {
			clear();
		}

		void clear() {
			_data.clear();
			_count = 0;
		}

		UnorderedMap<K, V>& operator=(const UnorderedMap<K, V>& other) {
			if (this != other) {
				_data = other._data;
				_count = other._count;
			}
			return *this;
		}

		void print() const {
			for (auto& c : _data) {
				c.print();
			}
		}

		V* search(K key) {
			size_t index = hash(key);
			if (_data[index].key == key) return &_data[index].val;
			else {
				int i = 1;
				while (_data[index].state != empty) {
					index = (index + i) % _data.size();
					if (index == hash(key)) return nullptr;
					if (_data[index].key == key) return &_data[index].val;
					i++;
				}
			} 
			return nullptr;
		}

		void insert(K key, V val) {
			size_t index = hash(key);
			int i = 1; 
			if (search(key) != nullptr) return;
			while (_data[index].state != empty ) {
				index = (index + i) % _data.size(); 
				if (index == hash(key)) return;
				i++;
			}
			_data[index].key = key;
			_data[index].val = val;
			_data[index].state = exist;
			_count++;
			if (_count / _data.size() >= loadFactor) rehash();
		}

		void insert_or_assign(K key, V val) {
			size_t index = hash(key);
			if (_data[index].state != exist) {
				_data[index].state = exist;
				_count++;
				if (_count / _data.size() >= 0.7) rehash();
			}
			_data[index].key = key;
			_data[index].val = val;  
		}

		bool contains(V val) const {
			for (auto& c : _data) {
				if (c.state == exist) {
					if (c.val == val) return true;
				}
			}
			return false;
		}

		bool erase(K key) {
			if (!search(key)) return false;
			size_t index = hash(key);
			if (_data[index].key == key) {
				_data[index].state = deleted;
				_data[index].key = K();
				_data[index].val = V();
				_count--;
				return true;
			}
			else {
				int i = 1;
				while (true) {
					index = (index + i) % _data.size();
					if (_data[index].key == key) {
						_data[index].state = deleted;
						_data[index].key = K();
						_data[index].val = V();
						_count--;
						return true;
					}
					if (index == hash(key)) return false;
				}
				i++;
			}
		}

		size_t count() const { return _count; }

		size_t size() const { return _data.size(); }

		size_t count(K key) {
			size_t cnt = 0;
			for (auto& c : _data) {
				if (c.state == exist) {
					if (hash(c.key) == hash(key)) cnt++;
				}
			}
			return cnt;
		} 
	};

	unsigned char hashPearson(const string& str) {
		static const unsigned char T[256] = {
			 98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
			 61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
			 90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
			237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
			123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
			 59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
			197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
			 39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
			154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
			133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
			189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
			183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
			221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
			  3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
			238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
			 43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
		};
		unsigned char hash = 0;

		for (auto& c : str)
			hash = T[hash ^ static_cast<unsigned char>(c)];
		return hash;
	}

	bool compareHashes(const string& str1, const string& str2) {
		if (hashPearson(str1) == hashPearson(str2)) return true;
		return false;
	}
}