# @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
# @version 2021년도 2학기
# @author 김상진
# @file unsortedlist01.py
# 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
# 순서를 유지하는 방법으로 pushFront, popFront, remove를 구현함

class UnsortedList:
	
	def __init__(self, initList: list=[]):
		self.capacity = 10
		if len(initList)==0:
			self.numItems = 0
			self.items = [0]*self.capacity
		elif len(initList)<self.capacity:
			self.numItems = len(initList)
			self.items = initList + [0]*(self.capacity-len(initList))
		else:
			self.numItems = 10
			self.items = initList[:10]

	def __len__(self):
		# 구현필요
		return 0

	def isFull(self) -> bool:
		# 구현필요
		return False

	def clear(self) -> None:
		# 구현필요

	def pushback(self, item: int) -> None:
		# 구현필요

	def popback(self) -> int:
		# 구현필요
		return 0

	def pushfront(self, item: int) -> None:
		# 구현필요 

	def popfront(self) -> int: 
		# 구현필요
		return 0

	def peekback(self) -> int:
		# 구현필요
		return 0

	def peekfront(self) -> int:
		# 구현필요
		return 0

	def __contains__(self, item: int) -> bool:
		# 구현필요
		return False

	def removeFirst(self, item: int) -> None:
		# 구현필요
	
	def removeAll(self, item: int) -> None:
		# 구현필요

	def __iter__(self):
		self.it = 0
		return self

	def __next__(self) -> int:
		if self.it<self.numItems:
			self.it += 1
			return self.items[self.it-1]
		else: raise StopIteration

	def computeRange(self, index: slice):
		start = index.start if index.start else 0
		flag = start<0
		start = self.numItems+start if flag else start
		flag = flag or index.start is None
		stop = index.stop if index.stop else self.numItems 
		stop = self.numItems+stop if flag and stop<0 else stop
		step = index.step if index.step else 1
		return start, stop, step

	def retrieveRange(self, index: slice):
		start, stop, step = self.computeRange(index)
		return range(start,stop,step)

	def __getitem__(self, index):
		if isinstance(index, int):
			if abs(index)<self.numItems:
				return self.items[index]
			else: raise IndexError('index out of range')
		elif isinstance(index, slice):
			return [self.items[i] for i in self.retrieveRange(index)]
		else: 
			raise TypeError('Index must be int, not {}'.format(type(index).__name__))
	
	def __setitem__(self, index, item):
		if isinstance(index, int):
			if abs(index)<self.numItems:
				self.items[index] = item
			else: raise IndexError('index out of range')
		elif isinstance(index, slice):
			start, stop, step = self.computeRange(index)
			if start+step*(len(item)-1)>stop:
				raise ValueError('slicing in this list require same size')
			j=0
			for i in range(start,stop,step):
				self.items[i] = item[j]
				j += 1
		else: 
			raise TypeError('Index must be int, not {}'.format(type(index).__name__))





















