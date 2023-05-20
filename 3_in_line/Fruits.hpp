#pragma once
#include "Source.cpp"

class fruits {
public:
	static const int NUM_FRUITS = 6;
	int fruit[NUM_FRUITS][NUM_FRUITS];
	void drawField();
	void printfruits();
	void fillFruits();
	int mark[6][6];
	bool delGroups();
	void findGroups(int row, int col, int dx, int dy);
	void mouse(int button, int state, int x, int y);
	void shiftDown();
};