#pragma once
#include "Point2D.h"

class BestNode
{
private:
	Point2D* point;
	Point2D* target_point;
	BestNode* parent;
	int f;
	int g;

public:
	BestNode(Point2D*, Point2D*);
	BestNode(const BestNode&);
	BestNode();
	~BestNode();

	//Getters
	Point2D* GetPoint();
	BestNode* getParent();
	int getF();
	int getG();

	//Setters
	void setTargetPoint(Point2D*);
	void setParent(BestNode*);
	void setF();
	void setG(int);
	void setPoint(int, int);
	
	//Methods
	int h();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	bool operator==(const BestNode&);
};

