#include <SFML/Audio/Music.hpp>

class Sound : public sf::Music{
public:
  Sound();
  ~Sound();
  void playSound();
};