#ifndef GRID_H
#define GRID_H

#include "TBlock.h"

#define CellCount 6

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

#endif
