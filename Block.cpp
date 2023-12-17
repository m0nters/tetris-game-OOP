#include "Block.h"

Block::Block()
{
	cellSize = 30;
	rotation = 0;
	colors = GetCellColors();
	rowOffset = 0;
	columnOffset = 0;
}
void Block::Draw(int horizontalOffset, int verticalOffset)
{
	std::vector<Position> blockCells = GetCellPosition();
	for (Position cell : blockCells)
	{
		DrawRectangle(cell.column * cellSize + horizontalOffset, cell.row * cellSize + verticalOffset, cellSize - 1, cellSize - 1, colors[blockType]);
	}
}
LBlock::LBlock()
{
	blockType = 1;
	cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
	cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
	cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) };
	cells[3] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
	Move(0, 3);
}
IBlock::IBlock()
{
	blockType = 2;
	cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
	cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
	cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
	cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
	Move(-1, 3);
}
JBlock::JBlock()
{
	blockType = 3;
	cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
	cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(0, 2) };
	cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) };
	cells[3] = { Position(2, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
	Move(0, 3);
}
OBlock::OBlock()
{
	blockType = 4;
	cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
	cells[1] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
	cells[2] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
	cells[3] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
	Move(0, 4);
}
SBlock::SBlock()
{
	blockType = 5;
	cells[0] = { Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) };
	cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) };
	cells[2] = { Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) };
	cells[3] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) };
	Move(0, 3);
}
TBlock::TBlock()
{
	blockType = 6;
	cells[0] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) };
	cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(1, 2) };
	cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) };
	cells[3] = { Position(1, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
	Move(0, 3);
}
ZBlock::ZBlock()
{
	blockType = 7;
	cells[0] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
	cells[1] = { Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) };
	cells[2] = { Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) };
	cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) };
	Move(0, 3);
}
void Block::Move(int row, int column)
{
	rowOffset += row;
	columnOffset += column;
}
std::vector<Position> Block::GetCellPosition()
{
	std::vector<Position> blockCells = cells[rotation];
	std::vector<Position> moved;
	for (Position cell : blockCells)
	{
		Position newPos = Position(cell.row + rowOffset, cell.column + columnOffset);
		moved.push_back(newPos);
	}
	return moved;
}

void Block::Rotate()
{
	rotation++;
	if (rotation == (int)cells.size())
		rotation = 0;
}

void Block::UndoRotate()
{
	rotation--;
	if (rotation == -1)
		rotation = (int)cells.size() - 1;
}
