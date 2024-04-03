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
		size_t _count;
		double loadFactor = 0.7;

		size_t hash(K k) const {
			return k % _data.size();
		}

		void rehash() {
				vector<Pair<K, V>> newData; 
				newData.resize((int)(_data.size() * 2 + 1));
				_data = newData;
				for (auto& c : _data) insert(c.key, c.val);
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
				while (true) {
					index = (index + i) % _data.size();
					if (index == hash(key)) return nullptr;
					if (_data[index].key == key) return &_data[index].val;
					i++;
				}
			} 
		}

		void insert(K key, V val) {
			if (search(key) != nullptr) return;
			size_t index = hash(key);
			if (_data[index].state != exist) {
				_data[index].key = key;
				_data[index].val = val;
				_data[index].state = exist;
				_count++;
				if (_count / _data.size() >= loadFactor) rehash(); 
			}
			else {
				int i = 1;
				while (_data[index].state != empty) {
					index = (index + i) % _data.size();
					if (index == hash(key)) return;
					if (_data[index].state != exist) {
						_data[index].key = key;
						_data[index].val = val;
						_data[index].state = exist;
						_count++;
						if (_count / _data.size() >= loadFactor) rehash();
					}
					i++;
				} 
			}
		}

		void insert_or_assign(K key, V val) {
			size_t index = hash(key);
			if (search(key) != nullptr) return;
			if (_data[index].state != exist) {
				_data[index].state = exist;
				_count++;
				if (_count / _data.size() >= loadFactor) rehash();
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

		size_t get_count() const { return _count; }

		size_t size() const { return _data.size(); }

		size_t count(K key) {
			size_t cnt = 0;
			for (auto& c : _data) {
				if (hash(c.key) == hash(key)) cnt++;
			}
			return cnt;
		}
	};
}