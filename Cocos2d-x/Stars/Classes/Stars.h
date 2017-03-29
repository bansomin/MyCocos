//
//  Stars.h
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#ifndef __Stars__Stars__
#define __Stars__Stars__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class Stars : public Sprite{

private:
    int _index_i;
    int _index_j;
    
    int _color;
    
    bool _selected;
    Point _desPosition;
    
private:
    char* getImage(int color);
   
public:
    enum color{
        GREEN,
        RED,
        YELLOW,
        PURPLE,
        BLUE
    };
    
    const static int _MOVE_SPEED    = 8;    //移动
    static const int _STAR_WIDTH    = 72;
    static const int _STAR_HEIGHT   = 72;
    static const int _COLOR_MAX_NUM = 5;    //类型种类数

public:
    static Stars* create(int color);
    
    int getColor();
    int getIndexI();
    int getIndexJ();
    bool isSelected();
    void updatePosition();  //更新位置
    Point getDesPosition(); //得到目的位置
    void setSelected(bool b);
    void setIndex_IJ(int i, int j);
    void setDesPosition(const Point& point);
};

#endif /* defined(__Stars__Stars__) */







