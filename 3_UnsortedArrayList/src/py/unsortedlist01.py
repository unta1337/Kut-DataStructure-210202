# @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
# @version 2021년도 2학기
# @author 김상진
# @file unsortedlist01.py
# 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
# 순서를 유지하는 방법으로 pushFront, popFront, remove를 구현함

# 2020136018 김성녕

class UnsortedList:
	def __init__(self, initList: list = []):
		self.capacity = 10

		if len(initList) == 0:
			self.numItems = 0
			self.items = [0] * self.capacity
		elif len(initList) < self.capacity:
			self.numItems = len(initList)
			self.items = initList + [0] * (self.capacity - len(initList))
		else:
			self.numItems = 10
			self.items = initList[:10]

	# 내부적으로만 사용될 메소드이므로 private으로 선언.
	def __debugPrint(self) -> None:
		for e in self.items:
			print(e, end = ' ')
		print()

	def isEmpty(self) -> bool:
		return self.numItems == 0

	def isFull(self) -> bool:
		return self.numItems >= self.capacity

	def pushValidCheck(self) -> None:
		if self.isFull():
			raise RuntimeError('리스트 인덱스 범위 예외: 리스트에 있는 원소의 개수가 최대입니다.')

	def popValidCheck(self) -> None:
		if self.isEmpty():
			raise RuntimeError('리스트 인덱스 참조 예외: 리스트에 참조할 수 있는 원소가 없습니다.')

	def refValidCheck(self, index: int) -> None:
		if not 0 <= index < numItems:
			raise RuntimeError('리스트 인덱스 참조 예외: 참조할 수 있는 인덱스의 범위를 벗어났습니다.')

	def __len__(self) -> int:
		return self.numItems

	def clear(self) -> None:
		self.numItems = 0

	def pushback(self, item: int) -> None:
		self.pushValidCheck()

		self.items[self.numItems] = item
		self.numItems += 1

	def popback(self) -> int:
		self.popValidCheck()

		temp: int = self.items[self.numItems - 1]
		self.numItems -= 1
		return temp

	def pushfront(self, item: int) -> None:
		self.pushValidCheck()

		temp: list = self.items.copy()
		self.items[0] = item
		self.items[1:] = temp

		self.numItems += 1

	def popfront(self) -> int: 
		self.popValidCheck()

		temp: int = self.items[0]
		self.items = self.items[1:]

		self.numItems -= 1

		return temp

	def peekback(self) -> int:
		self.popValidCheck()

		return self.items[self.numItems - 1]

	def peekfront(self) -> int:
		self.popValidCheck()

		return self.items[0]

	def __contains__(self, item: int) -> bool:
		for e in self.items:
			if e == item:
				return True

		return False

	def _remove(self, index: int) -> None:
		temp: list = self.items[index + 1:].copy()
		self.items[index:] = temp

		self.numItems -= 1

	def removeFirst(self, item: int) -> None:
		for i in range(self.numItems):
			if self.items[i] == item:
				return self._remove(i)
	
	def removeAll(self, item: int) -> None:
		while item in self.items:
			self.removeFirst(item)

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





















