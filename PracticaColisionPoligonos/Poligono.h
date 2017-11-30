#pragma once

#include<vector>


#include "Point.h"

using namespace std;

class Poligono
{
public:
	Poligono();
	~Poligono();

	Poligono(const Poligono & pVector);

	void addPoint(Point p);

	Point getPoint(int index);

	vector<Point> getPoints();

	//list<Point> getPointsList();

	void trasladar(Point p);

	void rotar(double angulo);

	void escalar(float factorEscalado);

	pair<Point, Point>getAABB();

	bool colision(const Poligono & p);

	bool puntoInteriorAABB(const Point & p) const;

private:
	vector<Point> pointsVector;

	Point aabb[2] = {Point(INT_MAX, INT_MAX), Point(INT_MIN, INT_MIN)};

	void recalcularAABB();

	bool aabbCruzadas(const Point & p);
	
};

