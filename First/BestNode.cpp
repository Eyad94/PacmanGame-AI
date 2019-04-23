#include "BestNode.h"
#include <stdlib.h>

BestNode::BestNode(Point2D *start_point, Point2D *target_point)
{
	this->point = start_point;
	this->target_point = target_point;
}

BestNode::BestNode(const BestNode & other)
{
	point = new Point2D(other.point->GetX(), other.point->GetY());
	target_point = other.target_point;
	parent = other.parent;
	f = other.f;
	g = other.g;
}

BestNode::BestNode()
{
	this->g = 0;
	this->f = 0;
}

BestNode::~BestNode()
{
}

Point2D* BestNode::GetPoint()
{
	return point;
}

void BestNode::setTargetPoint(Point2D *point)
{
	target_point = point;
}

int BestNode::getF()
{
	return f;
}

void BestNode::setF()
{
	f = (int)(0.2 * g + 0.8 * h());
}

void BestNode::setPoint(int y, int x)
{
	point->setY(y);
	point->setX(x);
}

int BestNode::getG()
{
	return g;
}

void BestNode::setG(int new_g)
{
	g = new_g;
}

int BestNode::h()
{
	int target_y, target_x;
	target_y = point->GetY();
	target_x = point->GetX();
	return abs(target_point->GetY() - target_y) + abs(target_point->GetX() - target_x);
}

void BestNode::setParent(BestNode *parent)
{
	this->parent = parent;
}

BestNode * BestNode::getParent()
{
	return parent;
}

bool BestNode::operator==(const BestNode& other)
{
	if (point->GetX() == other.point->GetX() && point->GetY() == other.point->GetY())
		return true;
	return false;
}

void BestNode::move_up()
{
	this->setPoint(point->GetY() + 1, point->GetX());
	this->setG(g + 1);
	this->setF();
}

void BestNode::move_down()
{
	this->setPoint(point->GetY() - 1, point->GetX());
	this->setG(g + 1);
	this->setF();
}

void BestNode::move_right()
{
	this->setPoint(point->GetY(), point->GetX() + 1);
	this->setG(g + 1);
	this->setF();
}

void BestNode::move_left()
{
	this->setPoint(point->GetY(), point->GetX() - 1);
	this->setG(g + 1);
	this->setF();
}
