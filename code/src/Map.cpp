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

/* void Map::drawMap(sf::RenderWindow* App) {
    int x_position = 0;
    int y_position = 0;
    sf::Texture texture;
    if (!texture.loadFromFile("./data/sprites.png")) {
        std::cout << "ERROR TEXTURE" << std::endl;
    }
    sf::Sprite land_sprite;
    sf::Sprite water_sprite;
    land_sprite.setTexture(texture);
    water_sprite.setTexture(texture);
    land_sprite.setTextureRect(sf::IntRect(106,50,25,25));
    water_sprite.setTextureRect(sf::IntRect(106,25,25,25));

    for (int y = 0; y < map_size_y; y++) 
    {
        for (int x = 0; x < map_size_x; x++) 
        {
            if (map_array[x][y] == LAND)
            {
                land_sprite.setPosition(sf::Vector2f(x_position, y_position));
                App->draw(land_sprite);
            }
            else
            {
                water_sprite.setPosition(sf::Vector2f(x_position, y_position));
                App->draw(water_sprite);
            }
            x_position += tile_size;
        }
        x_position = 0;
        y_position += tile_size;
    }        
} */
