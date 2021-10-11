/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file SortedDoubleLinkedListTest.cpp
 * 테스트 프로그램
 */

#include <string>
#include "gtest/gtest.h"

#include "SortedDoubleLinkedList.h"

TEST(SortedDoubleLinkedList_Duplicate_WithTail, listEmptyInitializationTest)
{
	SortedDoubleLinkedList list{};
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, PushAndPopBackTest)
{
	SortedDoubleLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.size(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"7,5,3,3,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, PushAndPopBackTest_EXTRA)
{
	SortedDoubleLinkedList list;
	ASSERT_THROW(list.popBack(), std::runtime_error);
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(1);
	list.pushBack(2);
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, PushAndPopFrontTest)
{
	SortedDoubleLinkedList list;
	ASSERT_THROW(list.popFront(), std::runtime_error);
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.pushFront(7);
	ASSERT_EQ(list.size(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,3,5,7,7,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, PushPopBackFrontTest)
{
	SortedDoubleLinkedList list;
	list.pushFront(3);
	ASSERT_EQ(list.peekFront(), 3);
	ASSERT_EQ(list.peekBack(), 3);
	list.pushFront(5);
	list.pushFront(7);
	ASSERT_EQ(list.peekFront(), 3);
	ASSERT_EQ(list.peekBack(), 7);
	list.pushBack(1);
	list.pushBack(2); // 1 2 3 5 7
	ASSERT_EQ(list.peekFront(), 1);
	ASSERT_EQ(list.peekBack(), 7);
	ASSERT_EQ(list.size(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"1,2,3,5,7,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, listInitializationTest)
{
	SortedDoubleLinkedList list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	SortedDoubleLinkedList list2{1,2,3,4,5,6,7,8,9,10,11,12};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,11,12,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, findTest){
	SortedDoubleLinkedList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, removeFirstTest){
	SortedDoubleLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.removeFirst(3);
	ASSERT_EQ(list.size(),2);
	list.removeFirst(7);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(5,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.pushFront(3);
	list.pushBack(5);
	ASSERT_EQ(list.size(),2);
	list.removeFirst(5);
	list.removeFirst(3);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, removeAllTest){
	SortedDoubleLinkedList list{1,3,1,1,3,4,5,4,4,6};
	list.removeAll(3);
	ASSERT_EQ(list.size(),8);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,1,1,4,4,4,5,6,");
	list.removeAll(1);
	ASSERT_EQ(list.size(),5);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,4,4,5,6,");
	list.removeFirst(5);
	ASSERT_EQ(list.size(),4);
	list.removeAll(4);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(6,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(3);
	list.pushFront(3);
	list.pushFront(3);
	list.removeAll(3);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, iteratorTest){
	SortedDoubleLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	std::string output = "";
	for(auto b = list.cbegin(); b!=list.cend(); ++b){
		//*b = 4;
		output += std::to_string(*b)+",";
	}
	ASSERT_EQ(output,"3,5,7,");

	output = "";
	auto it{list.begin()};
	*it = 0;
	for(auto n: list)
		output += std::to_string(n)+",";
	ASSERT_EQ(output,"0,5,7,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, IndexOperator){
	SortedDoubleLinkedList list;
	list.pushBack(3);
	list.pushBack(5);
	ASSERT_EQ(list[1], 5);
	ASSERT_THROW(list[2], std::out_of_range);
	ASSERT_THROW(list[2]=0, std::out_of_range);

	list.pushBack(7);
	list[0] = 4;	// list.set(0, 4);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,7,");
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, clearTest){
	SortedDoubleLinkedList list{1,3,1,1,3,4,5,4,4,6};
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(4);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(4,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	ASSERT_EQ(list.size(),0);
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, Big5)
{
	SortedDoubleLinkedList list1{1,2,3,4,5};
	SortedDoubleLinkedList list2{6,7,8,9,10};
	SortedDoubleLinkedList list3;
	SortedDoubleLinkedList list4(list2);
	// copy constructor test
	for(size_t i=0; i<list2.size(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(size_t i=0; i<list1.size(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SortedDoubleLinkedList list5(std::move(list3));
	for(size_t i=0; i<list5.size(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(size_t i=0; i<list3.size(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

TEST(SortedDoubleLinkedList_Duplicate_WithTail, removeRange)
{
	SortedDoubleLinkedList list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ASSERT_THROW(list.removeRange(-1, 10), std::out_of_range);
	ASSERT_THROW(list.removeRange(0, 11), std::out_of_range);
	ASSERT_THROW(list.removeRange(-1, 11), std::out_of_range);
	list.removeRange(3, 5);
	ASSERT_EQ(list.size(), 8);
	list.removeRange(0, 2);
	ASSERT_EQ(list.size(), 6);
	list.removeRange(list.size() - 4, list.size());
	ASSERT_EQ(list.size(), 2);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,6,");
}
