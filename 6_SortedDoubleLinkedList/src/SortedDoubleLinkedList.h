// 기관명: 한국기술교육대학교
// 학년도: 2021 학년도
// 교과목: 자바프로그래밍
// 주차: 6 주차
// 과제명: 이중 연결구조 기반 정렬 리스트 (head, tail 유지; dummy 노드 사용; 코드 중복 제거)
// 저자: 2020136018 김성녕
// 원본: original.h | 저자: 김상진

#ifndef SORTEDDOUBLELINKEDLIST_H_
#define SORTEDDOUBLELINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <iostream>

class SortedDoubleLinkedList {
private:
	struct Node {
		int item = 0;
		Node* prev = nullptr;
		Node* next = nullptr;

		Node() = default;

		Node(int item, Node* prev = nullptr, Node* next = nullptr) : item{item}, prev{prev}, next{next} { }
	};

	template <typename U>

	class ListIterator: public std::iterator<std::input_iterator_tag,U> {
        Node *p;

    public:
        explicit ListIterator(Node* p) : p{p} { }

        const ListIterator& operator++() noexcept {
        	p = p->next;
        	return *this;
        }

        ListIterator operator++(int) noexcept {
        	auto retval = *this;
        	p = p->next;
        	return retval;
        }

        bool operator==(const ListIterator& other) const noexcept {
        	return p == other.p;
        }

        bool operator!=(const ListIterator& other) const noexcept {
        	return p != other.p;
        }

        U& operator*() noexcept {
        	return p->item;
        }
    };

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t numItems = 0;

	// pushBack 메소드를 이용하여 코드의 중복을 줄일 수 있음.
	void copyList(const SortedDoubleLinkedList& other) {
		for (Node* otherCurrent = other.head; otherCurrent; otherCurrent = otherCurrent->next)
			pushBack(otherCurrent->item);
	}

	void moveList(SortedDoubleLinkedList& other) {
		numItems = other.numItems;
		head = other.head;
		tail = other.tail;

		other.head = other.tail = nullptr;
		other.numItems = 0;
	}

	// getItem이 아닌 getNode 메소드를 구현함으로써 getItem 및 removeRange에서 사용할 수 있음.
	Node* getNode(int index) const {
		Node* current = head;

		for (int i = 0; i < index; i++)
			current = current->next;

		return current;
	}

	// getNode를 통해 구현.
	int& getItem(int index) const {
		return getNode(index)->item;
	}

	// 모든 삭제 연산은 removeNode 메소드를 통해 이뤄짐.
	// 본 메소드에서 유효성 검사 및 numItems 변수를 관리하므로, 원소 삭제 시 해당 관련 내용을 신경쓰지 않아도 됨.
	void removeNode(Node* current) {
		if (current->prev == nullptr) {
			// current가 리스트의 첫 요소일 때.
			head = current->next ? current->next : nullptr;			// 원소의 개수가 1일 때를 처리하기 위한 삼항 연산자.
			if (head)
				head->prev = nullptr;
			tail = head ? tail : nullptr;
		} else if (current->next == nullptr) {
			// current가 리스트의 마지막 요소일 때.
			tail = current->prev;
			tail->next = nullptr;
		} else {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}

		delete current;
		numItems--;
	}

	// 모든 push 연산은 insertItem 메소드를 통해 수행됨.
	// prev와 next에 대해서 모두 예외를 고려하므로 !prev && !next인 상황인 리스트가 빈 경우는 따로 고려하지 않아도 됨.
	// 본 메소드에서 유효성 검사 및 numItems 변수를 관리하므로, 원소 삭제 시 해당 관련 내용을 신경쓰지 않아도 됨.
	void insertItem(Node* prev, Node* next, int item) {
		Node* newNode = new Node{item, prev, next};

		// prev가 nullptr이면, 즉 삽입 위치가 첫 번째면 head를 newNode로 바꾼다.
		if (prev)
			prev->next = newNode;
		else
			head = newNode;

		// next가 nullptr이면, 즉 삽입 위치가 마지막 번째면 tail을 newNode로 바꾼다.
		if (next)
			next->prev = newNode;
		else
			tail = newNode;

		numItems++;
	}

	void printList() {
		std::cout << "[SortedDoubleLinkedList 디버깅 출력]" << std::endl;
		std::cout << "numItems: " << numItems << std::endl;

		int index = 0;
		for (Node* current = head; current; current = current->next) {
			std::cout << "index: " << index++ << " | ";
			std::cout << "current->prev: " << current->prev << " | ";
			std::cout << "current: " << current << " | ";
			std::cout << "current->item: " << current->item << " | ";
			std::cout << "current->next: " << current->next << std::endl;
		}

		std::cout << "[=================================]" << std::endl;
	}

public:
	explicit SortedDoubleLinkedList() = default;

	explicit SortedDoubleLinkedList(const std::initializer_list<int>& initList){
		// pushBack 메소드를 이용하여 코드의 중복을 줄일 수 있음.
		for (auto item : initList)
			pushBack(item);
	}

	virtual ~SortedDoubleLinkedList() {
		clear();
	}

	SortedDoubleLinkedList(const SortedDoubleLinkedList& other) {
		copyList(other);
	}

	SortedDoubleLinkedList(SortedDoubleLinkedList&& other) {
		moveList(other);
	}

	const SortedDoubleLinkedList& operator=(const SortedDoubleLinkedList& other) {
		clear();
		copyList(other);
		return *this;
	}

	const SortedDoubleLinkedList& operator=(SortedDoubleLinkedList&& other) {
		clear();
		moveList(other);
		return *this;
	}

	// numItems를 이용해 isEmpty 여부를 확인함.
	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	bool isFull() const noexcept {
		return false;
	}

	size_t size() const noexcept {
		return numItems;
	}

	// removeNode를 이용해 모든 노드 제거.
	void clear() noexcept {
		for (Node* current = head; current; current = current->next)
			removeNode(current);
	}

	int operator[](int index) const {
		if(0 <= index && index < (int)numItems)
			return getItem(index);
		else
			throw std::out_of_range("Index ERROR: [] const");
	}

	int& operator[](int index){
		if(0 <= index && index < (int)numItems)
			return getItem(index);
		else
			throw std::out_of_range("Index ERROR: []");
	}

	// pushBack과 pushFront 연산은 최소 연산 단위인 insertItem을 이용해 구현할 수 있다.
	void pushBack(int item) {
		Node* next = nullptr;
		Node* current = tail;

		while (current && current->item > item) {
			next = current;
			current = current->prev;
		}

		insertItem(current, next, item);
	}

	// popBack과 popFront 연산은 최소 연산 단위인 removeNode를 이용해 구현할 수 있다.
	int popBack() {
		if(isEmpty())
			throw std::runtime_error("popBack: empty state");

		int ret = tail->item;

		removeNode(tail);

		return ret;
	}

	// pushBack과 pushFront 연산은 최소 연산 단위인 insertItem을 이용해 구현할 수 있다.
	void pushFront(int item) {
		Node* prev = nullptr;
		Node* current = head;

		while (current && current->item < item) {
			prev = current;
			current = current->next;
		}

		insertItem(prev, current, item);
	}

	// popBack과 popFront 연산은 최소 연산 단위인 removeNode를 이용해 구현할 수 있다.
	int popFront() {
		if(isEmpty())
			throw std::runtime_error("popFront: empty state");

		int ret = head->item;

		removeNode(head);

		return ret;
	}

	int peekFront() const {
		if(isEmpty())
			throw std::runtime_error("peekFront: empty state");
		return head->item;
	}

	int peekBack() const {
		if(isEmpty())
			throw std::runtime_error("peekBack: empty state");
		return tail->item;
	}

	// removeAll 메소드에서 코드의 중복을 줄이고 효율을 높이기 위한 메소드.
	// 비정렬 리스트일 때 구현한 메소드로, 정렬 리스트일 때는 굳이 필요하지 않음.
	// 단, 본 메소드에 의존성을 갖는 find 메소드는 정렬 여부에 관계 없이 특정 노드에서부터 수행할 수 있으므로 사용은 가능함.
	Node* findWithStartingNode(Node* start, int item) const noexcept {
		if(isEmpty())
			return nullptr;

		Node* current = start;
		while (current && current->item != item)
			current = current->next;

		// 값이 존재하지 않으면 current는 nullptr일 것이므로, 굳이 current->item == item을 확인하지 않아도 됨.
		return current;
	}

	// 기존의 bool 반환이 아닌, 해당 노드를 반환함으로써 코드 중복을 줄이고 효율을 높일 수 있음.
	// 비정렬 리스트일 때 구현한 메소드로, findWithStartingNode 메소드를 통해 구현되었지만, 이 둘을 통합해도 됨.
	Node* find(int item) const noexcept {
		return findWithStartingNode(new Node{-1, nullptr, head}, item);			// 더미 도느 활용.
	}

	// removeNode를 제외한 remove 계열 함수는 원소의 삭제 여부를 bool 타입으로 반환함.
	bool removeFirst(int item) noexcept {
		if(isEmpty())
			return false;

		Node* deleteNode = find(item);
		if (deleteNode)
			removeNode(deleteNode);

		return true;
	}

	// 정렬 리스트이므로 한번 item을 찾으면 item의 값이 동일한 노드를 연속적으로 제거할 수 있음.
	bool removeAll(int item) noexcept {
		Node* current = find(item);

		if (!current)
			return false;

		while (current && current->item == item) {
			Node* deleteNode = current;
			current = current->next;
			removeNode(deleteNode);
		}

		return true;
	}

	// getNode를 통해 구현.
	bool removeRange(int first, int last) {
		if (!(0 <= first && first <= last && last <= (int)numItems))
			throw std::out_of_range("removeRange: out of range");

		Node* current = getNode(first);
		for (int i = first; i < last; i++) {
			Node* deleteNode = current;
			current = current->next;
			removeNode(deleteNode);
		}

		return true;
	}

	auto begin() {
		return ListIterator<int>(head);
	}

	auto end() {
		return ListIterator<int>(nullptr);
	}

	auto cbegin() const {
		return ListIterator<const int>(head);
	}

	auto cend() const {
		return ListIterator<const int>(nullptr);
	}
};

#endif /* SORTEDDOUBLELINKEDLIST_H_ */
