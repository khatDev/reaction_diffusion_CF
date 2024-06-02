#include "Grid.h"

Grid::Grid(const int _w, const int _h, const int _cellSize)
	:
	height(_h / _cellSize),
	width(_w / _cellSize),
	cellSize(_cellSize),
	numCells((_h / _cellSize) * (_w / _cellSize))
{	
	cells = new Cell[numCells];
	for (int i = 0; i < numCells; i++)
	{
		cells[i].A = 1;
		cells[i].B = 0;
	}
}

Grid::~Grid()
{
	delete[] cells;
	cells = nullptr;
}

void Grid::Draw(Graphics& gfx) const
{
	for (int i = 0; i < numCells; i++)
	{
		int sX = (i % width) * cellSize;
		int sY = (i / width) * cellSize;

		Color c;
		if (cells[i].A > cells[i].B)
		{
			c = Colors::White;
		}
		else
		{
			c = Colors::Black;
		}

		for (int y = 0; y < cellSize; y++)
		{
			for (int x = 0; x < cellSize; x++)
			{
				gfx.PutPixel(sX + x, sY + y, c);
			}
		}
	}
}
