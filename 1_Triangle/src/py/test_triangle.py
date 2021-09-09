#============================================================================
# File        : test_triangle.py
# Author      : 김상진
# Version     : 2021년도 2학기
# Copyright   : 한국기술교육대학교 컴퓨터공학부 자료구조및실습
# Description : 삼각형 클래스 테스트 프로그램
#============================================================================
import unittest
from triangle import Triangle, Point

class TestTriangle(unittest.TestCase):

	def test_init(self):
		self.assertRaises(ValueError, Triangle, Point(15,15), Point(15,20), Point(15, 30))

	def test_area(self):
		a = Triangle(Point(15,15), Point(23,30), Point(50, 25))
		self.assertEqual(a.area(), 222.5)
		b = Triangle(Point(15,15), Point(23,30), Point(35, 10))
		self.assertEqual(b.area(), 170)

	def test_isInside(self):
		a = Triangle(Point(15,15), Point(23,30), Point(50, 25))
		b = Triangle(Point(15,15), Point(23,30), Point(35, 10))
		self.assertTrue(a.isInside(Point(25,20)))
		self.assertTrue(b.isInside(Point(25,20)))
		self.assertFalse(a.isInside(Point(10,25)))
		self.assertFalse(b.isInside(Point(10,25)))

unittest.main()
