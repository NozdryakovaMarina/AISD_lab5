#pragma once

#include <iostream>
#include <stdexcept> 
#include <vector>

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
		size_t _size;
		size_t hash(K k) const {
			return k % _size;
		}
	public:
		UnorderedMap(): _size(0) {
			_data.resize(_default_size);
		}

		UnorderedMap(size_t size): _size(0) {
			_data.resize(size); 
		}

		UnorderedMap(const UnorderedMap<K, V>& other) : _data(other._data), _size(other._size) {}

		~UnorderedMap() = default;

		size_t get_size() const { return _size; }

		UnorderedMap<K, V>& operator=(const UnorderedMap<K, V>& other) {
			if (this != other) {
				_data = other._data;
				_size = other._size;
			}
			return *this;
		}

		void print() const {
			for (auto& c : _data) {
				c.print();
			}
		}

		void insert(K k, V v) {
			if (contains(k)) return;
			size_t index = hash(k);
			if (_data[index].state != exist) {
				_data[index].key = k;
				_data[index].val = v;
				_data[index].state = exist;
				_size++;
			}
			else {
				size_t i = 1;
				while (_data[index].state == exist) {
					index = (index + i) % _data.size();
					if (index == hash(k)) return;
					if (_data[index].state != exist) {
						_data[index].key = k;
						_data[index].val = v;
						_data[index].state = exist;
						_size++;
					}
					i++;
				}
			}
		}

		bool contains(V v) const {
			for (auto& c : _data) {
				if (c.val == v) return true;
			}
			return false;
		}
	};
}