#include "Grid.h"

Grid::Grid(int cell_width, int cell_height)
{
	this->cell_width = cell_width;
	this->cell_height = cell_height;
}

void Grid::Resize(int map_width, int map_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	int totalCol = this->map_width / this->cell_width;
	int totalRow = this->map_height / this->cell_height;

	allcells.resize(totalRow);
	for (int i = 0; i < totalRow; i++)
		allcells[i].resize(totalCol);

	ClearGrid(totalRow, totalCol);
}

void Grid::ClearGrid(int nums_row, int nums_col)
{
	for (int i = 0; i < nums_row; i++)
		for (int j = 0; j < nums_col; j++)
			allcells[i][j].clear();
}

void Grid::PushGrid(vector<LPGAMEOBJECT> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		int row = (int)(list[i]->y / cell_height);
		int col = (int)(list[i]->x / cell_width);

		if (!list[i]->isDead)
 			allcells[row][col].push_back(list[i]);
	}
}

void Grid::ResetGrid(vector<LPGAMEOBJECT> list)
{
	ClearGrid((int)this->map_height / cell_height, (int)this->map_width / cell_width);

	PushGrid(list);
}


void Grid::GetGrid(vector<LPGAMEOBJECT>& list)
{
	int firstCol = (int)(CGame::GetInstance()->GetCamPosX() / cell_width);
	int lastCol = ceil((CGame::GetInstance()->GetCamPosX() + SCREEN_WIDTH) / cell_width);
	int totalRow = this->map_height / cell_height;

	for (int i = 0; i < totalRow; i++)
		for (int j = firstCol; j < lastCol; j++)
			for (int k = 0; k < allcells[i][j].size(); k++)
				list.push_back(allcells[i][j][k]);
}

Grid::~Grid()
{
}
