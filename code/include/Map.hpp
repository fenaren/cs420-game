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

    enum Terrain
    {
      WATER = 0,
      LAND  = 1
    };
        
private:    

    const int map_size_x = 32;
   
    const int map_size_y = 24;
    
    int map_array[32][24];

    int tile_size = 25;
};

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
