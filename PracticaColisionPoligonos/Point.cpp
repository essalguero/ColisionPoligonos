#include "stdafx.h"
#include "Point.h"


Point::Point()
{
	x = 0;
	y = 0;
}


Point::~Point()
{
}


void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

void Point::operator=(const Point &p) {
	x = p.x;
	y = p.y;
}

bool Point::operator<(const Point &p) const {
	if (x < p.x)
		return true;
	else if ((x == p.x) && (y < p.y))
		return true;

	return false;
}

bool Point::operator>(const Point &p) const {
	if (x > p.x)
		return true;
	else if ((x == p.x) && (y > p.y))
		return true;

	return false;
}

Point Point::operator+(const Point &p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator* (const float & factorEscalado) const {

	Point p;
	p.x = x * factorEscalado;
	p.y = y * factorEscalado;

	return p;
}

double Point::distance2(const Point &p) {
	double distX = x - p.x;
	double distY = y - p.y;

	return ((distX * distX) + (distY * distY));
}

// La funcion devuelve el coseno del angulo que forman los puntos a, b y c
double Point::angleCos(Point a, Point b, Point c) {

	double v1X = c.getX() - b.getX();
	double v1Y = c.getY() - b.getY();

	double v2X = a.getX() - b.getX();
	double v2Y = a.getY() - b.getY();

	double v1Mod = sqrt((v1X * v1X) + (v1Y * v1Y));
	double v2Mod = sqrt((v2X * v2X) + (v2Y * v2Y));

	double v1Dotv2 = (v1X * v2X) + (v1Y * v2Y);

	double value = v1Dotv2 / (v1Mod * v2Mod);

	return value;




}
