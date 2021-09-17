//============================================================================
// Name        : Chap01-Triangle.cpp
// Author      : 김상진
// Version     : 2021년도 2학기
// Copyright   : 한국기술교육대학교 컴퓨터공학부 자료구조및실습
// Description : 삼각형 클래스
//============================================================================

// 2020136018 김성녕

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <stdexcept>
#include <algorithm>

struct Point{
	int x;
	int y;

	// 점의 일치 여부를 판단하기 위한 함수.
	bool equals(const Point& other) const {
		bool xCondition = this->x == other.x;
		bool yCondition = this->y == other.y;

		return xCondition && yCondition;
	}

	// 2차원 벡터끼리의 외적의 크기를 반환.
	// 점의 위치 관계를 구하기 위함.
	// ref: http://www.findmean.com/%EC%88%98%ED%95%99/%EB%B2%A1%ED%84%B0/%EB%B2%A1%ED%84%B0%EC%9D%98-%EC%99%B8%EC%A0%81/
	int crossProductScalar2D(const Point& other) const {
		return this->x * other.y - other.x * this->y;
	}
};

class Triangle{
private:
	Point p1;
	Point p2;
	Point p3;

	// 연산의 편의를 위한 배열화.
	Point* p;
public:
	// 주어진 좌표로 삼각형을 만들 수 없으면 std::runtime_error 예외를 발생해야 함
	Triangle(const Point& p1, const Point& p2, const Point& p3):
		p1(p1), p2(p2), p3(p3){
		// 연산의 편의를 위한 배열화.
		p = new Point[3];
		for (int i = 0; i < 3; i++)
			p[i] = *(&this->p1 + i);

		// 삼각형 결정조건: 서로 다른 세 개의 점.
		int pointsEq = 0;
		for (int i = 0 ; i < 3; i++)
			pointsEq += p[i].equals(p[(i + 1) % 3]);
		if (pointsEq >= 2)
			throw std::runtime_error("삼각형 결정조건 불만족: 두 개 이상의 점이 서로 일치합니다.");

		// 삼각형 결정조건: 한 직선 위에 있지 않은 서로 다른 세 개의 점.
		const Point p31{p[2].x - p[0].x, p[2].y - p[0].y};
		const Point p32{p[2].x - p[1].x, p[2].y - p[1].y};
		if (p31.crossProductScalar2D(p32) == 0)
			throw std::runtime_error("삼각형 결정조건 불만족: 세 개의 점이 한 직선 위에 있습니다.");
	}
	~Triangle() {
		delete[] p;
	}
	// 삼각형의 면적
	double area(){
		int temp = 0;

		// 신발끈 공식 이용.
		// ref: https://ko.wikipedia.org/wiki/%EC%8B%A0%EB%B0%9C%EB%81%88_%EA%B3%B5%EC%8B%9D
		for (int i = 0; i < 3; i++) {
			temp += p[i].x * p[(i + 1) % 3].y;
			temp -= p[i].y * p[(i + 1) % 3].x;
		}
		temp = temp > 0 ? temp : -temp;

		return 0.5 * temp;
	}
	// 주어진 좌표가 삼각형 내부에 있는 여부
	bool isInside(const Point& point){
		// 외적을 이용한 점의 위치 관계 이용.
		// ref: https://bbungprogram.tistory.com/13

		// 임의의 점 세 개의 배열을 판단하는 변수 ref.
		// if ref > 0: 반시계 방향 배열, elif ref < 0: 시계 방향 배열
		const Point p12{p[1].x - p[0].x, p[1].y - p[0].y};
		const Point p23{p[2].x - p[1].x, p[2].y - p[1].y};

		int ref = p12.crossProductScalar2D(p23);
		ref /= ref > 0 ? ref : -ref; // ref의 부호 추출.

		// 세 꼭짓점과 임의의 점과의 외적 계산.
		// 모든 외적이 ref와 동일한 부호이면 점은 삼각형 내부에 존재.
		// 모든 외적의 부호를 추합해 ref와 비교.
		int val = 0;
		for (int i = 0; i < 3; i++) {
			int temp = p[i].crossProductScalar2D(point);
			temp /= temp > 0 ? temp : -temp;
			val += temp;
		}
		val /= val > 0 ? val : -val;

		return  ref == val;
	}
};

#endif
