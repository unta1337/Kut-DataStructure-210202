/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file SortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 정렬 정수 리스트
 * 코드 중복 제거
 */

// 2020136018 김성녕

#ifndef SORTEDARRAYLIST_H_
#define SORTEDARRAYLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <cstdlib>

class SortedArrayList {
	template <typename U>
	class ListIterator: public std::iterator<std::input_iterator_tag,U>{
        U *p;
    public:
        explicit ListIterator(U *p): p{p} {}
        const ListIterator& operator++() noexcept {++p; return *this;}
        ListIterator operator++(int) noexcept {auto retval{*this}; ++p; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        U& operator*() const noexcept {return *p;}
    };
private:
	// 검사 목적으로 용량을 작게 설정
	const static inline size_t MAX{10};
	//int items[MAX];
	size_t currentCapacity{1};
	size_t numItems{0};
	int* items = (int*)malloc(currentCapacity);

	void shiftLeft(size_t startIdx){
		for(size_t i{startIdx}; i<numItems-1; ++i)
			items[i] = items[i+1];
		--numItems;
	}
	// 이진 탐색
	// @return 있으면 해당 요소가 있는 색인, 없으면 해당 요소를 삽입할 위치
	size_t search(int item) const noexcept{
		size_t lo{0};
		size_t hi{numItems-1};
		while(lo<=hi){
			size_t mid{lo+(hi-lo)/2};
			if(items[mid]==item) return mid;
			else if(items[mid]>item){
				if(mid==0) return lo;
				hi = mid-1;
			}
			else lo = mid+1;
		}
		return lo;
	}

	// 내부적으로만 사용되는 메소드이므로 private 선언.

	// isFull()과는 별개로, 배열이 확장 가능할 때(용량이 MAX를 넘어서지 않음) 용량을 확장해야할지 판단하는 함수.
	bool shouldExpand() noexcept {
		return numItems==currentCapacity && !isFull();
	}

	void increaseCapacity() {
		if (!shouldExpand())
			return;

		currentCapacity = currentCapacity * 2 > MAX ? MAX : currentCapacity * 2;
		items = (int*)realloc(items, currentCapacity * sizeof(int));
	}

	void increaseCapacity(int cap) {
		if (!shouldExpand())
			return;

		currentCapacity = currentCapacity + cap > MAX ? MAX : currentCapacity + cap;
		items = (int*)realloc(items, currentCapacity * sizeof(int));
	}
public:
	explicit SortedArrayList() = default;
	explicit SortedArrayList(const std::initializer_list<int>& initList){
		auto it{initList.begin()};
		for(size_t i{0}; i<std::min(initList.size(),MAX); ++i){
			add(*it);
			++it;
		}
	}

	virtual ~SortedArrayList(){
		free(items);
	}

 	SortedArrayList(const SortedArrayList& sal){
		currentCapacity = sal.currentCapacity;
		numItems = sal.numItems;
		items = sal.items;
 	}

	SortedArrayList(SortedArrayList&& sal){
		currentCapacity = sal.currentCapacity;
		numItems = sal.numItems;
		items = sal.items;
	}

	const SortedArrayList& operator=(const SortedArrayList& sal){
		currentCapacity = sal.currentCapacity;
		numItems = sal.numItems;
		items = sal.items;

		return *this;
	}

	const SortedArrayList& operator=(SortedArrayList&& sal){
		currentCapacity = sal.currentCapacity;
		numItems = sal.numItems;
		items = sal.items;

		return *this;
	}

	bool isEmpty() const noexcept {
		return numItems==0;
	}

	bool isFull() noexcept {
		return numItems==MAX;
	}

	size_t size() const noexcept{
		return numItems;
	}

	// size()와는 별개로 현재 용량을 표시하는 함수.
	size_t cap() noexcept{
		return currentCapacity;
	}

	void clear() noexcept{
		numItems = 0;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems) return items[index];
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		--numItems;
		return items[numItems];
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{items[0]};
		shiftLeft(0);
		return ret;
	}

	void add(int item){
		if(isFull()) throw std::runtime_error("add: full state");

		// 확장이 필요하면 확장 수행.
		if(shouldExpand()) increaseCapacity();

		if(isEmpty()||items[numItems-1]<=item)
			items[numItems] = item;
		else{
			size_t insertLoc{search(item)};
			for(size_t i{numItems}; i>insertLoc; --i)
				items[i] = items[i-1];
			items[insertLoc] = item;
		}
		++numItems;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return items[0];
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: empty state");
		return items[numItems-1];
	}

	bool find(int item) const noexcept{
		if(isEmpty()) return false;
		return items[search(item)]==item;
	}

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(items[itemLoc]==item) shiftLeft(itemLoc);
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(items[itemLoc]==item){
			size_t lo{itemLoc};
			while(lo-1>=0 && items[lo-1]==item){
				--lo;
				if(lo==0) break;
			}
			size_t hi{itemLoc};
			while(hi+1<=numItems-1 && items[hi+1]==item) ++hi;
			for(size_t i{hi+1}, j{lo}; i<numItems; ++i, ++j)
				items[j] = items[i];
			numItems -= (hi-lo+1);
		}
	}

	auto begin() {return ListIterator<int>(items);}
	auto end() {return ListIterator<int>(items+numItems);}
	auto cbegin() const {return ListIterator<const int>(items);}
	auto cend() const {return ListIterator<const int>(items+numItems);}
};

#endif /* SORTEDARRAYLIST_H_ */
