#pragma once
#include<vector>
#include<map>
#include"Position.h"
#include"Color.h"

class Block
{
private:
	int cellSize;
	int rotation;
	int rowOffset, columnOffset;
public:
	int blockType;
	std::map<int, std::vector<Position>> cells;
	std::vector<Color> colors;
	Block();
	void Draw(int horizontalOffset, int verticalOffset);
	void Move(int row, int column);
	std::vector<Position> GetCellPosition();
	void Rotate();
	void UndoRotate();
};
class LBlock : public Block
{
public:
	LBlock();
};
class IBlock : public Block
{
public: 
	IBlock();
};
class JBlock : public Block
{
public:
	JBlock();
};
class OBlock : public Block
{
public:
	OBlock();
};
class SBlock : public Block
{
public:
	SBlock();
};
class TBlock : public Block
{
public:
	TBlock();
};
class ZBlock : public Block
{
public:
	ZBlock();
};
