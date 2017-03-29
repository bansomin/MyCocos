//
//  Stars.cpp
//  Stars
//
//  Created by HAO on 15-7-18.
//
//

#include "Stars.h"

extern bool isModel;

Stars* Stars::create(int color){
    
    Stars* ret = new Stars();
    if (ret && ret->initWithFile(ret->getImage(color))) {
        ret->_color = color;
        ret->_selected = false;
        ret->autorelease();
        
        return ret;
    }
    CC_SAFE_DELETE(ret);

    return nullptr;
}

//利用isModel进行选择模式
char* Stars::getImage(int color){
    
//选择心形
    if (isModel) {
        switch (color) {
            case color::RED:
                return "red2.png";
                break;
            case color::BLUE:
                return "blue2.png";
                break;
            case color::GREEN:
                return "green2.png";
                break;
            case color::YELLOW:
                return "orange2.png";
                break;
            default:
                return "purple2.png";
                break;
        }
    }
//选择星星
    else{
        switch (color) {
            case color::RED:
                return "red.png";
                break;
            case color::BLUE:
                return "blue.png";
                break;
            case color::GREEN:
                return "green.png";
                break;
            case color::YELLOW:
                return "orange.png";
                break;
            default:
                return "purple.png";
                break;
        }
    }
}

bool Stars::isSelected(){
    
    return _selected;
}

void Stars::setSelected(bool b){
    
    _selected = b;
}

int Stars::getColor(){
    
    return _color;
}

void Stars::setDesPosition(const Point& point){
    
    _desPosition = point;
}

Point Stars::getDesPosition(){
    
    return _desPosition;
}

void Stars::updatePosition(){
    
    if (_desPosition.y != getPositionY()) {
        setPositionY(getPositionY() - _MOVE_SPEED);
        if (getPositionY() < _desPosition.y) {
            setPositionY(_desPosition.y);
        }
    }
    
    if (_desPosition.x != getPositionX()) {
        setPositionX(getPositionX() - _MOVE_SPEED);
        if (getPositionX() < _desPosition.x) {
            setPositionX(_desPosition.x);
        }
    }
}

int Stars::getIndexI(){

    return _index_i;
}

int Stars::getIndexJ(){

    return _index_j;
}

void Stars::setIndex_IJ(int i, int j){

    _index_i = i;
    _index_j = j;
}











