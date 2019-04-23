#include "CompareNodes.h"

CompareNodes::CompareNodes()
{
}

CompareNodes::~CompareNodes()
{
}

bool CompareNodes::operator() (BestNode &b1, BestNode &b2)
{
	if (b1.getF() > b2.getF())
		return true;
	else
		return false;
}
