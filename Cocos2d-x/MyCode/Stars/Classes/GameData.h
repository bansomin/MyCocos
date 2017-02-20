//
//  GameData.h
//  Stars
//
//  Created by HAO on 15-7-29.
//
//

#ifndef Stars_GameData_h
#define Stars_GameData_h

#include "cocos2d.h"
using namespace cocos2d;

class GAMEDATA{

private:
    GAMEDATA();
    void init();
    
public:
    static GAMEDATA* getInstance();
    
private:
    static GAMEDATA* _instance;
    
private:
    int _cur_score;
    int _next_score;
    int _cur_level;
    int _next_level;
    int _history_score;

    friend class MenuLayer;

public:    
    void setCurLevel(int level);
    int getCurLevel();
    
    int getNextLevel();
    
    void setHistoryScore(int score);
    int getHistoryScore();
    
    void setCurScore(int score);
    int getCurScore();
    
    int getNextScore();
    
    int getScoreByLevel(int level);
    int getJiangli(int size);
    
    void saveHighestScore();
    void saveCurLevelScore(int level, float score);
    
};

#endif













