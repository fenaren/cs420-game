#if !defined SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "EventManager.hpp"
#include "GameLogic.hpp"
#include "GameWonEvent.hpp"
#include "GameLostEvent.hpp"
#include "TransactionCheckEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"

class Sound{
public:
  Sound(GameLogic* game_logic);
  ~Sound();
  
  bool initialize();
  
  void playTStart();
  void playTSuccess();
  void playTFail();
  void playTheme();
  void playGameWin();
  void playGameFail();
  void pauseTheme();
  void stopTheme();
  
  //Sound handlers
  void transactionFailSoundHandler(const EventInterface& event);
  void transactionStartSoundHandler(const EventInterface& event);
  void transactionSuccessSoundHandler(const EventInterface& event);
  void gameWonSoundHandler(const EventInterface& event);
  void gameLostSoundHandler(const EventInterface& event);
  
  EventManager* getEventManager();
  
  GameLogic* getGameLogic();
  
private:
  sf::Music tStart, tFail, tSuccess, gameFail, gameWin;
  sf::Sound theme;
  sf::SoundBuffer buffer;
  
  EventManager event_manager;
  GameLogic* game_logic;
};

inline EventManager* Sound::getEventManager()
{
  return &event_manager;
}

inline GameLogic* Sound::getGameLogic()
{
  return game_logic;
}

#endif
