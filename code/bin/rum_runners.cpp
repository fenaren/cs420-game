#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "GameLogic.hpp"
#include "HumanGameView.hpp"
#include "Map.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"
#include "EventInterface.hpp"

// Cap on maximum frame rate
#define MAX_FRAME_RATE 60

// Toggles frame rate display.  true = display, false = don't display
#define FRAME_RATE_DISPLAY false

// # of frames to average over to calculate the frame rate
#define FRAME_RATE_AVGFRAMES 5



  // How fast is game time relative to real time?
  // 1 = game time is real time
  // (0 1) = game time is slower than real time
  // 0 = game time is paused
  // >1 = game time is faster than real time
  // <0 = game time runs in reverse
double GAME_TIME_FACTOR = 1.0;


//Pauses game during TransactionStartEvent
void PauseStartHandler(const EventInterface& event)
{
    GAME_TIME_FACTOR = 0.0;
}

//Un-pauses game after TransactionFailEvent or TransactionSuccessEvent
void TransactionEndHandler(const EventInterface& event)
{
    GAME_TIME_FACTOR = 1.0;
}


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Rum Runners");
    
    /*Map game_map = Map();
    if(!game_map.createMap("first_map.txt"))
    {
        std::cout << "Map failed to create" << std::endl;
    }
    else
    {
        game_map.drawMap(&App);
    }
    App.display();*/


  // Clocks for managing frame time.  'processing_clock' is used to determine
  // how long the processing required by the game takes, 'update_clock' is used
  // to determine how much time actually passes between successive game updates
  sf::Clock processing_clock;
  sf::Clock update_clock;

  // Update time for the first frame doesn't make sense because the update clock
  // is running before the game ever gets into the game loop, and because there
  // isn't a previous update from which to reference.  Instead of allowing
  // inconsistent behavior the update time for the first frame is forced to 0 to
  // force consistent first frame update behavior.  The rest of the frames
  // obviously don't do this.
  bool first_frame = true;


  // Initialize all the framerate indicator stuff

  // Initialize the font
  sf::Font framerate_font;
  if (!framerate_font.loadFromFile("Arial.ttf"))
  {
    std::cerr << "Couldn't load framerate indicator font\n";
    return 0;
  }

  // Initialize the framerate indicator
  sf::Text framerate_indicator;
  framerate_indicator.setFont(framerate_font);
  framerate_indicator.setPosition(0, 0);
  framerate_indicator.setCharacterSize(15);
  framerate_indicator.setColor(sf::Color::White);

  // Will be used to store the last FRAME_RATE_AVGFRAMES frame times
  std::vector<sf::Time> frametimes;


  // Create and initialize the game logic
  GameLogic game_logic;
  if (!game_logic.initialize())
  {
    // Do something smarter than this
    return 0;
  }


  // Create and initialize the game view
  HumanGameView human_game_view(&game_logic, &App);
  if (!human_game_view.initialize())
  {
    // Do something smarter than this
    return 0;
  }


  // start main loop
  while(App.isOpen())
  {
    // We're at the beginning of the frame, so we want to start tracking how
    // long we take to do game processing now.
    processing_clock.restart();


    /*// process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }*/


    // How much time has passed since the last update?
    sf::Time update_time = update_clock.restart();
    if (first_frame)
    {
      // Force a no-op update on the first frame
      update_time = sf::seconds(0.0);
    }

    // Pull event_manager from GameLogic
    EventManager* event_manager;
    event_manager = game_logic.getEventManager();
    // Add delegates bound to each event type
    // PauseStartHandler: pauses game at TransactionStartEvent
     event_manager->addDelegate(
    EventDelegate(PauseStartHandler),
    TransactionStartEvent::event_type);
     // UnpauseFailHandler: unpauses game after TransactionFailEvent
     event_manager->addDelegate(
    EventDelegate(TransactionEndHandler),
    TransactionFailEvent::event_type);
     // UnpauseSuccessHandler: unpauses game after TransactionSuccessEvent
     event_manager->addDelegate(
    EventDelegate(TransactionEndHandler),
    TransactionSuccessEvent::event_type);
     
    // UPDATE GAME VIEWS
    human_game_view.update(update_time);

    // UPDATE GAME LOGIC
    game_logic.update(update_time);
 
    // Note how long since the last update for the framerate indicator
    frametimes.push_back(update_time);
    if (frametimes.size() == FRAME_RATE_AVGFRAMES)
    {
      // Average all the frame times
      double frametime_average = 0;
      for (std::vector<sf::Time>::iterator i = frametimes.begin();
	   i != frametimes.end();
	   i++)
      {
	frametime_average += i->asSeconds();
      }
      frametime_average /= FRAME_RATE_AVGFRAMES;

      // Convert the average framerate to a text string
      std::ostringstream fr_to_text;
      fr_to_text << 1.0 / frametime_average;
      framerate_indicator.setString(fr_to_text.str());

      // Clear all the frame times
      frametimes.clear();
    }


    // clear screen and fill with blue
    //App.clear(sf::Color::Blue);

    // Draw the framerate indicator
    if (FRAME_RATE_DISPLAY)
    {
      //App.draw(framerate_indicator);
    }

    // display
    //App.display();


    // How much time did this frame's processing take?
    sf::Time processing_time = processing_clock.getElapsedTime();

    // Cap the frame rate at MAX_FRAME_RATE
    if (processing_time.asSeconds() < 1.0 / MAX_FRAME_RATE)
    {
      // Construct a time representing how much time we need to sleep
      sf::Time sleep_time =
	sf::seconds((1.0 / MAX_FRAME_RATE) - processing_time.asSeconds());

      sf::sleep(sleep_time);
    }


    // It's about to not be the first frame anymore so make that note
    first_frame = false;
  }

  // Done.
  return 0;
}

