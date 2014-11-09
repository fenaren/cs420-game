#if !defined HUMAN_GAME_VIEW_HPP
#define HUMAN_GAME_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <map>
#include <vector>

#include "ActorId.hpp"
#include "GameLogic.hpp"
#include "GameView.hpp"
#include "UIElement.hpp"
#include "UITextInput.hpp"
#include "UIPortData.hpp"
#include "Map.hpp"
#include "ShipMoveCmdEvent.hpp"
#include "TransactionCheckEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"

class HumanGameView : public GameView
{
public:

  HumanGameView(GameLogic* game_logic, sf::RenderWindow* App);

  ~HumanGameView();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);
  
  void readInputs(const sf::Time& delta_t);

  void updateUI();
  
  void drawMap();
  
  void drawActors();
  
  void drawUI();
  
  void transactionFailEventHandler(const EventInterface& event);
  void transactionSuccessEventHandler(const EventInterface& event);
  void transactionStartEventHandler(const EventInterface& event);

  // Takes a coordinate pair (map_coords) denoting a location on the game map
  // and returns a coordinate pair (window_coords) denoting where the top-left
  // point of that map location is in the window, given current map and window
  // sizes.  Depends on the results of the last run of
  // calculateMapWindowData().  Returns true if the transformation was
  // successful, false otherwise.
  bool mapToWindow(const sf::Vector2f& map_coords, sf::Vector2f& window_coords); 

  // Takes a coordinate pair (window_coords) denoting a location in the window
  // and returns a coordinate pair (map_coords) denoting where that location
  // is on the map, given current map and window sizes.  Depends on the results
  // of the last run of calculateMapWindowData().  Returns true if the
  // transformation was successful, false otherwise.
  bool windowToMap(const sf::Vector2f& window_coords, sf::Vector2f& map_coords);

private:

  // Calculates where the top-left corner of the map is in window coordinates
  // (map_tl_wcoords) and what the map tile size is in pixels (map_tile_size).
  void calculateMapWindowData();

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

  // last known ship position, for animation
  unsigned int lastShipX;
  unsigned int lastShipY;
  
  // position in sprite sheet for ship animation
  unsigned int shipSpriteY;
  
  // the dialogue box
  UITextInput *test;
  
  // temp ints for storing transaction event data
  ActorId tc_shipid;
  ActorId tc_portid;
  int tc_shipgold;
  int tc_shiprum;
  int tc_portrum;

  // UI data on the ports.  Right now display of the port UI data doesn't
  // support changes in the number of ports at runtime, which is okay because
  // neither do some other systems in the game
  std::map<ActorId, UIPortData*> port_ui_data;
};

#endif
