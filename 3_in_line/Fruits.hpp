#pragma once
#include "Source.cpp"

static const int NUM_FRUITS = 6;

static int fruit[NUM_FRUITS][NUM_FRUITS];

static int randomazer(int min, int max) {
	return min + rand() % (max - min + 1);
}

class fruits {
public:
	static void drawField();
	static void printfruits();
	static void fillFruits();
	static bool delGroups();
	static void findGroups(int row, int col, int dx, int dy);
	static void mouse(int button, int state, int x, int y);
	static void shiftDown();
};