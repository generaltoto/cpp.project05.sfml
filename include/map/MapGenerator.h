#pragma once
#include "include/map/db_perlin.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

const int MAPHEIGHT = 256;
const int MAPWIDTH = 256;

#define DB_PERLIN_IMPL

class MapGenerator
{
private:
	int entry_x;
	int exit_x;
	int count;
	int seed;
	float level[MAPHEIGHT][MAPWIDTH] = {};
	int level2[MAPHEIGHT * MAPWIDTH] = {};

	/// Set a number acording to perlin noise to a 2D array
	void GenerateMap();

	/// Set a random number as entry_x and exit_x 
	void SetEntryExitPoints();

	/// Convert from float to int 
	void NormalizeMap();

	/// Convert from a 2D array to a 1D array 
	void SetMapToLevel2();

	/// Change mountain sprites accordingly to their environment 
	void SetMountains();

	/// Print the 1D array on the consol
	void PrintMap();

	/// Print the 2D array on the consol
	void PrintMap2();

	/// Method for checking boundaries
	bool IsPath();

	/// Returns true if there is a path from a source (a cell with value 3) to a destination (a cell with value 4)
	bool IsSafe(int, int);

	/// Method for finding and printing whether the path between entry_point and exit_point exists or not
	bool IsaPath(int i, int j, bool visited[][MAPWIDTH]);

public:
	MapGenerator(int winWidth, int winHeight);
	
	/// Get the 1D array
	int *GetLevel2();

	/// Get the 2D array
	float *GetLevel();

	/// Generate the map's seed
	void GenerateSeed();

	/// Get entry_x
	int GetEntry();

	/// Get the value of target cell in level
	int GetCellValue(int x, int y);

};

