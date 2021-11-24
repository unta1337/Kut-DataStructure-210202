/*
 * @copyright 헌귝기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author: 김상진
 * HashMap.h
 * 해시 테이블을 이용한 맵 자료구조
 * 해시 태이블은 chaining 기법 이용
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <utility>
#include <functional>
#include <unordered_set>
#include "HashTableIterator.h"

template <typename K, typename V>
class HashMap {
private:
	using Pair = std::pair<K,V>;
	size_t tableSize;
	std::vector<std::list<Pair>> table;
	size_t numItems{0};
	std::function<size_t(K)> hash;
public:
	HashMap(size_t tableSize, const std::function<size_t(K)>& hash):
		tableSize{tableSize}, table(tableSize), hash{hash}{}
	virtual ~HashMap() = default;

	HashMap(HashMap<K,V>&& tmp) = default;
	HashMap<K,V>& operator=(HashMap<K,V>&& tmp) = default;

	bool isEmpty() const noexcept{
		return numItems==0;
	}
	bool isFull() const noexcept{
		return false;
	}
	size_t size() const noexcept{
		return numItems;
	}
	size_t capacity() const noexcept{
		return tableSize;
	}
	const std::function<size_t(K)>& hash_function() const noexcept{
		return hash;
	}

	typename std::list<Pair>::iterator getIterator(size_t index, const K& key){
		for(auto it{table[index].begin()}; it!=table[index].end(); ++it){
			if(it->first == key) return it;
		}
		return table[index].end();
	}

	typename std::list<Pair>::const_iterator getIterator(size_t index, const K& key) const{
		for(auto it{table[index].cbegin()}; it!=table[index].cend(); ++it){
			if(it->first == key) return it;
		}
		return table[index].cend();
	}

	void put(const K& key, const V& value){
		int index = getIndex(key);
		auto it = table[index].begin();

		while (1)
		{
			if (it->first == key)
			{
				it->second = value;
				return;
			}

			it++;

			if (it == table[index].end())
				break;
		}

		table[index].push_back(std::pair<K, V> {key, value});
		numItems++;
	}

	bool containsKey(const K& key) const noexcept{
		auto outer = table.begin();

		while (1)
		{
			auto inner = outer->begin();

			while (1)
			{
				if (inner->first == key)
					return true;

				inner++;

				if (inner == outer->end())
					break;
			}

			outer++;

			if (outer == table.end())
				break;
		}

		return false;
	}

	const V& get(const K& key) const{
		auto outer = table.begin();

		while (1)
		{
			auto inner = outer->begin();

			while (1)
			{
				if (inner->first == key)
					return inner->second;

				inner++;

				if (inner == outer->end())
					break;
			}

			outer++;

			if (outer == table.end())
				break;
		}

		throw std::runtime_error("HashMap: get, key does not exists");
	}

	void remove(const K& key) noexcept{
		if (!containsKey(key))
			return;

		auto value = get(key);

		table[getIndex(key)].remove(std::pair<K, V>{key, value});
		numItems--;
	}

	std::unordered_set<K> getKeySet() const noexcept{
		std::unordered_set<K> set;
		for(size_t i=0; i<tableSize; ++i){
			if(!table[i].empty()){
				for(auto& entry: table[i]) set.insert(entry.first);
			}
		}
		return set;
	}
	std::unordered_set<V> getValueSet() const noexcept{
		std::unordered_set<V> set;
		for(size_t i=0; i<tableSize; ++i){
			if(!table[i].empty()){
				for(auto& entry: table[i]) set.insert(entry.second);
			}
		}
		return set;
	}
	void debugPrint(){
		for(size_t i=0; i<tableSize; ++i){
			std::cout << i << ": ";
			if(table[i].empty()) std::cout << "empty\n";
			else{
				for(auto& key: table[i])
					std::cout << key << ", ";
				std::cout << '\n';
			}
		}
	}

	auto begin() {return TableIterator<Pair>(table.begin(), table.end());}
	auto end() {return TableIterator<Pair>(table.end(), table.end());}
	auto begin() const {return TableConstIterator<Pair>(table.cbegin(), table.cend());}
	auto end() const {return TableConstIterator<Pair>(table.cend(), table.cend());}
private:
	bool needCapacityExpansion() const noexcept{
		return static_cast<double>(numItems)/tableSize>0.7;
	}

	std::vector<Pair> getEntryList(){
		std::vector<Pair> keyList;
		keyList.reserve(numItems);
		for(auto list: table){
			if(!list.empty())
				for(auto key: list) keyList.push_back(key);
		}
		return keyList;
	}

	void increaseCapacity(){
		std::vector<Pair> entryList{getEntryList()};
		tableSize = tableSize*2+1;
		numItems = 0;
		table.clear();
		table.resize(tableSize);
		for(auto& entry: entryList) put(entry.first, entry.second);
	}
	size_t getIndex(const K& key) const noexcept{
		return hashInteger(hash(key));
	}
	size_t hashInteger(size_t x) const noexcept{
		constexpr static size_t P{4210098769L};
		constexpr size_t a{42283};
		constexpr size_t b{44267};
		size_t value = (a*x + b) % P;
		return value % tableSize;
	}
};

#endif /* HASHMAP_H_ */
