#pragma once

#include "Graphics.h"

class Grid
{
private:
	class Cell
	{
	public:
		float A = 0.0f;
		float B = 0.0f;
	};

public:
	Grid(const int _w, const int _h, const int _cellSize); //CellSize must be multiple of width AND height!
	~Grid();


	void Reset();
	void Paint(const int x, const int y, const int radius, const bool mode = true);
	void Update(float dt = 1.0f);
	void Draw(Graphics& gfx) const;

private:

	float GetLaplaceA(const int ind);
	float GetLaplaceB(const int ind);

	int ConvertXYToIndice(const int x, const int y);

private:
	Cell* cells = nullptr;
	Cell* oldCells = nullptr;

	//-----Grid Params-----
	const int numCells;
	const int cellSize; 
	const int width;
	const int height;

	//-----Sim Params-----
	const float diffA = 1.0f;
	const float diffB = 0.5f;
	const float f = .02643f;
	const float k = .06072f;

	const float diagW = 0.05f;
	const float adjW = 0.2f;
	const float centerW = -1.0f;
};