#============================================================================
# File        : triangle.py
# Author      : 김상진
# Version     : 2021년도 2학기
# Copyright   : 한국기술교육대학교 컴퓨터공학부 자료구조및실습
# Description : 삼각형 클래스
#============================================================================

class Point:
    def __init__(self, x: int = 0, y: int = 0):
        self.x: int = x
        self.y: int = y

    # 점의 일치 여부를 판단하기 위한 함수.
    def equals(self, other) -> bool:
        xCondition: bool = self.x == other.x
        yCondition: bool = self.y == other.y

        return xCondition and yCondition

    # 2차원 벡터끼리의 외적의 크기를 반환.
    # 점의 위치 관계를 구하기 위함.
    # ref: http://www.findmean.com/%EC%88%98%ED%95%99/%EB%B2%A1%ED%84%B0/%EB%B2%A1%ED%84%B0%EC%9D%98-%EC%99%B8%EC%A0%81/
    def crossProductScalar2D(self, other) -> int:
        return self.x * other.y - other.x * self.y

class Triangle:
    # 주어진 3점이 삼각형을 형성하지 않으면 ValueError 예외를 발생해야 함
    def __init__(self, p1: Point, p2: Point, p3: Point):
        # 연산의 편의를 위한 배열화.
        self.p: list = [p1, p2, p3]

        # 삼각형 결정조건: 서로 다른 세 개의 점.
        pointsEq: int = 0
        for i in range(3):
            pointsEq += self.p[i].equals(self.p[(i + 1) % 3])
        if pointsEq >= 2:
            raise ValueError('삼각형 결정조건 불만족: 두 개 이상의 점이 서로 일치합니다.')

        # 삼각형 결정조건: 한 직선 위에 있지 않은 서로 다른 세 개의 점.
        p31: Point = Point(self.p[2].x - self.p[0].x, self.p[2].y - self.p[0].y)
        p32: Point = Point(self.p[2].x - self.p[1].x, self.p[2].y - self.p[1].y)
        if p31.crossProductScalar2D(p32) == 0:
            raise ValueError('삼각형 결정조건 불만족: 세 개의 점이 한 직선 위에 있습니다.')

    # 삼각형의 면적
    def area(self) -> float:
        temp: int = 0

        # 신발끈 공식 이용.
        # ref: https://ko.wikipedia.org/wiki/%EC%8B%A0%EB%B0%9C%EB%81%88_%EA%B3%B5%EC%8B%9D
        for i in range(3):
            temp += self.p[i].x * self.p[(i + 1) % 3].y
            temp -= self.p[i].y * self.p[(i + 1) % 3].x
        temp = temp if temp > 0 else -temp

        return 0.5 * temp

    # 주어진 점이 삼각형 내부에 있는지 검사
    def isInside(self, point: Point) -> bool:
        # 외적을 이용한 점의 위치 관계 이용.
        # ref: https://bbungprogram.tistory.com/13

        # 임의의 점 세 개의 배열을 판단하는 변수 ref.
        # if ref > 0: 반시계 방향 배열, elif ref < 0: 시계 방향 배열
        p12: Point = Point(self.p[1].x - self.p[0].x, self.p[1].y - self.p[0].y)
        p23: Point = Point(self.p[2].x - self.p[1].x, self.p[2].y - self.p[1].y)

        ref: int = p12.crossProductScalar2D(p23)
        ref //= ref if ref > 0 else -ref

        # 세 꼭짓점과 임의의 점과의 외적 계산
        # 모든 외적이 ref와 동일한 부호이면 점은 삼각형 내부에 존재.
        # 모든 외적의 부호를 추합해 ref와 비교.
        val: int = 0
        for i in range(3):
            temp = self.p[i].crossProductScalar2D(point)
            temp //= temp if temp > 0 else -temp
            val += temp
        val //= val if val > 0 else -val

        return ref == val

