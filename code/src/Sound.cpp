#include <iostream>
#include "Sound.hpp"


Sound::Sound(GameLogic* game_logic):
  game_logic(game_logic)
{
  
  if(!buffer.loadFromFile("./data/rumrunnerstheme.wav"))
    std::cout << "Theme can't be found\n" << std::endl;
   
  if(!tStart.openFromFile("./data/coin.wav"))
    std::cout << "Transaction Start sound can't be found\n" << std::endl;
  
  
  if(!tFail.openFromFile("./data/error.wav"))
    std::cout << "Transaction Fail sound can't be found\n" << std::endl;
  
  
  if(!tSuccess.openFromFile("./data/success.wav"))
    std::cout << "Transaction Success sound can't be found\n" << std::endl;
  
  if(!gameWin.openFromFile("./data/tada.wav"))
    std::cout << "Game Win sound can't be found\n" << std::endl;
  
  theme.setBuffer(buffer);
  theme.setLoop(true);
}

Sound::~Sound(){

}

bool Sound::initialize(){
   getGameLogic()->getEventManager()->addDelegate(
      EventDelegate(std::bind(&Sound::transactionFailSoundHandler,
			      this,
			      std::placeholders::_1)),
      TransactionFailEvent::event_type);
  
    getGameLogic()->getEventManager()->addDelegate(
      EventDelegate(std::bind(&Sound::transactionSuccessSoundHandler,
			      this,
			      std::placeholders::_1)),
    TransactionSuccessEvent::event_type);
    
    getGameLogic()->getEventManager()->addDelegate(
      EventDelegate(std::bind(&Sound::transactionStartSoundHandler,
			      this,
			      std::placeholders::_1)),
      TransactionStartEvent::event_type);
    
    getGameLogic()->getEventManager()->addDelegate(
      EventDelegate(std::bind(&Sound::gameWonSoundHandler,
			      this,
			      std::placeholders::_1)),
      GameWonEvent::event_type);
          
    return true;
}



void Sound::playTStart(){
  tStart.play(); 
}

void Sound::playTFail(){
  tFail.play(); 
}

void Sound::playTSuccess(){
  tSuccess.play(); 
}

void Sound::playTheme(){
  
  theme.play();  
}

void Sound::playGameWin(){
  gameWin.play(); 
}

void Sound::pauseTheme(){
  theme.pause();
}

void Sound::stopTheme(){
  theme.stop();  
}

//Plays sound for Transaction Start
void Sound::transactionStartSoundHandler(const EventInterface& event) {
  this->playTStart();
}

//Plays sound for Transaction Fail
void Sound::transactionFailSoundHandler(const EventInterface& event) {
  this->playTFail();
}

//Plays sound for Transaction Success
void Sound::transactionSuccessSoundHandler(const EventInterface& event) {
  this->playTSuccess();
}

//Plays sound for Game Won
void Sound::gameWonSoundHandler(const EventInterface& event) {
  this->playGameWin();
}