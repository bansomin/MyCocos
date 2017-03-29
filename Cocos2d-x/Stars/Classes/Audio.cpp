//
//  Audio.cpp
//  Stars
//
//  Created by HAO on 15-7-18.
//
//
#include "Audio.h"
#include "SimpleAudioEngine.h"

Audio* Audio::_my_instance = nullptr;
Audio* Audio::getInstance(){

    if (_my_instance == nullptr) {
        
        _my_instance = new Audio();
    }
    
    return _my_instance;
}


void Audio::prepare(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgMusic1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgMusic2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgMusic3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgMusic4.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_2.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("combo_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fireworks_1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fireworks_2.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("fireworks_3.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("NextGameRound.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("readygo.wav");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("yinxiao.wav");
}

void Audio::playBGM(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgMusic4.wav", true);
}

void Audio::playEffects(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("yinxiao.wav", false);
}


void Audio::playReadyGo(){

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("readygo.wav", false);
}

void Audio::playCombo(int size){

    if (size < 5)
        return;
    
    if (size >= 10) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_3.wav",false);
    }
    else if (size >= 7){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_2.wav",false);
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("combo_1.wav",false);
    }
}

void Audio::playFireWorks(int index){
    
    if (index == 3) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fireworks_3.wav");
    }
    else if (index == 2){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fireworks_2.wav");
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fireworks_1.wav");
    }
}

void Audio::setValueMusic(float value){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(value);
}

void Audio::setValueSound(float value){

    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(value);
}

void Audio::pauseMusic(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void Audio::pauseSound(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void Audio::resumeMusic(){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void Audio::resumeSound(){
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}


