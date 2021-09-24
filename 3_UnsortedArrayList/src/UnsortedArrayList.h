/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file UnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하는 방법으로 pushFront, popFront, remove를 구현함
 */

// 2020136018 김성녕

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

#include <iostream>

class UnsortedArrayList {

	template <typename U>

	class ListIterator : public std::iterator<std::input_iterator_tag, U> {
        U *p;

    public:
        explicit ListIterator(U *p) : p{p} {}

        const ListIterator& operator++() noexcept { ++p; return *this; }

        ListIterator operator++(int) noexcept { auto retval{ *this }; ++p; return retval; }

        bool operator==(const ListIterator& other) const noexcept { return p == other.p; }

        bool operator!=(const ListIterator& other) const noexcept { return p != other.p; }

        U& operator*() const noexcept { return *p; }
    };

private:
	// 검사 목적으로 용량을 작게 설정
	const static inline size_t MAX{10};
	int items[MAX];
	size_t numItems{0};			// 이 변수는 배열의 크기 또는 리스트의 크기를 나타내는 변수이지만, 동시에 push 명령이 들어왔을 때 원소를 넣을 인덱스로서도 활용할 수 있음.

	// remove 함수들의 코드 중복을 막기 위한 함수.
	// 내부적으로만 사용되는 메소드로 private로 선언.
	// 내부적으로 유효한 인덱스만 받도록 설계되므로 noexcept로 함수 선언.
	void remove(int index) noexcept {
		for (size_t i = index; i < numItems - 1; i++) {
			items[i] = items[i + 1];
		}

		numItems--;
	}

public:
	explicit UnsortedArrayList() = default;

	explicit UnsortedArrayList(const std::initializer_list<int>& initList) {
		// std::min 대신 삼항 연산자를 사용함으로써 함수 호출 시간을 단축함.
		numItems = initList.size() < MAX ? initList.size() : MAX;

		std::initializer_list<int>::iterator it{initList.begin()};
		for (size_t i = 0; i < numItems; i++) {
			items[i] = *it;
			it++;
		}
	}

	virtual ~UnsortedArrayList() = default;

	void debugPrint() {
		std::cout << "numItems: " << numItems << '\n';
		std::cout << "{ ";
		for(size_t i = 0; i < MAX; ++i)
			std::cout << items[i] << " ";
		std::cout << "}\n";
	}

	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	bool isFull() const noexcept {
		// MAX == 10이고 배열의 인덱스는 0부터 시작하므로 우리가 원소를 넣고자 하는 인덱스인 numItems가 9 초과가 되면 배열이 꽉 찬 것으로 간주함.
		// 9 초과 == 10 이상 == MAX 이상.
		return numItems >= MAX;
	}

	// std::exeption을 상속하여 사용자 정의 예외 클래스를 만들고 싶었으나, 테스트에서 std::rumtime_error 또는 std::out_of_range만을 취급하여 테스트 통과가 불가능하다고 판단됨.
	// 아래의 함수들을 통해 해당 예외들을 처리할 수 있도록 함.
	// 예외의 종류가 같을 때 발생하는 코드의 중복도 중복이지만, 예외 메시지의 일관성을 위해 하나의 함수로 선언아하여 예외를 처리함.
	void pushValidCheck() const {
		if (isFull())
			throw std::runtime_error("리스트 인덱스 범위 예외: 리스트에 있는 원소의 개수가 최대입니다.");
	}

	void popValidCheck() const {
		if (isEmpty())
			throw std::runtime_error("리스트 인덱스 참조 예외: 리스트에 참조할 수 있는 원소가 없습니다.");
	}

	void refValidCheck(int index) const {
		if (!(0 <= index && index < (int)numItems))
			throw std::out_of_range("리스트 인덱스 참조 예외: 참조할 수 있는 인덱스의 범위를 벗어났습니다.");
	}

	size_t size() const noexcept {
		return numItems;
	}

	void clear() noexcept {
		// 모든 원소를 0으로 초기화하는 등의 행동을 하지 않고, 리스트의 크기를 0으로 수정함으로써 각 원소에 접근하지 않고도 리스트의 원소를 모두 제거한 효과를 낼 수 있음.
		numItems = 0;
	}

	int operator[](int index) const {
		refValidCheck(index);

		return items[index];
	}

	int& operator[](int index) {
		refValidCheck(index);

		return items[index];
	}

	void pushBack(int item) {
		pushValidCheck();

		items[numItems++] = item;
	}

	int popBack() {
		popValidCheck();

		return items[--numItems];
	}

	void pushFront(int item) {
		pushValidCheck();

		// 만약 items가 배열과 같은 포인터 상수가 아니었다면, 모든 원소를 움직이지 않고 해당 포인터가 가리키는 위치를 바꿈으로써 시간을 절약할 수 있음.
		for (size_t i = numItems; i >= 1; i--)
			items[i] = items[i - 1];
		items[0] = item;

		numItems++;
	}

	int popFront() {
		popValidCheck();

		int temp = items[0];

		// 만약 items가 배열과 같은 포인터 상수가 아니었다면, 모든 원소를 움직이지 않고 해당 포인터가 가리키는 위치를 바꿈으로써 시간을 절약할 수 있음.
		for (size_t i = 0; i < numItems; i++)
			items[i] = items[i + 1];

		numItems--;

		return temp;
	}

	int peekFront() const {
		popValidCheck();

		return items[0];
	}

	int peekBack() const {
		popValidCheck();

		return items[numItems - 1];
	}

	// insert 함수 추가 선언 및 구현.
	void insert(int index, int item) {
		pushValidCheck();

		// 배열의 끝에 원소 삽입 시 발생하는 잘못된 예외를 처리하기 위해 삼항 연산자를 이용해 조건을 설정함.
		refValidCheck(index == (int)numItems ? index - 1 : index);

		for (int i = numItems; i > index; i--)
			items[i] = items[i - 1];
		items[index] = item;

		numItems++;
	}

	bool find(int item) const noexcept {
		if (isEmpty())
			return false;

		// 본 자료구조가 사용하는 배열이 정렬되지 않은 배열이므로 이진 탐색이 불가능하다. 선형 탐색 이용.
		for (size_t i = 0; i < numItems; i++) {
			if (items[i] == item)
				return true;
		}

		return false;
	}

	// find()가 bool이 아닌 int로 원소의 첫 인덱스를 반환하면 중복되는 선형 탐색을 줄여 알고리즘을 개선할 수 있음.
	void removeFirst(int item) noexcept {
		for (size_t i = 0; i < numItems; i++) {
			if (items[i] == item)
				return remove(i);
		}
	}

	// 복잡한 알고리즘 없이 재귀적으로 해당 원소가 있으면 제거를 시도함.
	// 단, 동일한 원소가 많아질수록 재귀의 깊이가 깊어져 효율이 떨어질 수 있음.
	// find()가 원소의 첫 인덱스를 반환하게 하면 재귀 호출 없이 알고리즘을 구현할 수 있음.
	void removeAll(int item) noexcept {
		while (find(item))
			removeFirst(item);
	}

	auto begin() { return ListIterator<int>(items); }

	auto end() { return ListIterator<int>(items+numItems); }

	auto cbegin() const { return ListIterator<const int>(items); }

	auto cend() const { return ListIterator<const int>(items+numItems); }
};

#endif /* UNSORTEDARRAYLIST_H_ */
