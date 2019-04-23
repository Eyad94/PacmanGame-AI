#include "Point2D.h"

Point2D::Point2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point2D::Point2D(): x(0)
{
}

Point2D::~Point2D()
{
}

int Point2D::GetX()
{
	return x;
}

int Point2D::GetY()
{
	return y;
}

void Point2D::setY(int y)
{
	this->y = y;
}

void Point2D::setX(int x)
{
	this->x = x;
}
