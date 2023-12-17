#pragma once
#include<iostream>
#include<vector>
#include<raylib.h>
#include"Color.h"

class Grid
{
private:
	int numRows, numCols;
	int cellSize;
	std::vector<Color> colors;
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRow(int row, int numRows);
public:
	Grid();
	void InitializeGrid();
	void Print();
	void Draw();
	int grid[20][10];
	bool isCellOutside(int row, int column);
	bool isCellEmpty(int row, int column);
	int clearRow();
};
