#pragma once

#include "BestNode.h"
#include "Point2D.h"
#include "CompareNodes.h"
#include <math.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class AStar
{
public:
	static constexpr int MAZE_SIZE = 100;
	static constexpr int SPACE_ASTAR = 1;
	static constexpr int PACMAN_ASTAR = 3;
	static constexpr int MONSTER_ASTAR = 4;
	static constexpr int COIN_ASTAR = 5;
	int start_point;
	int target_point;

private:
	int *maze[MAZE_SIZE][MAZE_SIZE];
	bool *a_star_started;
	int g;
	BestNode current;
	BestNode* node;
	BestNode* pointer_node;
	priority_queue <BestNode, vector <BestNode>, CompareNodes> priorityQueue;
	vector <BestNode> grayVector;
	vector <BestNode> blackVector;
	vector<BestNode>::iterator black_iterator;
	vector<BestNode>::iterator gray_iterator;

public:
	AStar(Point2D* start, Point2D* target, int maze[MAZE_SIZE][MAZE_SIZE]);
	AStar();
	~AStar();

	//Methods
	void run_pacman(bool *a_star_started);
	void run_monster(bool *a_star_started);
	void run_algorithm();
	void try_to_go_up();
	void try_to_go_down();
	void try_to_go_right();
	void try_to_go_left();
	void clean_leftover();
};

