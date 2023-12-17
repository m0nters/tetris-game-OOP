#include "game.h"

Game::Game()
{
	grid = Grid();
	blocks = getAllBlock();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false;
	musicStopped = false;
	isPaused = false;
	score = 0;
	currentLevel = 1;
	moveSpeed = 0.4;
	InitAudioDevice();
	music = LoadMusicStream("main_music.mp3");
	BlockRotatedSound = LoadSound("rotate.mp3");
	RowClearedSound = LoadSound("clear.mp3");
	MoveSound = LoadSound("move.mp3");
	SetSoundVolume(MoveSound, 0.3);
}
Game::~Game()
{
	UnloadSound(MoveSound);
	UnloadSound(BlockRotatedSound);
	UnloadSound(RowClearedSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}
std::vector<Block> Game::getAllBlock()
{
	return { LBlock(), IBlock(), JBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}
Block Game::getRandomBlock()
{
	srand(time(NULL));
	if (blocks.empty())
		blocks = getAllBlock();
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}
void Game::Draw()
{
	grid.Draw();
	if (!gameOver)
		currentBlock.Draw(11, 11);
	switch (nextBlock.blockType)
	{
	case 2: 
		nextBlock.Draw(255, 240);
		break;
	case 4: 
		nextBlock.Draw(255, 230);
		break;
	default:
		nextBlock.Draw(270, 225);
		break;
	}
}
void Game::HandleInput()
{
	int key = GetKeyPressed();
	if (gameOver && key != 0)
	{
		gameOver = false;
		key = 0;
		Restart();
	}
	switch (key)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	case KEY_LEFT_CONTROL:
		RotateBlock();
		break;
	case KEY_SPACE: 
		MoveDownImmediately();
		break;
	}
}
void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (isBlockOutside() || CheckCollision())
			currentBlock.Move(0, 1);
		PlaySound(MoveSound);
	}
}
void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (isBlockOutside() || CheckCollision())
			currentBlock.Move(0, -1);
		PlaySound(MoveSound);
	}
}
void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (isBlockOutside() || CheckCollision())
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}
void Game::MoveDownImmediately()
{
	if (!gameOver) 
	{
		while (!isBlockOutside() && !CheckCollision()) {
			currentBlock.Move(1, 0);
		}
		currentBlock.Move(-1, 0);
		LockBlock();
		PlaySound(MoveSound);
	}
}
bool Game::isBlockNested()
{
	std::vector<Position> blockCells = currentBlock.GetCellPosition();
	for (Position cell : blockCells)
	{
		if (!grid.isCellEmpty(cell.row, cell.column) || grid.isCellOutside(cell.row, cell.column))
		{
			return true;
		}
	}
	return false;
}
void Game::LockBlock()
{
	std::vector<Position> blockCells = currentBlock.GetCellPosition();
	while (isBlockNested())
	{
		currentBlock.Move(-1, 0);
		blockCells = currentBlock.GetCellPosition();
	}
	for (Position cell : blockCells)
	{
		grid.grid[cell.row][cell.column] = currentBlock.blockType;
	}
	currentBlock = nextBlock;
	if (CheckCollision())
	{
		gameOver = true;
	}
	nextBlock = getRandomBlock();
	int linesCleared = grid.clearRow();
	if (linesCleared > 0)
	{
		PlaySound(RowClearedSound);
		UpdateScore(linesCleared);
	}
}
bool Game::CheckCollision()
{
	std::vector<Position> blockCells = currentBlock.GetCellPosition();
	for (Position cell : blockCells)
	{
		if (!grid.isCellEmpty(cell.row, cell.column) || grid.isCellOutside(cell.row, cell.column))
		{
			return true;
		}
	}
	return false;
}
bool Game::isBlockOutside()
{
	std::vector<Position> blockCells = currentBlock.GetCellPosition();
	for (Position cell : blockCells)
		if (grid.isCellOutside(cell.row, cell.column))
			return true;
	return false;
}
void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();
		if (isBlockOutside() || CheckCollision())
			currentBlock.UndoRotate();
		else PlaySound(BlockRotatedSound);
	}
}
void Game::Restart()
{
	grid.InitializeGrid();
	blocks = getAllBlock();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	score = 0;
	currentLevel = 1;
	moveSpeed = 0.4;
	musicStopped = false;
}

void Game::UpdateScore(int linesCleared)
{
	switch (linesCleared)
	{
	case 1: 
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4: 
		score += 700;
		break;
	default:
		break;
	}
	if (score >= 100 && currentLevel == 1) 
	{
		currentLevel = 2;
		moveSpeed = 0.3;
	}
	else if (score >= 300 && currentLevel == 2) 
	{
		currentLevel = 3;
		moveSpeed = 0.2; 
	}
	else if (score >= 500 && currentLevel == 3) 
	{
		currentLevel = 4;
		moveSpeed = 0.15;
	}
	else if (score >= 700 && currentLevel == 4) 
	{
		currentLevel = 5;
		moveSpeed = 0.1;
	}
}

