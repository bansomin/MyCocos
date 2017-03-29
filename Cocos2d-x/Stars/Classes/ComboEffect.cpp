//
//  ComboEffect.cpp
//  Stars
//
//  Created by HAO on 15-7-19.
//
//
#include "Audio.h"
#include "ComboEffect.h"

extern bool isSound;

void showComboEffect(int size, Node* node){

    if (size < 5)
        return;
  
    Size visible = Director::getInstance()->getVisibleSize();
    
    Sprite* comboSprite;
    
    if (size >= 10) {
		comboSprite = Sprite::create("combo_3.png");
        if (isSound) {
            Audio::getInstance()->playFireWorks(3);
        }
    }
    else if (size >= 7){
        comboSprite = Sprite::create("combo_2.png");
        if (isSound) {
            Audio::getInstance()->playFireWorks(2);
        }
    }
    else{
        comboSprite = Sprite::create("combo_1.png");
        if (isSound) {
            Audio::getInstance()->playFireWorks(1);
        }
    }
    
    comboSprite->setPosition(Vec2(visible.width/2, visible.height/2));
    node->addChild(comboSprite);
    
    Blink* blink  = Blink::create(1.0f, 5);
    auto callFunc = CallFunc::create([=](){
        
        comboSprite->removeFromParentAndCleanup(true);
    });
    
    auto seq = Sequence::create(blink, callFunc, NULL);
    
    comboSprite->runAction(seq);    
}












