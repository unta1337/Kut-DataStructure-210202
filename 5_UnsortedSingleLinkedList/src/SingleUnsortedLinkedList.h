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

		Node(int item, Node* next = nullptr) : item{item}, next{next} { }
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

//	Node* head = new Node{-1, nullptr};
//	Node* tail = new Node{-1, nullptr};
	Node* head = new Node;
	Node* tail = new Node;
	size_t numItems = 0;

	// tail 포인터를 유지하므로 getTail 함수는 필요 없음.
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
		other.head = new Node;
	}

	int& getItem(int index) const {
		Node* current = head;

		for (int i = 0; i < index; i++)
			current = current->next;

		return current->item;
	}

	// 삭제 연산은 이 함수를 통해 수행.
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

	// push 메소드가 있으므로 해당 함수를 이용해 리스트를 초기화할 수 있다.
	explicit SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		for(auto item: initList){
			pushBack(item);
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
		printf("[SINGLE UNSORTED LINKED LIST DEBUGGIN LOG]\n");
		printf("numItems: %d\n", (int)numItems);
		printf("head: %p\n", head);
		printf("head->next: %p\n", head->next);
		printf("tail: %p\n", tail);
		printf("tail->next: %p\n", tail->next);
		printf("list: ");
		Node* current = head;
		while (current) {
			printf("%d, ", current->item);
			current = current->next;
		}
		printf("\n[========================================]\n");
	}

	// numItems를 이용해 원소의 개수 추적.
	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	// 확장 가능하므로 항상 false.
	bool isFull() const noexcept {
		return false;
	}

	// isEmpty()와 마찬가지로 numItems를 이용해 원소의 개수 추척.
	size_t size() const noexcept {
		return numItems;
	}

	// removeNode 메소드를 이용해 모든 원소를 제거.
	// 마지막으로 head와 tail도 제거.
	void clear() noexcept {
		Node dummy{-1, head};
		Node* current = head;

		while (current) {
			// removeNode 메소드에 의해 dummy의 next 요소가 current의 다음 요소로 바뀜.
			removeNode(&dummy, current);
			current = dummy.next;
		}

		head = tail = new Node;
	}

	int operator[](int index) const{
		if(index>=0&&index<(int)numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<(int)numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: []");
	}


	void pushBack(int item){
		Node* newNode = new Node{item};

		if (isEmpty()) {
			head = tail = newNode;
			tail->next = nullptr;
		}
		else
			tail = tail->next = newNode;

		numItems++;
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
			head = tail = new Node;
		}

		return ret;
	}

	void pushFront(int item) {
		Node* newNode = new Node{item, head};

		head = newNode;
		if (numItems == 0)
			head->next = tail;

		numItems++;
	}

	int popFront() {
		if(isEmpty()) throw std::runtime_error("popBack: empty state");

		int ret = head->item;

		Node dummy{-1, head};
		removeNode(&dummy, head);
		head = dummy.next;
		if (!tail)
			tail = head;

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
			return new Node;

		Node dummy{-1, head};
		Node* prev = &dummy;
		Node* current = head;

		while (current) {
			if (current->item == item)
				return prev;

			prev = current;
			current = current->next;
		}

		return new Node;
	}

	void removeFirst(int item) noexcept{
		if (isEmpty())
			return;

//		// 다른 메소드와는 다르게 이 메소드는 [
//		Node dummy{-1, head};
//		Node* prev = &dummy;
//		Node* current = prev->next;
//		Node* next = current-> next;
//
//		if (current->item == item) {
//			head = next == nullptr ? nullptr : next;
//			tail = next == nullptr ? nullptr : tail;
//			removeNode(prev, current);
//			return;
//		} else {
//			while (next && next->item != item) {
//				prev = current;
//				current = next;
//				next = next->next;
//			}
//		}
//		removeNode(current, next);
//		if (prev->item == -1)
//			tail = head;

		Node dummy{-1, head};
		Node* prev = &dummy;
		Node* current = prev->next;

		if (current->item == item) {
			removeNode(prev, current);
			head = prev->next;
			tail = head ? tail : head;
			return;
		} else {
			while (current->item != item) {
				prev = current;
				current = current->next;
			}
		}
		removeNode(prev, current);
	}

	void removeAll(int item) noexcept{
		if(isEmpty())
			return;

		while (find(item))
			removeFirst(item);
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
