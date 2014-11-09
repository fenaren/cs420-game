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
	int x = 0;
    	int y = 0;
    	std::ifstream map_file (filename);
    	if (map_file.is_open()) {
		while (std::getline(map_file,line,',')) {
			if(x == 32) {
				x = 0;
				y+= 1;
			}
			map_array[x][y] = atoi(line.c_str());
            		x++;
        	}
        	return true;
    	}
    	else {
        	return false;
    	}
    	map_file.close();
}
