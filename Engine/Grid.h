#pragma once

#include "Graphics.h"

class Grid
{
private:
	class Cell
	{
	public:
		int A = 0;
		int B = 0;
	};

public:
	Grid(const int _w, const int _h, const int _cellSize); //CellSize must be multiple of width AND height!
	~Grid();

	void Draw(Graphics& gfx) const;

private:
	Cell* cells = nullptr;

	const int numCells;
	const int cellSize;
	const int width;
	const int height;
};