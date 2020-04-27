#pragma once
#include"Sprites.h"
#include"Textures.h"
#include"Utils.h"
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include"Game.h"

class TileMap
{
	CSprites * sprites = CSprites::GetInstance();
	LPCWSTR filePath_data;
	LPCWSTR filePath_texture;

	int id;
	int num_row_on_tilemap;
	int num_row_on_texture, num_col_on_textture;
	int tileset_width, tileset_height;
	vector<vector<LPSPRITE>> tilemap;

public:
	TileMap(int ID, LPCWSTR pathFileTexture, LPCWSTR pathFileData, int num_row_read_on_texture, int num_col_read_on_textture, int num_row_on_tilemap, int tileset_width = 32, int tileset_height = 32);
	~TileMap();

	void Load();
	void LoadMap();
	void Draw();
};
