//
//  FloatWord.cpp
//  Stars
//
//  Created by HAO on 15-7-18.
//
//
/*
    * 五串字体从右到左的飘入
    * 显示关卡等信息
    * 创建继承自Node的一个类 
 
    * create和init是连在一起的,调用create的时候必然会调用init
 
*/

#include "FloatWord.h"


FloatWord* FloatWord::create(const std::string& word, const int fontSize, Point begin){
    
    FloatWord* floatWord = new FloatWord();
    if (floatWord && floatWord->init(word, fontSize, begin)) {
        
        floatWord->autorelease();
        return floatWord;
    }
    CC_SAFE_DELETE(floatWord);
    
    return nullptr;
}

bool FloatWord::init(const std::string& word, const int fontSize, Point begin){
    
    if (!Node::init()) {
        return false;
    }
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _begin = begin;
    
    _label = Label::createWithSystemFont(word, "Arial", fontSize);
    _label->setPosition(begin);
    this->addChild(_label);
    
    return true;
}

void FloatWord::floatIn(const float delay,  std::function<void()>callback){
    
    auto moveTo = MoveTo::create(delay, Point(_visibleSize.width/2, _begin.y));
    auto callFunc = CallFunc::create(callback);
    auto seq = Sequence::create(moveTo, callFunc, NULL);
    
    _label->runAction(seq);
}

void FloatWord::floatOut(const float delay,  std::function<void()>callback){
    
    //移出屏幕
    auto moveTo = MoveTo::create(delay, Point(-100, _begin.y));
    auto callFunc = CallFunc::create(callback);
    
    auto removeFunc = CallFunc::create([this](){
        
        this->removeFromParentAndCleanup(true);
    });
    auto seq = Sequence::create(moveTo, callFunc, removeFunc, NULL);
    
    _label->runAction(seq);
}

void FloatWord::floatInOut(const float speed, const float delay, std::function<void()>callback){
    
    auto moveIn  = MoveTo::create(speed, Point(_visibleSize.width/2, _begin.y));
    auto moveOut = MoveTo::create(speed, Point());
    
    auto removeFunc = CallFunc::create([this](){
    
        this->removeFromParentAndCleanup(true);
    });
    
    auto callFunc = CallFunc::create(callback);
    
    auto delayTime = DelayTime::create(delay);
    auto seq = Sequence::create(moveIn, delayTime, moveOut, removeFunc, callFunc, NULL);

    _label->runAction(seq);
}







