//
//  Audio.h
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#ifndef __Stars__Audio__
#define __Stars__Audio__

#include <iostream>

class Audio{

public:
    static Audio* getInstance();
    
private:
    static Audio* _my_instance;
    
public:
    void prepare();
    void playBGM();
    
    void pauseMusic();
    void pauseSound();
    void resumeMusic();
    void resumeSound();
    
    void playEffects();
    void playReadyGo();
    void playCombo(int size);
    void playFireWorks(int index);
    
    void setValueMusic(float value);
    void setValueSound(float value);
};
#endif /* defined(__Stars__Audio__) */







