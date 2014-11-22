#if !defined MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

class Map
{
public:
    
    Map();
    
    ~Map();
    
    virtual bool initialize();
    
    bool createMap(std::string filename);
    
    int* getMap();
    
    int getTerrain(int x, int y) const;

    int get_map_size_x();

    int get_map_size_y();

    int get_tile_size();
	
	// checks if this position is a valid spot
	// for an actor to be at
	bool isValidPosition(sf::Vector2i pos);

private:    

    const int map_size_x = 32;
   
    const int map_size_y = 24;
    
    int map_array[32][24];

    int tile_size = 25;
};

inline bool Map::isValidPosition(sf::Vector2i pos) {
	if (getTerrain(pos.x, pos.y) != 19 &&
      pos.x < get_map_size_x() &&
      pos.y < get_map_size_y() &&
	  pos.x >= 0 && pos.y >= 0) 
		  return true;
	else
		return false;
}

inline int* Map::getMap()
{
    return *map_array;
}

inline int Map::getTerrain(int x, int y) const
{
    return map_array[x][y];
}

inline int Map::get_map_size_x()
{
    return map_size_x;
}

inline int Map::get_map_size_y()
{
    return map_size_y;
}

inline int Map::get_tile_size()
{
    return tile_size;
}

#endif
