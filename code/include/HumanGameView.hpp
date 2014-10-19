#if !defined HUMAN_GAME_VIEW_HPP
#define HUMAN_GAME_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

#include "GameLogic.hpp"
#include "GameView.hpp"
#include "UIElement.hpp"
#include "UITextInput.hpp"

class HumanGameView : public GameView
{
public:

  HumanGameView(GameLogic* game_logic, sf::RenderWindow* App);

  ~HumanGameView();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);
  
  void readInputs(const sf::Time& delta_t);
  
  void drawUI();

private:

  // Pointer to the game window so this view can draw in it
  sf::RenderWindow* App;
  
  // float which represents the difference between the default resolution and current
  float resRatioX;
  float resRatioY;
  
  // float which represents the aspect ratio Y/X
  float aspectRatio;
  
  // the defaults for the initial window and on which resRatio will be based
  const float DEFAULT_RES_X = 800;
  const float DEFAULT_RES_Y = 600;
  
  // the current resolution
  float currentResX;
  float currentResY;
  
  // a list of UI elements
  std::vector<UIElement*> uiList;
};

#endif
