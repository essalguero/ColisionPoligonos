#include "stdafx.h"

#include <cmath>

#include "Poligono.h"



Poligono::Poligono()
{
}


Poligono::~Poligono()
{
}

Poligono::Poligono(const Poligono & p)
{
	pointsVector = p.pointsVector;
	aabb[0] = p.aabb[0];
	aabb[1] = p.aabb[1];
}

void Poligono::addPoint(Point p)
{
	pointsVector.push_back(p);

	if (pointsVector.size() == 1)
	{
		aabb[0] = p;
		aabb[1] = p;
	}
	else {

		if (p.getX() < aabb[0].getX())
		{
			aabb[0].setX(p.getX());
		}
		
		if (p.getX() > aabb[1].getX())
		{
			aabb[1].setX(p.getX());
		}

		if (p.getY() < aabb[0].getY())
		{
			aabb[0].setY(p.getY());
		}
		
		if (p.getY() > aabb[1].getY())
		{
			aabb[1].setY(p.getY());
		}
	}
}

Point Poligono::getPoint(int index)
{
	return pointsVector.at(index);
}

vector<Point> Poligono::getPoints()
{
	vector<Point> vectorP(pointsVector);

	return vectorP;
}



void Poligono::trasladar(Point p)
{
	// Trasladar el polinono
	for (auto it = pointsVector.begin(); it < pointsVector.end(); ++it)
	{
		(*it) = (*it) + p;
	}

	aabb[0] = aabb[0] + p;
	aabb[1] = aabb[1] + p;
}

void Poligono::rotar(double angulo) {
	double PI = atan(1.0) * 4;
	double coseno = cos((angulo * PI) / 180);
	double seno = sin((angulo * PI) / 180);
	
	for (auto it = pointsVector.begin(); it < pointsVector.end(); ++it)
	{
		int nuevoX{ 0 };
		int nuevoY{ 0 };
		nuevoX = static_cast<int>(coseno * (*it).getX() + (-seno * (*it).getY()));
		nuevoY = static_cast<int>(seno * (*it).getX() + (coseno * (*it).getY()));
		(*it).setX(nuevoX);
		(*it).setY(nuevoY);
		cout << endl;
	}

	recalcularAABB();
}

pair<Point, Point> Poligono::getAABB()
{
	pair<Point, Point> aabbPair = { aabb[0], aabb[1] };

	return aabbPair;
}


// Recalcular el AABB. Se debe utilizar por ejemplo después de una rotación
void Poligono::recalcularAABB()
{
	if (pointsVector.size() > 0)
	{
		if (pointsVector.size() == 1) {
			aabb[0] = pointsVector.at(0);
			aabb[1] = pointsVector.at(0);
		}
		else
		{
			aabb[0] = Point(INT_MAX, INT_MAX);
			aabb[1] = Point(INT_MIN, INT_MIN);
			for (Point p : pointsVector)
			{	
				if (p.getX() < aabb[0].getX())
				{
					aabb[0].setX(p.getX());
				}
				
				if (p.getX() > aabb[1].getX())
				{
					aabb[1].setX(p.getX());
				}

				if (p.getY() < aabb[0].getY())
				{
					aabb[0].setY(p.getY());
				}
				
				if (p.getY() > aabb[1].getY())
				{
					aabb[1].setY(p.getY());
				}
			}
		}
	}
}


void Poligono::escalar(float factorEscalado) {
	Point centroAABB(aabb[1].getX() - aabb[0].getX(), aabb[1].getY() - aabb[0].getY());

	Point vectorTraslacion(-centroAABB.getX(), -centroAABB.getY());

	trasladar(vectorTraslacion);

	for (auto it = pointsVector.begin(); it < pointsVector.end(); ++it) {
		(*it) = (*it) * factorEscalado;
	}

	vectorTraslacion.setX(-vectorTraslacion.getX());
	vectorTraslacion.setY(-vectorTraslacion.getY());

	trasladar(vectorTraslacion);

	recalcularAABB();
}


bool Poligono::colision(const Poligono & p) {

    // 2 posibles casos.
    // 1.- La AABB esta completamente dentro de la AABB de p
    // 2.- Almenos un vertice esta incluido
	double PI = atan(1.0) * 4;

	bool colision = false;

	// Comprobar si las AABB colisionan
	/*for (auto it = p.pointsVector.begin(); it < p.pointsVector.end() && !colision; ++it)
	{
		colision = puntoInteriorAABB(*it);
	}

	/*if (!colision)
	{
		for (auto it = pointsVector.begin(); it < pointsVector.end() && !colision; ++it)
		{
			colision = p.puntoInteriorAABB(*it);
		}
	}*/
    
    //pair <Point, Point> aabbP = p.aabb;
    Point pDerechaAbajo(p.aabb[1].getX(), p.aabb[0].getY());
    Point pIzquierdaArriba(p.aabb[0].getX(), p.aabb[1].getY());
    
    
    // Comprobar si las dos AABB son iguales
    if (p.aabb[0] == aabb[0] && p.aabb[1] == aabb[1]) {
        return true;
    }
    
    // Comprobar si hay algun punto de la AABB del poligono p dentro de la AABB de este poligono
    colision = puntoInteriorAABB(p.aabb[0]) || puntoInteriorAABB(p.aabb[1]) ||
        puntoInteriorAABB(pDerechaAbajo) || puntoInteriorAABB(pIzquierdaArriba);
    
    // Comprobar si la AABB tiene todos sus puntos dentro de la AABB de p
    if (!colision)
    {
        colision = p.puntoInteriorAABB(aabb[0]);
    }

	if (!colision)
	{
		return false;
	}

    // Calcular si hay colision de manera mas exacta
    // Metodo de los angulos
	double angulo = 0;
    for (auto it = pointsVector.begin(); it < pointsVector.end() - 1; ++it)
    {
		double angulo = 0;
		double coseno = 0;
		for (auto itP = p.pointsVector.begin(); itP < p.pointsVector.end() - 1; ++itP)
		{
			coseno = Point::angleCos(*itP, *it, *(itP + 1));
			double currentAngulo = (acos(coseno) * 180 / PI);

			// Angulo positivo si el punto *it esta a la izquierda de la linea (*itP, *(itP + 1))
			if (!Point::left(*itP, *(itP + 1), *it))
			{
				currentAngulo *= -1;
			}
			angulo += currentAngulo;
		}

		// Se ha detectado una colision?
		if (abs(abs(angulo) - 360.0) < 0.000000001) {
			return true;
		}
    }
    
	return false;
}


bool Poligono::puntoInteriorAABB(const Point & p) const {

	Point pDerechaAbajo(aabb[1].getX(), aabb[0].getY());
	Point pIzquierdaArriba(aabb[0].getX(), aabb[1].getY());

	bool incluido = Point::left(aabb[0], pDerechaAbajo, p) &&
		Point::left(pDerechaAbajo, aabb[1], p) &&
		Point::left(aabb[1], pIzquierdaArriba, p) &&
		Point::left(pIzquierdaArriba, aabb[0], p);

	return incluido;
}

// Comprueba el caso de que los limites de dos AABB se crucen, pero no tengan ninguno de sus puntos dentro de la otra
bool Poligono::aabbCruzadas(const Point & p) {
	return false;
}

