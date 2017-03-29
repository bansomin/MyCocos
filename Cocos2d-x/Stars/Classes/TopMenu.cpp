//
//  TopMenu.cpp
//  Stars
//
//  Created by HAO on 15-7-19.
//
//

#include "TopMenu.h"
#include "GameData.h"

bool TopMenu::init(){
    
    if (!Node::init()) {
        
        return false;
    }
    
    Size winSize     = Director::getInstance()->getWinSize();
    
//关卡信息标签
    auto levelLabel = Label::createWithSystemFont("关数", "Zapfino", 35);
    levelLabel->setPosition(Vec2(50, winSize.height-50));
    levelLabel->setColor(Color3B::YELLOW);
    this->addChild(levelLabel);
    
//关卡信息内容标签
    _levelContent = Label::createWithSystemFont("", "Zapfino", 23);
    _levelContent->setPosition(Vec2(levelLabel->getPosition() + Vec2(70, 0)));
    this->addChild(_levelContent);
    
//目标分数标签
    auto targetScoreLabel = Label::createWithSystemFont("目标", "Zapfino", 35);
    targetScoreLabel->setPosition(Vec2(levelLabel->getPosition() + Vec2(0, -60)));
    targetScoreLabel->setColor(Color3B::YELLOW);
    this->addChild(targetScoreLabel);
    
//目标分数内容标签
    _targetScoreContent = Label::createWithSystemFont("", "Zapfino", 23);
    _targetScoreContent->setPosition(Vec2(targetScoreLabel->getPosition() + Vec2(80, 0)));
    this->addChild(_targetScoreContent);
    
//当前得分标签
    auto curScoreLabel = Label::createWithSystemFont("得分", "Zapfino", 35);
    curScoreLabel->setPosition(levelLabel->getPosition() + Vec2(250, 0));
    curScoreLabel->setColor(Color3B::YELLOW);
    this->addChild(curScoreLabel);
    
//当前得分内容
    _curScoreContent = Label::createWithSystemFont("", "Zapfino", 23);
    _curScoreContent->setPosition(Vec2(curScoreLabel->getPosition() + Vec2(80, 0)));
    this->addChild(_curScoreContent);
  
//历史最高分标签
    auto historyScoreLabel = Label::createWithSystemFont("最高分", "Zapfino", 35);
    historyScoreLabel->setPosition(Vec2(targetScoreLabel->getPosition() + Vec2(250, 0)));
    historyScoreLabel->setColor(Color3B::YELLOW);
    this->addChild(historyScoreLabel);
    
//历史最高分内容标签
    _highestScoreContent = Label::createWithSystemFont("", "Zapfino", 23);
    _highestScoreContent->setPosition(Vec2(historyScoreLabel->getPosition() + Vec2(80, 0)));
    
    char tempHisScore[64];  //历史最高分
    sprintf(tempHisScore, "%d",GAMEDATA::getInstance()->getHistoryScore());
    _highestScoreContent->setString(tempHisScore);
    
    this->addChild(_highestScoreContent);
    
    this->refresh();
    
    return true;
}


void TopMenu::refresh(){
    
    char tempCurLevel[10];  //关卡
    char tempTarScore[64];  //目标分数
    char tempCurScore[64];  //当前
    char tempHisScore[64];  //历史最高分

//设置关卡
    sprintf(tempCurLevel, "%d",GAMEDATA::getInstance()->getNextLevel());
    _levelContent->setString(tempCurLevel);
    
//目标分数
    sprintf(tempTarScore, "%d",GAMEDATA::getInstance()->getNextScore());
    _targetScoreContent->setString(tempTarScore);
    
//当前分数
    sprintf(tempCurScore, "%d",GAMEDATA::getInstance()->getCurScore());
    _curScoreContent->setString(tempCurScore);
    
//设置历史最高分数
    sprintf(tempHisScore, "%d",GAMEDATA::getInstance()->getHistoryScore());
    //_highestScoreContent->setString(tempHisScore);
}










