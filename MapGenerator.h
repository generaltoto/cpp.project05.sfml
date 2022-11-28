#pragma once
#include "db_perlin.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#define MAPHEIGHT 64
#define MAPWIDTH 64


class MapGenerator
{
private:
	int entry_x = 0;
	int exit_x = 0;
	int count = 0;
	int seed = 0;
	float level[MAPHEIGHT][MAPWIDTH] = {};
	int level2[MAPHEIGHT * MAPWIDTH] = {};

public:
	void GenerateMap();
	void SetEntryExitPoints();
	void NormalizeMap();
	void SetMapToLevel2();
	void SetMountains();

	void PrintMap();
	void PrintMap2();
	bool IsPath();
	bool IsSafe(int, int);
	bool IsaPath(int i, int j, bool visited[][MAPWIDTH]);

	MapGenerator();
	
	int *GetLevel2();
	int GetSeed();
	void GenerateSeed();
	
};

