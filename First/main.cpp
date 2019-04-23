#include "GLUT.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <queue>
#include <math.h>
#include "Point2D.h"
#include "BestNode.h"
#include "CompareNodes.h"
#include "AStar.h"

using namespace std;

const int W = 600; // window width
const int H = 600; // window height

const int SPACE = 1;
const int WALL = 2;
const int PACMAN = 3;
const int MONSTER = 4;
const int COIN = 5;

const int MSIZE = 100;
const double SQSIZE = 2.0 / MSIZE;

int maze[MSIZE][MSIZE];

bool a_star_started = false;

// gray queue
vector <BestNode> gray;
vector <BestNode> black;

//target point
Point2D* pacman_point, *start_first_monster_point, *start_second_monster_point, *start_third_monster_point, *random_point;

AStar *pacman, *first_monster, *second_monster, *third_monster;

void SetupMaze();

void init()
{
	int i, j;

	srand(time(0));

	// clean up the maze
	for (i = 0; i < MSIZE; i++)
		for (j = 0; j < MSIZE; j++)
			maze[i][j] = SPACE;

	SetupMaze();

	maze[MSIZE / 2][MSIZE / 2] = PACMAN;
	pacman_point = new Point2D(MSIZE / 2, MSIZE / 2);

	start_first_monster_point = new Point2D(rand() % MSIZE, rand() % MSIZE);
	start_second_monster_point = new Point2D(rand() % MSIZE, rand() % MSIZE);
	start_third_monster_point = new Point2D(rand() % MSIZE, rand() % MSIZE);
	random_point = new Point2D(rand() % MSIZE, rand() % MSIZE);

	maze[start_first_monster_point->GetY()][start_first_monster_point->GetX()] = MONSTER;
	maze[start_second_monster_point->GetY()][start_second_monster_point->GetX()] = MONSTER;
	maze[start_third_monster_point->GetY()][start_third_monster_point->GetX()] = MONSTER;
	maze[random_point->GetY()][random_point->GetX()] = COIN;

	first_monster = new AStar(start_first_monster_point, pacman_point, maze);
	second_monster = new AStar(start_second_monster_point, pacman_point, maze);
	third_monster = new AStar(start_third_monster_point, pacman_point, maze);
	pacman = new AStar(pacman_point, random_point, maze);

	glClearColor(GLclampf(0.7), GLclampf(0.7), GLclampf(0.7), 0);

	glOrtho(-1, 1, -1, 1, -1, 1);
}

void SetupMaze()
{
	int i, j;

	for (i = 0; i < MSIZE; i++)
	{
		maze[i][0] = maze[i][MSIZE - 1] = WALL;
		maze[0][i] = maze[MSIZE - 1][i] = WALL;
	}
	// set walls
	for (i = 1; i < MSIZE - 1; i++)
		for (j = 1; j < MSIZE - 1; j++)
		{
			if (i % 2 == 0) // mostly walls
			{
				if (rand() % 100 < 50) maze[i][j] = WALL;
			}
			else // mostly spaces
			{
				if (rand() % 100 < 25) maze[i][j] = WALL;
			}
		}
}

void AstarSearch()
{
	if (a_star_started) first_monster->run_monster(&a_star_started);
	if (a_star_started) second_monster->run_monster(&a_star_started);
	if (a_star_started) third_monster->run_monster(&a_star_started);
	if (a_star_started) pacman->run_pacman(&a_star_started);
}

void DrawMaze()
{
	int i, j;

	for (i = 0; i < MSIZE; i++)
		for (j = 0; j < MSIZE; j++)
		{
			switch (maze[i][j])
			{
			case WALL:
				glColor3d(0.4, 0, 0); // dark red;
				break;
			case SPACE:
				glColor3d(1, 1, 1); // white;
				break;
			case PACMAN:
				glColor3d(0, 0, 1); // blue;
				break;
			case MONSTER:
				glColor3d(1, 0, 0); // RED;
				break;
			case COIN:
				glColor3d(1, .5, 0); // ORANGE;
				break;
			}
			// draw square
			glBegin(GL_POLYGON);
			glVertex2d(j*SQSIZE - 1 - SQSIZE / 2, i*SQSIZE - 1 + SQSIZE / 2);
			glVertex2d(j*SQSIZE - 1 + SQSIZE / 2, i*SQSIZE - 1 + SQSIZE / 2);
			glVertex2d(j*SQSIZE - 1 + SQSIZE / 2, i*SQSIZE - 1 - SQSIZE / 2);
			glVertex2d(j*SQSIZE - 1 - SQSIZE / 2, i*SQSIZE - 1 - SQSIZE / 2);
			glEnd();
		}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawMaze();
	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	if (a_star_started)
		AstarSearch();
	glutPostRedisplay();// calls indirectly to display
}

void Menu(int choice)
{
	switch (choice)
	{
	case 1:
		a_star_started = true;
		break;
	}

}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("PACMAN GAME");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // idle: when nothing happens
	init();

	glutCreateMenu(Menu);
	glutAddMenuEntry("A*", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}