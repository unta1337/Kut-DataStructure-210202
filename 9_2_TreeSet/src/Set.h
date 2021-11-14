/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * 집합: 균형 이진 탐색 트리를 이용하여 구현
 */

#ifndef SET_H_
#define SET_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <list>
#include <iterator>
#include <string>
#include <functional>
#include "AVL.h"

template <typename T>
class Set;

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B);
template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B);

template <typename T>
class Set {
private:
	AVL<T> tree{};
public:
	Set() = default;
	virtual ~Set() = default;
	Set(Set<T>&& tmp) = default;
	Set<T>& operator=(Set<T>&& tmp) = default;

	bool isEmpty() const noexcept{
		return tree.isEmpty();
	}
	bool isFull() const noexcept{
		return false;
	}
	size_t size() const noexcept{
		return tree.size();
	}

	void add(const T& key){
		// 완성
	}
	bool contains(const T& key) const{
		// 완성
		return false;
	}
	void remove(const T& key){
		// 완성
	}

	void debugPrint(){
		tree.debugPrint();
	}

	auto begin() const { return tree.begin(); }
	auto end() const { return tree.end(); }

	friend Set<T> operator+<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> operator-<>(const Set<T>& A, const Set<T>& B);
	friend Set<T> intersection<>(const Set<T>& A, const Set<T>& B);
};

template <typename T>
Set<T> operator+(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	// 완성
	return set;
}

template <typename T>
Set<T> operator-(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	// 완성
	return set;
}

template <typename T>
Set<T> intersection(const Set<T>& A, const Set<T>& B){
	Set<T> set;
	// 완성
	return set;
}


#endif /* SET_H_ */
