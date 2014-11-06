#if !defined HUMAN_GAME_VIEW_HPP
#define HUMAN_GAME_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

#include "GameLogic.hpp"
#include "GameView.hpp"
#include "UIElement.hpp"
#include "UITextInput.hpp"
#include "Map.hpp"
#include "ShipMoveCmdEvent.hpp"

class HumanGameView : public GameView
{
public:

  HumanGameView(GameLogic* game_logic, sf::RenderWindow* App);

  ~HumanGameView();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);
  
  void readInputs(const sf::Time& delta_t);
  
  void drawMap();
  
  void drawActors();
  
  void drawUI();

private:

  // Calculates where the top-left corner of the map is in window coordinates
  // (map_tl_wcoords) and what the map tile size is in pixels (map_tile_size).
  void calculateMapWindowData();

  // Takes a coordinate pair (map_coords) denoting a location on the game map
  // and returns a coordinate pair (window_coords) denoting where that location
  // is in the window, given current map and window sizes.
  void mapToWindow(const sf::Vector2u& map_coords, sf::Vector2u& window_coords); 

  // Location of the top-left corner of the map in window coordinates
  sf::Vector2u map_tl_wcoords;

  // Side length of map tiles in pixels
  unsigned int map_tile_size;

  // boolean that represents if a menu is asking for input
  // so gameview knows whether to read for text input
  // or game commands
  bool menuOpen = false;

  // Pointer to the game window so this view can draw in it
  sf::RenderWindow* App;
  
  // float which represents the difference between the default resolution and current
  sf::Vector2f resRatio;
  
  // float which represents the aspect ratio Y/X
  float aspectRatio;
  
  // the defaults for the initial window and on which resRatio will be based
  const sf::Vector2u DEFAULT_RES = sf::Vector2u(800, 600);
  
  // the current resolution
  sf::Vector2u currentRes;
  
  // a list of UI elements
  std::vector<UIElement*> uiList;
  
  // temporary map to draw from
  Map tempMap;

  // texture to draw sprites from
  sf::Texture texture;
  
  // the dialogue box
  UITextInput *test;
};

#endif
