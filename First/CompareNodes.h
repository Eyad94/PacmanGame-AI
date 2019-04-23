#pragma once
#include "BestNode.h"
class CompareNodes
{
public:
	CompareNodes();
	~CompareNodes();
	
	bool operator() (BestNode &b1, BestNode &b2);
};

