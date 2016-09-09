/*
Name: George Wulfers
Class: Adv Prog Concepts
*/

// TODO(George): Separate things into separate files.
// TOOD(George): Is this the best way to do this?

#include <iostream>
#include <random>
#include <Windows.h>

#define CellCount 6
#define TBlockWidth 3
#define TBlockHeight 2

COORD pos = { 0, 0 };

void GoToPos(int X, int Y)
{
	COORD pos = {(short)X, (short)Y};
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
		int flipCount = 0;

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
					flipCount++;
					cells[row * CellCount + col] = blockTile;
				}
				else if (cellTile == 1 && blockTile == 0)
				{
					flipCount++;
					cells[row * CellCount + col] = blockTile;
				}
			}
		}

		return (flipCount != 0);
	}

	int width;
	int height;
	int cells[CellCount * CellCount];
};

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

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
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

bool isKeyDown(unsigned int vkCode)
{
	return (bool)(GetKeyState(vkCode) & 0x80000);
}

int main()
{
	srand(0);

	Grid grid;
	Grid oldGrid;

	grid.Initialize();

	copyGrid(oldGrid, grid);

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

	GoToPos(7, 0);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("CellBlock\n");

	GoToPos(17, 0);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);

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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

		GoToPos(0, 1);
		printf("Pos: (%d, %d)", pos.X, pos.Y);

		drawCodex(COORD{ startPos.X, startPos.Y }, tBlock);
		drawGrid(COORD{ startPos.X + TBlockDim.X + startPos.X, startPos.Y}, grid, tBlock);
		drawOldGrid(COORD{ startPos.X + TBlockDim.X + startPos.X + (short)grid.width + startPos.X, startPos.Y}, oldGrid);

		Sleep(100);
	}
	
	return 0;
}