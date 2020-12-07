#pragma once
#ifndef POINT_H
#define POINT_H

#include "library.h"

struct Point2 {
	int x;
	int y;
	Point2() :x(0), y(0) {}
	template<class T1, class T2>
	Point2(const T1& x, const T2& y) : x((int)x), y((float)y) {}
	Point2(const Point2& p) : x(p.x), y(p.y) {}
	Point2 operator+(const Point2& point)const {
		return { x + point.x,y + point.y };
	}
	Point2 operator-(const Point2& point)const {
		return { x - point.x,y - point.y };
	}
	template <class T>
	Point2 operator*(const T& val)const {
		return { x * val,y * val };
	}
	template <class T>
	Point2 operator/(const T& val)const {
		return { x / val,y / val };
	}
	template <class T>
	Point2 operator+(const T& val)const {
		return { x + val,y + val };
	}
	template <class T>
	Point2 operator-(const T& val)const {
		return { x - val,y - val };
	}
	const int& operator[](const int& i) {
		if (i < 0 || i > 1) {
			std::cout << "Index out of bounds for instance of [Vertex]" << std::endl;
			exit(1);
		}
		switch (i) {
		case 0: return x;
		case 1: return y;
		}
	}
	inline bool operator==(const Point2& p) const {
		return ((p.x == x) && (p.y == y));
	}
	void print(void)const {
		std::cout << "[" << x << "|" << y << "]";
	}
	friend std::ostream& operator<<(std::ostream& os, const Point2& p);
	static int distance(const Point2& a, const Point2& b) {
		return static_cast<int>(sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
	}
	int distance(const Point2& p) const {
		return static_cast<int>(sqrtf((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)));
	}
};

std::ostream& operator<<(std::ostream& os, const Point2& p) {
	return (os << "[" << p.x << "|" << p.y << "]");
}

#endif // !POINT_H
