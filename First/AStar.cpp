#include "AStar.h"

AStar::AStar(Point2D* start, Point2D* target, int maze[MAZE_SIZE][MAZE_SIZE])
{
	this->g = 0;
	this->node = new BestNode(start, target);
	this->priorityQueue.emplace(*this->node);
	this->grayVector.push_back(*this->node);
	this->pointer_node = NULL;

	int i, j;
	for (i = 0; i < MAZE_SIZE; i++)
		for (j = 0; j < MAZE_SIZE; j++)
			this->maze[i][j] = &maze[i][j];
}

AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::run_pacman(bool *a_star_started)
{
	this->a_star_started = a_star_started;
	start_point = PACMAN_ASTAR;
	target_point = COIN_ASTAR;
	run_algorithm();
}

void AStar::run_monster(bool *a_star_started)
{
	this->a_star_started = a_star_started;
	start_point = MONSTER_ASTAR;
	target_point = PACMAN_ASTAR;
	run_algorithm();
}

void AStar::run_algorithm()
{
	if (priorityQueue.empty())
	{
		this->a_star_started = false;
		return;
	}
	else
	{
		current = priorityQueue.top();
		priorityQueue.pop();
		blackVector.push_back(current);

		gray_iterator = find(grayVector.begin(), grayVector.end(), current);
		grayVector.erase(gray_iterator);

		if (*maze[current.GetPoint()->GetY()][current.GetPoint()->GetX()] == target_point)
			this->a_star_started = false;
		else
		{
			if (*maze[current.GetPoint()->GetY()][current.GetPoint()->GetX()] != start_point)
				*maze[current.GetPoint()->GetY()][current.GetPoint()->GetX()] = start_point;

			if (start_point == PACMAN_ASTAR)
				node->setPoint(current.GetPoint()->GetY(), current.GetPoint()->GetX());

			if (this->a_star_started)
			{
				try_to_go_up();
				try_to_go_down();
				try_to_go_right();
				try_to_go_left();

				if (a_star_started)
					clean_leftover();
				if (start_point == PACMAN_ASTAR)
					target_point = COIN_ASTAR;
			}
			return;
		}
		return;
	}
}

void AStar::clean_leftover()
{
	if (start_point == PACMAN_ASTAR)
		target_point = MONSTER_ASTAR;
	for (black_iterator = blackVector.begin(); black_iterator != blackVector.end(); black_iterator++)
		if (!black_iterator->operator==(current))
			if (*maze[black_iterator->GetPoint()->GetY()][black_iterator->GetPoint()->GetX()] != target_point)
				*maze[black_iterator->GetPoint()->GetY()][black_iterator->GetPoint()->GetX()] = SPACE_ASTAR;
}

void AStar::try_to_go_up()
{
	if (*maze[current.GetPoint()->GetY() + 1][current.GetPoint()->GetX()] == target_point)
		*a_star_started = false;
	if (a_star_started && *maze[current.GetPoint()->GetY() + 1][current.GetPoint()->GetX()] == SPACE_ASTAR)
	{
		current.move_up();
		pointer_node = new BestNode(current);
		current.setG(g - 1);
		black_iterator = find(blackVector.begin(), blackVector.end(), *pointer_node);
		gray_iterator = find(grayVector.begin(), grayVector.end(), *pointer_node);
		if (black_iterator == blackVector.end() && gray_iterator == grayVector.end())
		{
			priorityQueue.emplace(*pointer_node);
			grayVector.push_back(*pointer_node);
		}
		current.move_down();
		current.setG(g - 1);
	}
}

void AStar::try_to_go_down()
{
	if (*maze[current.GetPoint()->GetY() - 1][current.GetPoint()->GetX()] == target_point)
		*a_star_started = false;
	if (a_star_started && *maze[current.GetPoint()->GetY() - 1][current.GetPoint()->GetX()] == SPACE_ASTAR)
	{
		current.move_down();
		pointer_node = new BestNode(current);
		current.setG(g - 1);
		black_iterator = find(blackVector.begin(), blackVector.end(), *pointer_node);
		gray_iterator = find(grayVector.begin(), grayVector.end(), *pointer_node);
		if (black_iterator == blackVector.end() && gray_iterator == grayVector.end())
		{
			priorityQueue.emplace(*pointer_node);
			grayVector.push_back(*pointer_node);
		}
		current.move_up();
		current.setG(g - 1);
	}
}

void AStar::try_to_go_right()
{
	if (*maze[current.GetPoint()->GetY()][current.GetPoint()->GetX() + 1] == target_point)
		*a_star_started = false;
	if (a_star_started && *maze[current.GetPoint()->GetY()][current.GetPoint()->GetX() + 1] == SPACE_ASTAR)
	{
		current.move_right();
		pointer_node = new BestNode(current);
		current.setG(g - 1);
		black_iterator = find(blackVector.begin(), blackVector.end(), *pointer_node);
		gray_iterator = find(grayVector.begin(), grayVector.end(), *pointer_node);
		if (black_iterator == blackVector.end() && gray_iterator == grayVector.end())
		{
			priorityQueue.emplace(*pointer_node);
			grayVector.push_back(*pointer_node);
		}
		current.move_left();
		current.setG(g - 1);
	}
}

void AStar::try_to_go_left()
{
	if (*maze[current.GetPoint()->GetY()][current.GetPoint()->GetX() - 1] == target_point)
		*a_star_started = false;
	if (a_star_started && *maze[current.GetPoint()->GetY()][current.GetPoint()->GetX() - 1] == SPACE_ASTAR)
	{
		current.move_left();
		pointer_node = new BestNode(current);
		current.setG(g - 1);
		black_iterator = find(blackVector.begin(), blackVector.end(), *pointer_node);
		gray_iterator = find(grayVector.begin(), grayVector.end(), *pointer_node);
		if (black_iterator == blackVector.end() && gray_iterator == grayVector.end())
		{
			priorityQueue.emplace(*pointer_node);
			grayVector.push_back(*pointer_node);
		}
		current.move_right();
		current.setG(g - 1);
	}
}
