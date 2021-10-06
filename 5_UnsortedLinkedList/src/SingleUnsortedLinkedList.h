/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file SingleUnsortedLinkedList.h
 * 중복 허용, 단일 연결구조를 이용한 비정렬 정수 리스트
 * 두 개의 포인터를 이용하여 popBack, remove 연산 구현
 * head만 유지, dummy 노드 사용, 코드 중복 제거
 */

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

#include <iostream>

class SingleUnsortedLinkedList {
private:
	struct Node {
		int item = 0;
		Node* next = nullptr;

		Node() = default;

		Node(int item, Node* next = nullptr) : item{item}, next{next} { }
	};

	template <typename U>

	class ListIterator: public std::iterator<std::input_iterator_tag,U>{
		Node *p;

	public:
		explicit ListIterator(Node *p): p{p} {}

		const ListIterator& operator++() noexcept {p = p->next; return *this;}

		ListIterator operator++(int) noexcept {auto retval{*this}; p = p->next; return retval;}

		bool operator==(const ListIterator& other) const noexcept {return p == other.p;}

		bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}

		U& operator*() noexcept {return p->item;}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t numItems = 0;

	// tail을 유지하므로 getTail 함수는 필요 없음.
	Node* getTail() const {
		return tail;
	}


	void copyList(const SingleUnsortedLinkedList& other) {
		Node* dest = nullptr;
		Node* src = other.head;

		while (src) {
			Node* newNode = new Node{src->item};

			if (dest) {
				dest->next = newNode;
				dest = newNode;
			} else {
				head = dest = newNode;
			}

			src = src->next;
			numItems++;
		}
	}

	void moveList(SingleUnsortedLinkedList& other) {
		numItems = other.numItems;
		head = other.head;

		other.numItems = 0;
		other.head = nullptr;
	}

	int& getItem(int index) const {
		Node* current = head;

		for (int i = 0; i < index; i++)
			current = current->next;

		return current->item;
	}

	// 모든 삭제 연산은 이 함수를 통해 수행.
	// pop, remove 등 모든 연산이 포함됨.
	void removeNode(Node* prev, Node* current) {
		if (!current)
			return;

		prev->next = current->next;
		delete current;

		numItems--;
	}

public:
	explicit SingleUnsortedLinkedList() = default;

	explicit SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		Node* current = nullptr;

		for(auto item: initList){
			Node* newNode = new Node{item};

			if(current){
				current->next = newNode;
				tail = current = newNode;
			} else {
				head = tail = current = newNode;
			}

			numItems++;
		}
	}

	virtual ~SingleUnsortedLinkedList(){
		clear();
	}

	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other){
		copyList(other);
	}

	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& tmp){
		moveList(tmp);
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

	void print() {
		printf("DEBUGGING PRINT\n");
		printf("numItems: %d\n", numItems);
		printf("head: %p\n", head);
		printf("tail: %p\n", tail);
		printf("list: ");
		Node* current = head;
		while (current) {
			printf("%d, ", current->item);
			current = current->next;
		}
		printf("\n\n");
	}

	bool isEmpty() const noexcept {
		//return !head && !tail;
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
		Node* current = head;

		while (current) {
			removeNode(&dummy, current);
			current = dummy.next;
		}

		head = tail = dummy.next;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: []");
	}


	void pushBack(int item){
		Node *newNode{new Node(item)};
		if(isEmpty()) head = newNode;
		else tail->next = newNode;
		tail = newNode;
		++numItems;
	}


	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");

		int ret = tail->item;

		Node dummy{-1, head};
		Node* prev = head;
		Node* current = head->next;

		while (current && current != tail) {
			prev = current;
			current = current->next;
		}

		if (prev != tail) {
			removeNode(prev, tail);
			tail = prev;
		} else {
			removeNode(&dummy, tail);
			head = tail = nullptr;
		}

		return ret;
	}

	void pushFront(int item) {
		Node* newNode = new Node{item};
		newNode->next = head;

		head = newNode;
		if (tail == nullptr)
			tail = head;

		numItems++;
	}

	int popFront() {
		if(isEmpty()) throw std::runtime_error("popBack: empty state");

		int ret = head->item;

		tail = head == tail ? nullptr : tail;
		Node* next = tail == nullptr ? nullptr : head->next;

		Node dummy{-1, head};
		removeNode(&dummy, head);
		head = next;

		return ret;
	}

	int peekFront() {
		if(isEmpty()) throw std::runtime_error("popBack: empty state");

		return head->item;
	}

	int peekBack() {
		if(isEmpty()) throw std::runtime_error("popBack: empty state");

		return tail->item;
	}

	Node* find(int item) const noexcept{
		if(isEmpty())
			return nullptr;

		Node dummy{-1, head};
		Node* prev = &dummy;
		Node* current = head;

		while (current) {
			if (current->item == item)
				return prev;

			prev = current;
			current = current->next;
		}

		return nullptr;
	}

	void removeFirst(int item) noexcept{
		if (isEmpty())
			return;

		Node dummy{-1, head};
		Node* prev = &dummy;
		Node* current = prev->next;

		while (current && current->item == item) {
			prev = current;
			current = current->next;
		}

		if (current) {
			removeNode(prev, current);
		}
	}

	void removeAll(int item) noexcept{
		if(isEmpty())
			return;

		while (!find(item))
			removeFirst(item);
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
