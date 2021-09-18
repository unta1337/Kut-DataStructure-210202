# @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
# @version 2021년도 2학기
# @author 김상진
# @file unsortedlist01.py
# 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
# 테스트 프로그램

import unittest
from unsortedlist01 import UnsortedList

class TestUnsortedList(unittest.TestCase):

	#@unittest.skip
	def test_listinit(self):
		L = UnsortedList()
		self.assertTrue(not L)
		self.assertFalse(L.isFull())

	#@unittest.skip
	def test_pushpop_back(self):
		L = UnsortedList()
		L.pushback(3)
		L.pushback(5)
		L.pushback(7)
		L.pushback(3)
		self.assertEqual(len(L),4)
		output = []
		while L:
			output.append(L.popback())
		self.assertEqual(output,[3,7,5,3])

		L = UnsortedList()
		self.assertRaises(RuntimeError, L.popback)
		L.pushback(1)
		L.pushback(2)
		L.pushback(3)
		L.pushback(4)
		L.pushback(5)
		L.pushback(6)
		L.pushback(7)
		L.pushback(8)
		L.pushback(9)
		L.pushback(10)
		self.assertRaises(RuntimeError, L.pushback, 11)

	#@unittest.skip
	def test_pushpop_front(self):
		L = UnsortedList()
		self.assertRaises(RuntimeError, L.popfront)
		L.pushfront(3)
		L.pushfront(5)
		L.pushfront(7)
		L.pushfront(3)
		L.pushfront(7)
		self.assertEqual(len(L),5)
		output = []
		while L:
			output.append(L.popfront())
		self.assertEqual(output,[7,3,7,5,3])
	
	#@unittest.skip
	def test_peek(self):
		L = UnsortedList()
		L.pushfront(3)
		self.assertEqual(L.peekfront(), 3)
		self.assertEqual(L.peekback(), 3)
		L.pushfront(5)
		L.pushfront(7)
		self.assertEqual(L.peekfront(), 7)
		self.assertEqual(L.peekback(), 3)
		L.pushback(1)
		L.pushback(2)
		self.assertEqual(L.peekfront(), 7)
		self.assertEqual(L.peekback(), 2)
		self.assertEqual(len(L),5)
		output = []
		while L:
			output.append(L.popfront())
		self.assertEqual(output,[7,5,3,1,2])

	#@unittest.skip
	def test_initList(self):
		L = UnsortedList([1,2,3,4,5,6])
		self.assertEqual(len(L),6)
		self.assertEqual(L.peekfront(),1)
		self.assertEqual(L.peekback(),6)

		L = UnsortedList([1,2,3,4,5,6,7,8,9,10])
		self.assertEqual(len(L),10)
		self.assertTrue(L.isFull())
		self.assertEqual(L.peekfront(),1)
		self.assertEqual(L.peekback(),10)

		L = UnsortedList([1,2,3,4,5,6,7,8,9,10,11,12,13])
		self.assertEqual(len(L),10)
		self.assertTrue(L.isFull())
		self.assertEqual(L.peekfront(),1)
		self.assertEqual(L.peekback(),10)

	#@unittest.skip
	def test_find(self):
		L = UnsortedList([3,3,5,7,9])
		self.assertTrue(3 in L)
		self.assertTrue(5 in L)
		self.assertTrue(7 in L)
		self.assertTrue(9 in L)
		self.assertFalse(1 in L)
		self.assertFalse(4 in L)
		self.assertFalse(6 in L)
		self.assertFalse(8 in L)
		self.assertFalse(11 in L)

	#@unittest.skip
	def test_removeFirst(self):
		L = UnsortedList([3,5,7])
		L.removeFirst(3)
		self.assertEqual(len(L),2)
		self.assertEqual(L.peekfront(), 5)
		L.removeFirst(7)
		self.assertEqual(len(L),1)
		self.assertEqual(L.peekback(), 5)
		L.removeFirst(5)
		self.assertTrue(not L)
		L = UnsortedList([3,5,7])
		L.removeFirst(5)
		self.assertEqual(len(L),2)
		self.assertEqual(L.peekfront(), 3)
		self.assertEqual(L.peekback(), 7)
	
	#@unittest.skip	
	def test_removeAll(self):
		L = UnsortedList([1,3,1,1,3,4,5,4,4,6])
		L.removeAll(3)
		self.assertFalse(3 in L)
		self.assertEqual(len(L),8)
		self.assertEqual(L.peekfront(), 1)
		self.assertEqual(L.peekback(), 6)
		L.removeAll(1)
		self.assertFalse(1 in L)
		self.assertEqual(len(L),5)
		self.assertEqual(L.peekfront(), 4)
		self.assertEqual(L.peekback(), 6)
		L.removeAll(5)
		self.assertEqual(len(L),4)
		self.assertFalse(5 in L)
		L.removeAll(4)
		self.assertEqual(len(L),1)
		self.assertFalse(4 in L)
		L.popback()
		L.pushback(3)
		L.pushfront(3)
		L.pushfront(3)
		self.assertEqual(len(L),3)
		L.removeAll(3)
		self.assertTrue(not L)

	#@unittest.skip	
	def test_clear(self):
		L = UnsortedList([1,3,4,1,2,6,8])
		self.assertEqual(len(L),7)
		L.clear()
		self.assertTrue(not L)
		L.pushback(4)
		self.assertEqual(len(L),1)
		self.assertEqual(L.peekback(),4)


	#@unittest.skip
	def test_iterator(self):
		L = UnsortedList([1,3,1,1,3,4,5,4,4,6])
		output = [x for x in L]
		self.assertEqual(output, [1,3,1,1,3,4,5,4,4,6])

	#@unittest.skip
	def test_getitem(self):
		L = UnsortedList(initList=[1,2,3,4,5,6,7,8,9,10])
		self.assertEqual(L[2],3)
		self.assertEqual(L[-1],10)
		self.assertEqual(L[:3],[1,2,3])
		self.assertEqual(L[-2:],[9,10])
		self.assertEqual(L[4:-1:-1],[5,4,3,2,1])
		self.assertEqual(L[-6:-3],[5,6,7])
		self.assertEqual(L[:-5],[1,2,3,4,5])
	
	#@unittest.skip
	def test_setitem(self):	
		L = UnsortedList(initList=[1,2,3,4,5,6,7,8,9,10])
		L[5] = 0
		output = [x for x in L]
		self.assertEqual(output, [1,2,3,4,5,0,7,8,9,10])
		L[5] = 6
		L[:5] = [0,0,0,0,0]
		output = [x for x in L]
		self.assertEqual(output, [0,0,0,0,0,6,7,8,9,10])
		L[-5:] = [0,0,0,0,0]
		output = [x for x in L]
		self.assertEqual(output, [0,0,0,0,0,0,0,0,0,0])
		L[0::2] = [1,2,3,4,5]
		output = [x for x in L]
		self.assertEqual(output, [1,0,2,0,3,0,4,0,5,0])
		self.assertRaises(TypeError, 'L[:2] = [1.2, 3.3]')


unittest.main()