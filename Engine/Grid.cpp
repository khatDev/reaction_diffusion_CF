#include "Grid.h"
#include "math.h"

Grid::Grid(const int _w, const int _h, const int _cellSize)
	:
	height(_h / _cellSize),
	width(_w / _cellSize),
	cellSize(_cellSize),
	numCells((_h / _cellSize) * (_w / _cellSize))
{	
	cells = new Cell[numCells];
	oldCells = new Cell[numCells];
	Reset();
}

Grid::~Grid()
{
	delete[] cells;
	cells = nullptr;


	delete[] oldCells;
	oldCells = nullptr;
}

void Grid::Paint(const int _x, const int _y, const int radius, const bool mode)
{
	for (int y = _y - radius - 1; y <= _y + radius - 1; y++)
	{
		for (int x = _x - radius - 1; x <= _x + radius - 1; x++)
		{
			if (sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y)) <= radius && y < height * cellSize && y > 0 && x > 0 && x < width * cellSize)
			{
				int i = ConvertXYToIndice(x, y);

				if (mode)
				{
					cells[i].A = 0;
					cells[i].B = 1;
				}
				else
				{
					cells[i].A = 1;
					cells[i].B = 0;
				}
			}
		}
	}
}

void Grid::Update(float dt)
{
	for (int y = cellSize; y < cellSize * (height - 1); y += cellSize)
	{
		for (int x = cellSize; x < cellSize * (width - 1); x += cellSize)
		{
			int i = ConvertXYToIndice(x, y);

			const float A = cells[i].A;
			const float B = cells[i].B;
			const float reaction = A * B * B;
			oldCells[i].A = A + (diffA * GetLaplaceA(i) - reaction + f * (1 - A)) * dt;
			oldCells[i].B = B + (diffB * GetLaplaceB(i) + reaction - (k + f) * B) * dt;

			
		}
		
	}

	Cell* temp = cells;
	cells = oldCells;
	oldCells = temp;
}

void Grid::Draw(Graphics& gfx) const
{
	for (int i = 0; i < numCells; i++)
	{
		int sX = (i % width) * cellSize;
		int sY = (i / width) * cellSize;

		unsigned char val = (cells[i].A - cells[i].B) * 255;
		val = val > 0 ? val : 0;
		val = val < 255 ? val : 255;
		
		if (val < 0)
		{

		}

		Color c = {val, val, val };
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

void Grid::Reset()
{
	for (int i = 0; i < numCells; i++)
	{
		cells[i].A = 1;
		cells[i].B = 0;
		oldCells[i].A = 1;
		oldCells[i].B = 0;
	}
}

float Grid::GetLaplaceA(const int ind)
{
	float sum = 0.0f;
	sum += cells[ind - 1 - width].A	* diagW;
	sum += cells[ind - width].A		* adjW;
	sum += cells[ind + 1 - width].A	* diagW;
	sum += cells[ind - 1].A			* adjW;
	sum += cells[ind].A				* centerW;
	sum += cells[ind + 1].A			* adjW;
	sum += cells[ind - 1 + width].A * diagW;
	sum += cells[ind + width].A		* adjW;
	sum += cells[ind + 1 + width].A * diagW;

	return sum;
}

float Grid::GetLaplaceB(const int ind)
{
	float sum = 0.0f;
	sum += cells[ind - 1 - width].B * diagW;
	sum += cells[ind - width].B		* adjW;
	sum += cells[ind + 1 - width].B * diagW;
	sum += cells[ind - 1].B			* adjW;
	sum += cells[ind].B				* centerW;
	sum += cells[ind + 1].B			* adjW;
	sum += cells[ind - 1 + width].B * diagW;
	sum += cells[ind + width].B		* adjW;
	sum += cells[ind + 1 + width].B * diagW;

	return sum;
}

int Grid::ConvertXYToIndice(const int _x, const int _y)
{
	int y = ((int)(_y / cellSize));
	int x = ((int)(_x / cellSize));
	return y * width + x;
}
