// PracticaColisionPoligonos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Poligono.h"


#include "Point.h"

using namespace std;

int main()
{

	Poligono p1;

	p1.addPoint(Point(10, 140));
	p1.addPoint(Point(120, 120));
	p1.addPoint(Point(170, 150));
	p1.addPoint(Point(140, 190));
	p1.addPoint(Point(110, 140));
	p1.addPoint(Point(10, 140));

	pair<Point, Point> p1AABB = p1.getAABB();

	
	cout << "Poligono Inicial: " << endl;


	for (Point p : p1.getPoints())
	{
		cout << p << endl;
	}

	cout << endl << endl;

	cout << "Axis Aligned Bounding Box: " << p1AABB.first << " - " << p1AABB.second << endl << endl << endl;


	Point vectorTraslacion(20, 10);

	cout << "Trasladar el poligono con un vector: " << vectorTraslacion << endl << endl;
		

	Poligono pTrasladado(p1);

	pTrasladado.trasladar(vectorTraslacion);

	pair <Point, Point> p2AABB = pTrasladado.getAABB();

	cout << "Poligono Trasladado: " << endl;

	for (Point p : pTrasladado.getPoints())
	{
		cout << p << endl;
	}

	cout << endl << endl;



	cout << "Axis Aligned Bounding Box: " << p2AABB.first << " - " << p2AABB.second << endl << endl << endl;


	Poligono pRotado(p1);
	pRotado.rotar(90);

	pair <Point, Point> pRotadoAABB = pRotado.getAABB();

	cout << "Poligono Rotado: " << endl;

	for (Point p : pRotado.getPoints())
	{
		cout << p << endl;
	}

	cout << endl << endl;

	cout << "Axis Aligned Bounding Box: " << pRotadoAABB.first << " - " << pRotadoAABB.second << endl << endl << endl;



	Poligono pEscalado(p1);
	pEscalado.escalar(1.1);

	pair <Point, Point> pEscaladoAABB = pEscalado.getAABB();

	cout << "Poligono Escalado: " << endl;

	for (Point p : pEscalado.getPoints())
	{
		cout << p << endl;
	}

	cout << endl << endl;

	cout << "Axis Aligned Bounding Box: " << pEscaladoAABB.first << " - " << pEscaladoAABB.second << endl << endl << endl;


	p1.colision(pTrasladado);

    return 0;
}



