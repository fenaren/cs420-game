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
    int row = 0;
    std::ifstream map_file (filename);
    if (map_file.is_open())
    {
        while (std::getline (map_file,line) ) 
        {
            for (int col = 0; col < map_cols; col++) {
                if (line[col] == 'L') {
                    map_array[row][col] = LAND;
                }
                else if (line[col] == 'W') {
                    map_array[row][col] = WATER;
                }
            }
            row++;
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
    for (int row = 0; row < map_rows; row++) 
    {
        for (int col = 0; col < map_cols; col++) 
        {
            if (map_array[row][col] == LAND)
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
