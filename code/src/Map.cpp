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

void Map::drawMap(sf::RenderWindow* App) {
    int x_position = 0;
    int y_position = 0;
    sf::RectangleShape tile(sf::Vector2f(tile_size,tile_size));
    for (int y = 0; y < map_size_y; y++) 
    {
        for (int x = 0; x < map_size_x; x++) 
        {
            if (map_array[x][y] == LAND)
            {
                tile.setFillColor(sf::Color::Green);
            }
            else
            {
                tile.setFillColor(sf::Color::Blue);
            }
            tile.setPosition(x_position, y_position);
            x_position += tile_size;
            App->draw(tile);
        }
        x_position = 0;
        y_position += tile_size;
    }        
}
