#include "MapGenerator.h"

void MapGenerator::GenerateMap() {

    std::cout << seed << std::endl;
    for (auto y = 0; y < MAPWIDTH; ++y) {
        for (auto x = 0; x < MAPHEIGHT; ++x) {

            level[x][y] = (
                db::perlin(float(x) / 64.0f, float(y) / 64.0f, seed * 0.25f) * 1.0f +
                db::perlin(float(x) / 32.0f, float(y) / 32.0f, seed * 0.75f) * 0.5f
                ) / 0.2f; 
        }
    }
}



void MapGenerator::NormalizeMap() {
    for (auto y = 0; y < MAPWIDTH; ++y) {
        for (auto x = 0; x < MAPHEIGHT; ++x) {
            if (level[x][y] <= 0) level[x][y] *= -1;

            if (level[x][y] >= 2) level[x][y] = 2;
            level[x][y] = round(level[x][y]);
            level2[count] = level[x][y];   
            count++;
        }   
    }
    count = 0;
}

void MapGenerator::PrintMap() {
    for (auto y = 0; y < MAPWIDTH; ++y) {
        for (auto x = 0; x < MAPHEIGHT; ++x) {
            
            std::cout << level2[count];
            count++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << count << std::endl;
    count = 0;
}

void MapGenerator::SetEntryExitPoints() {
    sf::Clock clock;
    srand(time(NULL));
    entry_x = (rand() % MAPWIDTH - 1);
    exit_x = (rand() % MAPWIDTH - 1);

    std::cout << "entry point = [" << entry_x << "][0]" << std::endl;
    std::cout << "exit point = [" << exit_x << "][" << MAPHEIGHT <<"]" << std::endl;

    level[exit_x][0] = 4;
    level[entry_x][MAPHEIGHT-1] = 3;

    level2[exit_x] = 4;
    level2[MAPHEIGHT * (MAPWIDTH - 1) + entry_x] = 3;
}

// Method for checking boundaries
bool MapGenerator::IsSafe(int i, int j)
{
    if (i >= 0 && i < MAPWIDTH && j >= 0 && j < MAPHEIGHT)
        return true;
    return false;
}

// Returns true if there is a
// path from a source (a
// cell with value 3) to a
// destination (a cell with
// value 4)
bool MapGenerator::IsaPath(int i, int j, bool visited[][MAPHEIGHT])
{
    // Checking the boundaries, obstacle and
    // whether the cell is unvisited
    //if (IsSafe(i, j) && level[i][j] != 2 && !visited[i][j]) {
    if ((i >= 0 && i < MAPWIDTH && j >= 0 && j < MAPHEIGHT) && level[i][j] != 2 && !visited[i][j]) {
        // Make the cell visited
        visited[i][j] = true;

        // if the cell is the required destination then return true
        if (level[i][j] == 4)
            return true;

        // traverse up
        bool left = IsaPath(i - 1, j, visited);

        // if path is found in up direction return true
        if (left) {
            //std::cout << "left" << std::endl;
            return true;
        }
            

        // traverse left
        bool up = IsaPath( i, j - 1, visited);

        // if path is found in left direction return true
        if (up) {
            //std::cout << "up" << std::endl;
            return true;
        }
            

        // traverse down
        bool right = IsaPath(i + 1, j, visited);

        // if path is found in down direction return true
        if (right) {
            //std::cout << "right" << std::endl;
            return true;
        }
            

        // traverse right
        bool down = IsaPath(i, j + 1, visited);

        // if path is found in right direction return true
        if (down)
        {
            //std::cout << "down" << std::endl;
            return true;
        }
            
    }

    // no path has been found
    return false;
}

// Method for finding and printing
// whether the path exists or not
bool MapGenerator::IsPath()
{

    // Defining visited array to keep
    // track of already visited indexes
    bool visited[MAPWIDTH][MAPHEIGHT];
    memset(visited, 0, sizeof(visited));

    // Flag to indicate whether the path exists or not
    bool flag = false;
    for (int i = 0; i < MAPWIDTH; i++) {
        for (int j = 0; j < MAPHEIGHT; j++) {
            // if matrix[i][j] is source and it is not visited
            if (level[i][j] == 3 && !visited[i][j])

                // Starting from i, j and then finding the path
                if (IsaPath(i, j, visited)) {

                    // if path exists
                    flag = true;
                    break;
                }
        }
    }
    /*for (auto y = 0; y < MAPWIDTH; ++y) {
        for (auto x = 0; x < MAPHEIGHT; ++x) {

            std::cout << visited[x][y];
        }
        std::cout << std::endl;
    }*/
    return flag;
}

MapGenerator::MapGenerator() {
}

int *MapGenerator::GetLevel2() {
    return this->level2;
}

int MapGenerator::GetSeed()
{
    return this->seed;
}

void MapGenerator::GenerateSeed()
{
    sf::Clock clock;

    srand(time(NULL));

    seed = (rand() % 10000000 + 1);
}
