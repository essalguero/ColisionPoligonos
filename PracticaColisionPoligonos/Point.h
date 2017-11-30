#pragma once

#include <iostream>

using namespace std;

class Point
{
public:
	Point();
	Point(int x, int y) : x(x), y(y) {}

	Point(const Point& p): x(p.x), y(p.y) {}

	~Point();


	void setX(int x);
	void setY(int y);

	inline int getX() const { return x; };
	inline int getY() const { return y; };

	Point operator+(const Point & p) const ;
	void operator=(const Point & p);
	bool operator<(const Point &p) const;
	bool operator>(const Point &p) const;

	Point operator* (const float & factorEscalado) const;

	inline bool operator!=(const Point & p) const {
		return ((x != p.x) || (y != p.y));
	}

	inline bool operator==(const Point & p) const {
		return ((x == p.x) && (y == p.y));
	}

	friend ostream & operator<<(ostream & stream, const Point & p) {
		return stream << "(" << p.x << ", " << p.y << ")";
	}

	double distance2(const Point &p);


	static inline int Area2(const Point & a, const Point & b, const Point & c)
	{
		return ((b.getX() - a.getX()) * (c.getY() - a.getY())) -
			((c.getX() - a.getX()) * (b.getY() - a.getY()));
	}

	inline static bool left(Point a, Point b, Point c) {
		bool value = Area2(a, b, c) > 0;
		return value;
	}

	// Devuelve el coseno del ángulo que forman los puntos a, b y c
	static double angleCos(Point a, Point b, Point c);

private:
	int x;
	int y;
};

