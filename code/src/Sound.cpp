#include <iostream>
#include "Sound.hpp"

Sound::Sound(){
  if(!buffer.loadFromFile("rumrunnerstheme.wav"))
    std::cout << "Theme can't be found\n" << std::endl;
  
  if(!tStart.openFromFile("coin.wav"))
    std::cout << "Transaction Start sound can't be found\n" << std::endl;
  
  
  if(!tFail.openFromFile("error.wav"))
    std::cout << "Transaction Fail sound can't be found\n" << std::endl;
  
  
  if(!tSuccess.openFromFile("success.wav"))
    std::cout << "Transaction Success sound can't be found\n" << std::endl;
  
  if(!gameWin.openFromFile("tada.wav"))
    std::cout << "Game Win sound can't be found\n" << std::endl;
  
  theme.setBuffer(buffer);
  theme.setLoop(true);
}

Sound::~Sound(){

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

void Sound::pauseTheme(){
  theme.pause();
}

void Sound::stopTheme(){
  theme.stop();  
}