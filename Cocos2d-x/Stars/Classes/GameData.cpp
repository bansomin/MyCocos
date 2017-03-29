//
//  GameData.cpp
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#include "GameData.h"

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){

    this->init();
}

void GAMEDATA::init(){

    setCurLevel(0);
    setCurScore(0);
    
    setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore", 0));
    
    printf("%dGAMEDATA\nGAMEDATA\nGAMEDATA\nGAMEDATA\nGAMEDATA\nGAMEDATA\n%d", _cur_level,_history_score);
}


GAMEDATA* GAMEDATA::getInstance(){

    if (_instance == 0) {
        
        _instance = new GAMEDATA();
    }
    
    return _instance;
}



void GAMEDATA::setCurLevel(int level){

    if (level < 0) {
        
        return;
    }
    _cur_level  = level;
    _next_level = level + 1;
    _next_score = getScoreByLevel(_next_level);
}
int GAMEDATA::getCurLevel(){
    
    return _cur_level;
}



int GAMEDATA::getNextLevel(){

    return _next_level;
}



void GAMEDATA::setHistoryScore(int score){
    
    _history_score = score;
}
int GAMEDATA::getHistoryScore(){
    
    return _history_score;
}



void GAMEDATA::setCurScore(int score){
    
    _cur_score = score;
}
int GAMEDATA::getCurScore(){
    
    return _cur_score;
}



int GAMEDATA::getNextScore(){
    
    return _next_score;
}



int GAMEDATA::getScoreByLevel(int level){

    int score = 0;
    
    printf("GameData_getScoreByLevel() = %d\n",level);
    
    if (level == 1) {
        score = 1000;
    }
    else if (level == 2){
        score = 2500;
    }
    else if (level == 3){
        score = 4100;
    }
    else if (level == 4){
        score = 5800;
    }
    else if (level == 5){
        score = 7600;
    }
    else if (level == 6){
        score = 9500;
    }
    else if (level == 7){
        score = 11500;
    }
    else if (level == 8){
        score = 13600;
    }
    else if (level == 9){
        score = 15800;
    }
    else{
        score = 15800 + 100*(level - 10);
    }
    return score;
}



int GAMEDATA::getJiangli(int size){
    
    static const int jiangli[10][2] = {
        {0, 2000},
        {1, 1980},
        {2, 1920},
        {3, 1820},
        {4, 1680},
        {5, 1500},
        {6, 1280},
        {7, 1020},
        {8, 720},
        {9, 380}
    };
    
    if (size > 9|| size < 0) {
        return 0;
    }
    return jiangli[size][1];
}



void GAMEDATA::saveHighestScore(){

    UserDefault::getInstance()->setIntegerForKey("highestScore", getHistoryScore());
}

//保存每一关的分数
void GAMEDATA::saveCurLevelScore(int level, float score){
    
    char tempScore[20];
    
    sprintf(tempScore, "cur_level_score%d",level);
    UserDefault::getInstance()->setFloatForKey(tempScore, score);
    printf("GameData_saveCurScore()＝ %f\n", score);
}





