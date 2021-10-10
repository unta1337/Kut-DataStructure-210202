// 기관명: 한국기술교육대학교
// 학년도: 2021 학년도
// 교과목: 자바프로그래밍
// 주차: 6 주차
// 과제명: 이중 연결구조 기반 정렬 리스트 (head, tail 유지; dummy 노드 사용; 코드 중복 제거)
// 저자: 2020136018 김성녕
// 원본: original.h | 저자: 김상진

#ifndef DOUBLEUNSORTEDLINKEDLIST_H_
#define DOUBLEUNSORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <iostream>

class DoubleUnsortedLinkedList {
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
	void copyList(const DoubleUnsortedLinkedList& other) {
		for (Node* otherCurrent = other.head; otherCurrent; otherCurrent = otherCurrent->next)
			pushBack(otherCurrent->item);
	}

	void moveList(DoubleUnsortedLinkedList& other) {
		numItems = other.numItems;
		head = other.head;
		tail = other.tail;

		other.head = other.tail = nullptr;
		other.numItems = 0;
	}

	int& getItem(int index) const {
		Node* current = head;

		for (int i = 0; i < index; i++)
			current = current->next;

		return current->item;
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

	void printList() {
		std::cout << "[DoubleUnsortedLinkedList 디버깅 출력]" << std::endl;
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
	explicit DoubleUnsortedLinkedList() = default;

	explicit DoubleUnsortedLinkedList(const std::initializer_list<int>& initList){
		// pushBack 메소드를 이용하여 코드의 중복을 줄일 수 있음.
		for (auto item : initList)
			pushBack(item);
	}

	virtual ~DoubleUnsortedLinkedList() {
		clear();
	}

	DoubleUnsortedLinkedList(const DoubleUnsortedLinkedList& other) {
		copyList(other);
	}

	DoubleUnsortedLinkedList(DoubleUnsortedLinkedList&& other) {
		moveList(other);
	}

	const DoubleUnsortedLinkedList& operator=(const DoubleUnsortedLinkedList& other) {
		clear();
		copyList(other);
		return *this;
	}

	const DoubleUnsortedLinkedList& operator=(DoubleUnsortedLinkedList&& other) {
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

	// remove 연산과는 다르게 push 연산은 앞에 push하느냐 뒤에 push하느냐가 다른 경우임.
	// 즉, pushBack과 pushFront 연산이 각각 최소 연산 단위임.
	// 두 연산 모두 따로 구현이 필요함.
	void pushBack(int item) {
		Node* newNode = new Node{item};

		if (isEmpty())
			head = tail = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}

		numItems++;
	}

	// popBack과 popFront 연산은 최소 연산 단위인 removeNode를 이용해 구현할 수 있다.
	int popBack() {
		if(isEmpty())
			throw std::runtime_error("popBack: empty state");

		int ret = tail->item;

		removeNode(tail);

		return ret;
	}

	// remove 연산과는 다르게 push 연산은 앞에 push하느냐 뒤에 push하느냐가 다른 경우임.
	// 즉, pushBack과 pushFront 연산이 각각 최소 연산 단위임.
	// 두 연산 모두 따로 구현이 필요함.
	void pushFront(int item) {
		Node* newNode = new Node{item};

		if (isEmpty())
			head = tail = newNode;
		else {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}

		numItems++;
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
	Node* findWithStartingNode(Node* start, int item) const noexcept {
		if(isEmpty() || start == nullptr)
			return nullptr;

		Node* current = start;
		while (current && current->item != item)
			current = current->next;

		// 값이 존재하지 않으면 current는 nullptr일 것이므로, 굳이 current->item == item을 확인하지 않아도 됨.
		return current;
	}

	// 기존의 bool 반환이 아닌, 해당 노드를 반환함으로써 코드 중복을 줄이고 효율을 높일 수 있음.
	Node* find(int item) const noexcept {
		return findWithStartingNode(head, item);
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

	bool removeAll(int item) noexcept {
		Node* current = find(item);

		if (!current)
			return false;

		for ( ; current; current = findWithStartingNode(current->next, item)) {
			Node* deleteNode = current;
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

#endif /* DOUBLEUNSORTEDLINKEDLIST_H_ */
