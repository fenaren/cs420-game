#if !defined SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Sound{
public:
  Sound();
  ~Sound();
  
  void playTStart();
  void playTSuccess();
  void playTFail();
  void playTheme();
  void pauseTheme();
  void stopTheme();
  
  
private:
  sf::Music tStart, tFail, tSuccess, gameFail, gameWin;
  sf::Sound theme;
  sf::SoundBuffer buffer;
};



#endif