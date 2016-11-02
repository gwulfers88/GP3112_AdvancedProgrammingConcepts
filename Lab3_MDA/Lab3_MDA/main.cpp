/*
Name: George Wulfers
Class: Adv Prog Concepts
*/

#define ArrayCount(a) (sizeof(a) / sizeof(a[0]))

#include <iostream>
#include <random>
#include <Windows.h>

#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE
#define RED FOREGROUND_RED
COORD pos = { 0, 0 };

#include "Grid.h"

HANDLE consoleOut;

void GoToPos(int X, int Y)
{
	COORD pos = {(short)X, (short)Y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool isKeyDown(unsigned int vkCode)
{
	return (bool)(GetKeyState(vkCode) & 0x80000);
}

void SetDrawColor(unsigned int colors)
{
	SetConsoleTextAttribute(consoleOut, colors);
}

void drawGrid(COORD location, Grid grid, TBlock tBlock)
{
	for (int row = 0;
		row < CellCount;
		row++)
	{
		for (int col = 0;
			col < CellCount;
			col++)
		{
			GoToPos(location.X + col, location.Y + row);

			if (col >= pos.X && col < pos.X + TBlockWidth &&
				row >= pos.Y && row < pos.Y + TBlockHeight)
			{
				int blockRow = row - pos.Y;
				int blockCol = col - pos.X;
				int tileID = tBlock.cells[(blockRow)* TBlockWidth + (blockCol)];
				if (tileID >= 0)
				{
					SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					printf("%d", tileID);
				}
				else
				{
					SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%d", grid.cells[row * CellCount + col]);
				}
			}
			else
			{
				SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
				printf("%d", grid.cells[row * CellCount + col]);
			}
		}
		printf("\n");
	}
}

void drawOldGrid(COORD pos, Grid grid)
{
	for (int row = 0;
		row < CellCount;
		row++)
	{
		for (int col = 0;
			col < CellCount;
			col++)
		{
			GoToPos(pos.X + col, pos.Y + row);

			SetDrawColor(FOREGROUND_RED | FOREGROUND_BLUE);
			printf("%d", grid.cells[row * CellCount + col]);
		}
		printf("\n");
	}
}

void copyGrid(Grid& dest, Grid src)
{
	dest.width = src.width;
	dest.height = src.height;

	for (int row = 0;
		row < src.height;
		row++)
	{
		for (int col = 0;
			col < src.height;
			col++)
		{
			dest.cells[row*dest.width + col] = src.cells[row*src.width + col];
		}
	}
}

void drawCodex(COORD location, TBlock tBlock)
{
	for (int row = 0;
		row < TBlockHeight;
		row++)
	{
		for (int col = 0;
			col < TBlockWidth;
			col++)
		{
			GoToPos(location.X + col, location.Y + row);

			int tile = tBlock.cells[row * TBlockWidth + col];

			if (tile >= 0)
			{
				printf("%d", tile);
			}
			else
			{
				printf(" ");
			}
		}

		printf("\n");
	}
}

int main()
{
	srand(0);

	Grid grid;
	Grid oldGrid;

	consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(consoleOut, &csbi);

	grid.Initialize();

	copyGrid(oldGrid, grid);

	TBlock tBlock;
	tBlock.Initialize();

	COORD startPos	= {2, 2};
	COORD spacing	= {2, 0};
	COORD TBlockDim = {TBlockWidth, TBlockHeight};
	COORD infoStart = {2, startPos.Y + CellCount + spacing.Y};

	GoToPos(infoStart.X, infoStart.Y);

	
	printf("INFO: ESC to exit. WASD to move codex. ENTER/RETURN to apply codex. R reset grid cells.");

	SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

	GoToPos(0, 0);

	printf("TBlock\n");

	GoToPos(7, 0);

	SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("CellBlock\n");

	GoToPos(17, 0);

	SetDrawColor(FOREGROUND_RED | FOREGROUND_BLUE);

	printf("OldCellBlock\n");

	bool isRunning = true;

	while (isRunning)
	{
		if (isKeyDown(VK_ESCAPE))
		{
			isRunning = false;
		}
		
		if (isKeyDown('D'))
		{
			pos.X++;
		}
		else if (isKeyDown('A'))
		{
			pos.X--;
		}

		if (isKeyDown('W'))
		{
			pos.Y--;
		}
		else if (isKeyDown('S'))
		{
			pos.Y++;
		}
		
		if (isKeyDown(VK_RETURN))
		{
			Grid temp = grid;

			if (grid.flipCell(tBlock))
			{
				copyGrid(oldGrid, temp);
			}
		}
		else if (isKeyDown('R'))
		{
			grid.Initialize();
		}

		if (pos.X < 0)
		{
			pos.X = 0;
		}
		else if (pos.X + 3 > CellCount)
		{
			pos.X = CellCount - 3;
		}

		if (pos.Y < 0)
		{
			pos.Y = 0;
		}
		else if (pos.Y + 2 > CellCount)
		{
			pos.Y = CellCount - 2;
		}

		// DRAW CODE
		SetDrawColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

		GoToPos(0, 1);
		printf("Pos: (%d, %d)", pos.X, pos.Y);

		drawCodex(COORD{ startPos.X, startPos.Y }, tBlock);
		drawGrid(COORD{ startPos.X + TBlockDim.X + startPos.X, startPos.Y}, grid, tBlock);
		drawOldGrid(COORD{ startPos.X + TBlockDim.X + startPos.X + (short)grid.width + startPos.X, startPos.Y}, oldGrid);

		Sleep(100);
	}
	
	return 0;
}