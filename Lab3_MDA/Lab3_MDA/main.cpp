/*
Name: George Wulfers
Class: Adv Prog Concepts
*/

#include <iostream>
#include <random>
#include <Windows.h>

#define CellCount 6
#define TBlockWidth 3
#define TBlockHeight 2

COORD pos = { 0, 0 };

//int Cells[CellCount * CellCount] = { 0 };
//int TBlock[TBlockWidth * TBlockHeight] = { 0, 1, 1, -1, 1, -1 };

void GoToPos(int X, int Y)
{
	COORD pos = {X, Y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class TBlock
{
public:
	TBlock()
	{
		width = TBlockWidth;
		height = TBlockHeight;
	}
	~TBlock() { }

	inline void Initialize()
	{
		cells[0 * width + 0] = 0;
		cells[0 * width + 1] = 1;
		cells[0 * width + 2] = 1;

		cells[1 * width + 0] = -1;
		cells[1 * width + 1] = 1;
		cells[1 * width + 2] = -1;
	}

	int width;
	int height;
	int cells[TBlockWidth * TBlockHeight];
};

class Grid
{
public:
	Grid()
	{
		width = height = CellCount;
	}

	~Grid() { }

	inline void Initialize()
	{
		for (int row = 0;
			row < CellCount;
			row++)
		{
			for (int col = 0;
				col < CellCount;
				col++)
			{
				cells[row * CellCount + col] = rand() % 2;
			}
		}
	}

	inline bool flipCell(TBlock t)
	{
		for (int row = pos.Y;
			row < pos.Y + 2;
			row++)
		{
			for (int col = pos.X;
				col < pos.X + 3;
				col++)
			{
				int cellTile = cells[row * CellCount + col];
				int blockTile = t.cells[(row - pos.Y) * TBlockWidth + (col - pos.X)];

				if (cellTile == 0 && blockTile == 1)
				{
					cells[row * CellCount + col] = blockTile;
				}
				else if (cellTile == 1 && blockTile == 0)
				{
					cells[row * CellCount + col] = blockTile;
				}
			}
		}

		return true;
	}

	int width;
	int height;
	int cells[CellCount * CellCount];
};

int main()
{
	srand(0);

	Grid grid;
	grid.Initialize();

	TBlock tBlock;
	tBlock.Initialize();

	COORD startPos	= {2, 2};
	COORD spacing	= {2, 0};
	COORD TBlockDim = {TBlockWidth, TBlockHeight};
	COORD infoStart = {2, startPos.Y + CellCount + spacing.Y};

	GoToPos(infoStart.X, infoStart.Y);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("INFO: ESC to exit. WASD to move codex. ENTER/RETURN to apply codex. R reset grid cells.");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

	GoToPos(0, 0);

	printf("TBlock\n");

	bool isRunning = true;

	while (isRunning)
	{
		if (GetKeyState(VK_ESCAPE) & 0x80000)
		{
			isRunning = false;
		}
		
		if (GetKeyState('D') & 0x8000)
		{
			pos.X++;
		}
		else if (GetKeyState('A') & 0x8000)
		{
			pos.X--;
		}

		if (GetKeyState('W') & 0x8000)
		{
			pos.Y--;
		}
		else if (GetKeyState('S') & 0x8000)
		{
			pos.Y++;
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

		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			grid.flipCell(tBlock);
		}
		else if (GetKeyState('R') & 0x8000)
		{
			grid.Initialize();
		}

		// DRAW CODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

		for (int row = 0;
			row < TBlockHeight;
			row++)
		{
			for (int col = 0;
				col < TBlockWidth;
				col++)
			{
				GoToPos(startPos.X + col, startPos.Y + spacing.Y + row);

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

		GoToPos(7, 0);
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);

		printf("CellBlock\n");

		for (int row = 0;
			row < CellCount;
			row++)
		{
			for (int col = 0;
				col < CellCount;
				col++)
			{
				GoToPos(startPos.X + TBlockDim.X + spacing.X + col, startPos.Y + spacing.Y + row);

				if (col >= pos.X && col < pos.X + TBlockWidth &&
					row >= pos.Y && row < pos.Y + TBlockHeight)
				{
					int blockRow = row - pos.Y;
					int blockCol = col - pos.X;
					int tileID = tBlock.cells[(blockRow)* TBlockWidth + (blockCol)];
					if (tileID >= 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
						printf("%d", tileID);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
						printf("%d", grid.cells[row * CellCount + col]);
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
					printf("%d", grid.cells[row * CellCount + col]);
				}
			}
			printf("\n");
		}

		Sleep(50);
	}
	
	return 0;
}