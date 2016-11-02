#ifndef TBLOCK_H
#define TBLOCK_H

#define TBlockWidth 3
#define TBlockHeight 2

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
		for (int row = 0;
			row < height;
			row++)
		{
			for (int col = 0;
				col < width;
				col++)
			{
				cells[row * width + col] = rand() % 2;
			}
		}

		cells[1 * width + 0] = -1;
		cells[1 * width + 2] = -1;
	}

	int width;
	int height;
	int cells[TBlockWidth * TBlockHeight];
};

#endif
