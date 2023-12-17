#pragma once
#include"grid.h"
#include"Block.h"
#include<random>

class Game
{
private:
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Sound RowClearedSound;
	Sound BlockRotatedSound;
	Sound MoveSound;
	void RotateBlock();
	bool isBlockOutside();
	void LockBlock();
	bool CheckCollision();
	void Restart();
	void UpdateScore(int linesCleared);
public:
	Grid grid;
	Music music;
	Game();
	~Game();
	Block getRandomBlock();
	void Draw();
	std::vector<Block> getAllBlock();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	void MoveDownImmediately();
	bool isBlockNested();
	bool gameOver, musicStopped, isPaused;
	int currentLevel;
	double moveSpeed;
	int score;
};

