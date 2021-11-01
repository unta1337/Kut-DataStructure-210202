// 기관명: 한국기술교육대학교
// 학년도: 2021 학년도
// 교과목: 자바프로그래밍
// 주차: 5 주차
// 과제명: 단일 연결구조 기반 비정렬 리스트 (tail 포인터 유지)
// 저자: 2020136018 김성녕
// 원본: original.h | 저자: 김상진

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleUnsortedLinkedList {
private:
	struct Node {
		int item = 0;
		Node* next = nullptr;

		Node() = default;

		Node(int item, Node* next = nullptr) {
			this->item = item;
			this->next = nullptr;
		}
	};

	template <typename U>

	class ListIterator: public std::iterator<std::input_iterator_tag,U>{
		Node *p;

	public:
		explicit ListIterator(Node *p): p{p} {}

		const ListIterator& operator++() noexcept {
			p = p->next; return *this;
		}

		ListIterator operator++(int) noexcept {
			auto retval{*this};
			p = p->next; return retval;
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

	Node* head = new Node;
	Node* tail = new Node;
	size_t numItems = 0;

	Node* getTail() const {
		return tail;
	}

	void copyList(const SingleUnsortedLinkedList& other) {
		Node* current = other.head;

		while (current) {
			pushBack(current->item);
			current = current->next;
		}
	}

	void moveList(SingleUnsortedLinkedList& other) {
		head = other.head;
		tail = other.tail;
		numItems = other.numItems;

		other.head = other.tail = new Node;
		other.numItems = 0;
	}

	int& getItem(int index) const {
		if (isEmpty())
			throw std::runtime_error("getItem: empty list");
		if (!(0 <= index && index < numItems))
			throw std::out_of_range("getItem: out of index");

		Node* current = head;
		for (int i = 0; i <= index; i++)
			current = current->next;

		return current->item;
	}

	void removeNode(Node* prev, Node* current) {
		if (!current)
			throw std::runtime_error("removeNode: invalid current node pointer");

		if (head == tail) {
			head = tail = new Node;
		} else if (current == head) {
			head = current->next;
		} else if (current == tail) {
			prev->next = nullptr;
			tail = prev;
		} else {
			prev->next = current->next;
		}

		delete current;
		numItems--;
	}

public:
	explicit SingleUnsortedLinkedList() = default;

	explicit SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		for (auto item : initList) {
			pushBack(item);
		}
	}

	virtual ~SingleUnsortedLinkedList(){
		clear();
	}

	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other){
		copyList(other);
	}

	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& other){
		moveList(other);
	}

	const SingleUnsortedLinkedList& operator=(const SingleUnsortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}

	const SingleUnsortedLinkedList& operator=(SingleUnsortedLinkedList&& tmp){
		clear();
		moveList(tmp);
		return *this;
	}

	void printList() {
		Node* current = head;
		int index = 0;

		std::cout << "[UNSORTED SINGLE LINKES LIST DEBUGGING LOG]\n";
		std::cout << "numItems: " << numItems << std::endl;
		while (current) {
			std::cout << "index: " << index++ << " | " << "current / current->item / current->next: " << current << " / " << current->item << " / " << current->next << std::endl;
			current = current->next;
		}
		std::cout << "[=========================================]\n";
	}

	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	bool isFull() const noexcept {
		return false;
	}

	size_t size() const noexcept {
		return numItems;
	}

	void clear() noexcept {
		Node dummy{-1, head};
		while (!isEmpty())
			removeNode(&dummy, head);
	}

	int operator[](int index) const{
		return getItem(index);
	}

	int& operator[](int index) {
		return getItem(index);
	}

	void pushBack(int item) {
		Node* newNode = new Node{item};

		if (isEmpty()) {
			head = tail = newNode;
		} else {
			if (head == tail)
				head->next = tail;

			tail->next = newNode;
			tail = newNode;
		}

		numItems++;
	}

	int popBack(){
		if (isEmpty())
			throw std::runtime_error("popBack: empty list");

		int ret = tail->item;

		Node dummy{-1, head};
		Node* prev = &dummy;
		Node* current = head;
		while (current != tail) {
			prev = current;
			current = current->next;
		}
		removeNode(prev, current);

		return ret;
	}

	void pushFront(int item) {
		Node* newNode = new Node{item, head};

		if (isEmpty()) {
			head = tail = newNode;
			head->next = nullptr;
		} else {
			head = newNode;
		}

		numItems++;
	}

	int popFront() {
		if (isEmpty())
			throw std::runtime_error("popFront: empty list");

		int ret = head->item;

		Node dummy{-1, head};
		removeNode(&dummy, head);

		return ret;
	}

	int peekFront() {
		if (isEmpty())
			throw std::runtime_error("peekFront: empty list");

		return head->item;
	}

	int peekBack() {
		if (isEmpty())
			throw std::runtime_error("peekBack: empty list");

		return tail->item;
	}

	Node* find(int item) const noexcept{
		if (isEmpty())
			return nullptr;

		Node* current = head;
		while (current->item != item)
			current = current->next;

		return current;
	}

	void removeFirst(int item) noexcept{
		if (isEmpty())
			return;

		Node* prev = new Node{-1, head};
		Node* current = head;

		while (current && current->item != item) {
			prev = current;
			current = current->next;
		}

		if (current)
			removeNode(prev, current);
	}

	void removeAll(int item) noexcept{
		if (isEmpty())
			return;

		Node* prev = new Node{-1, head};
		Node* current = head;

		while (current != nullptr) {
			while (current && current->item != item) {
				prev = current;
				current = current->next;
			}

			if (current)
				removeNode(prev, current);
		}
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
