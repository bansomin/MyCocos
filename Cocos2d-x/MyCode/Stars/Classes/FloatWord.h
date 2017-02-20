//
//  FloatWord.h
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#ifndef __Stars__FloatWord__
#define __Stars__FloatWord__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class FloatWord : public Node{
    
private:
    Point _begin;
    int _fontSize;
    Label* _label;
    Size _visibleSize;

public:
    static FloatWord* create(const std::string& word, const int fontSize, Point begin);
    bool init(const std::string& word, const int fontSize, Point begin);
    
public:
    void floatIn(const float delay,  std::function<void()>callback);
    void floatOut(const float delay,  std::function<void()>callback);
    void floatInOut(const float speed, const float delay, std::function<void()>callback);
};

#endif /* defined(__Stars__FloatWord__) */









