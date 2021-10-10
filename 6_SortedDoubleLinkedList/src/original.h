/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file original.h
 * 중복 허용, 이중 연결구조를 이용한 비정렬 정수 리스트
 * head, tail 유지, dummy 노드 사용, 코드 중복 제거
 */

#ifndef DOUBLEUNSORTEDLINKEDLIST_H_
#define DOUBLEUNSORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class DoubleUnsortedLinkedList {
private:
	struct Node{
		int item{0};
		Node* prev{nullptr};
		Node* next{nullptr};
		Node() = default;
		Node(int item, Node* prev = nullptr, Node* next = nullptr):
			item{item}, prev{prev}, next{next}{}
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

	Node* head{nullptr};
	Node* tail{nullptr};
	size_t numItems{0};

	void copyList(const DoubleUnsortedLinkedList& other){
		Node* dest{nullptr};
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(dest){
				dest->next = newNode;
				newNode->prev = dest;
				dest = newNode;
			}
			else head = dest = newNode;
			src = src->next;
			++numItems;
		}
		tail = dest;
	}

	void moveList(DoubleUnsortedLinkedList& tmp){
		numItems = tmp.numItems;
		head = tmp.head;
		tail = tmp.tail;
		tmp.head = tmp.tail = nullptr;
		tmp.numItems = 0;
	}

	int& getItem(int index) const{
		Node* curr{head};
		for(size_t i=0; i<index; ++i) curr = curr->next;
		return curr->item;
	}

	void removeNode(Node* curr){
		Node* prev{curr->prev};
		if(curr==tail) tail = (curr==head)? nullptr: prev;
		prev->next = curr->next; // dummy를 사용하므로 prev가 nullptr인 경우는 발생하지 않음
		if(curr->next) curr->next->prev = prev;
		delete curr;
		--numItems;
	}

public:
	explicit DoubleUnsortedLinkedList() = default;

	explicit DoubleUnsortedLinkedList(const std::initializer_list<int>& initList){
		Node* curr{nullptr};
		for(auto item: initList){
			Node* newNode{new Node{item}};
			if(curr){
				curr->next = newNode;
				newNode->prev = curr;
				curr = newNode;
			}
			else head = curr = newNode;
			++numItems;
		}
		tail = curr;
	}

	virtual ~DoubleUnsortedLinkedList(){
		clear();
	}

	DoubleUnsortedLinkedList(const DoubleUnsortedLinkedList& other){
		copyList(other);
	}

	DoubleUnsortedLinkedList(DoubleUnsortedLinkedList&& tmp){
		moveList(tmp);
	}

	const DoubleUnsortedLinkedList& operator=(const DoubleUnsortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}

	const DoubleUnsortedLinkedList& operator=(DoubleUnsortedLinkedList&& tmp){
		clear();
		moveList(tmp);
		return *this;
	}

	bool isEmpty() const noexcept {
		return !head;
	}

	bool isFull() const noexcept {
		return false;
	}

	size_t size() const noexcept{
		return numItems;
	}

	void clear() noexcept{
		Node* curr{head};
		while(curr){
			Node* deleteNode{curr};
			curr = curr->next;
			delete deleteNode;
		}
		head = tail = nullptr;
		numItems = 0;
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
		if(isEmpty()) head = tail = newNode;
		else{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		++numItems;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		int ret{tail->item};
		Node* prev{tail->prev};
		delete tail;
		if(prev){
			prev->next = nullptr;
			tail = prev;
		}
		else head = tail = nullptr; // 노드가 하나만 있는 경우
		--numItems;
		return ret;
	}

	void pushFront(int item){
		Node *newNode{new Node(item)};
		newNode->next = head;
		if(head) head->prev = newNode;
		else tail = newNode; // 리스트가 빈 경우
		head = newNode;
		++numItems;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{head->item};
		Node* deleteNode{head};
		head = head->next;
		if(head) head->prev = nullptr;
		else tail = nullptr; // 노드가 하나밖에 없는 경우
		delete [] deleteNode;
		--numItems;
		return ret;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return head->item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: empty state");
		return tail->item;
	}

	bool find(int item) const noexcept{
		if(isEmpty()) return false;
		Node *curr{head};
		while(curr){
			if(curr->item==item) return true;
			curr = curr->next;
		}
		return false;
	}

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		Node dummy{-1,nullptr,head};
		head->prev = &dummy;  // 단일 연결구조와 차이점
		Node* curr{head};
		while(curr){
			if(curr->item==item){
				removeNode(curr);
				break;
			}
			curr = curr->next;
		}
		head = dummy.next;
		if(head) head->prev = nullptr; // 단일 연결구조와 차이
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		Node dummy{-1,nullptr,head};
		head->prev = &dummy;  // 단일 연결구조와 차이점
		Node* curr{head};
		while(curr){
			if(curr->item==item){
				Node* next{curr->next};
				removeNode(curr);
				curr = next;
			}
			else curr = curr->next;
		}
		head = dummy.next;
		if(head) head->prev = nullptr; // 단일 연결구조와 차이
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* DOUBLEUNSORTEDLINKEDLIST_H_ */
