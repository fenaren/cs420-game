#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
}

bool Map::initialize()
{
    return true;
}

bool Map::createMap(std::string filename) {
    std::string line;
    int y = 0;
    std::ifstream map_file (filename);
    if (map_file.is_open())
    {
        while (std::getline (map_file,line) ) 
        {
            for (int x = 0; x < map_size_x; x++) {
                if (line[x] == 'L') {
                    map_array[x][y] = LAND;
                }
                else if (line[x] == 'W') {
                    map_array[x][y] = WATER;
                }
            }
            y++;
        }
        return true;
    }
    else
    {
        return false;
    }
    map_file.close();
}
