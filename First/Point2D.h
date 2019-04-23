#pragma once
class Point2D
{
private:
	int x;
	int y;

public:
	Point2D(int x, int y);
	Point2D();
	~Point2D();

	int GetX();
	int GetY();
	void setY(int);
	void setX(int);
};