#include "Grid.h"

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	InitializeGrid();
	colors = GetCellColors();
}
void Grid::InitializeGrid()
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++)
			grid[i][j] = 0;
}
void Grid::Print()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
			std::cout << grid[i][j] << " ";
		std::cout << std::endl;
	}
}
void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int value = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize - 1, cellSize - 1, colors[value]);
		}
	}
}
bool Grid::isCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
		return false;
	return true;
}

bool Grid::isCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
		return true;
	return false;
}
bool Grid::isRowFull(int row)
{
	for (int i = 0; i < numCols; i++)
		if (grid[row][i] == 0)
			return false;
	return true;
}

void Grid::clearRow(int row)
{
	for (int i = 0; i < numCols; i++)
	{
		grid[row][i] = 0;
	}
}

void Grid::moveRow(int row, int num)
{
	for (int i = 0; i < numCols; i++)
	{
		grid[row + num][i] = grid[row][i];
		grid[row][i] = 0;
	}
}
int Grid::clearRow()
{
	int count = 0;
	for (int i = numRows - 1; i >= 0; i--)
	{
		if (isRowFull(i))
		{
			clearRow(i);
			count++;
		}
		else if (count > 0)
			moveRow(i, count);
	}
	return count;
}