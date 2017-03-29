//
//  SetLayer.cpp
//  Stars
//
//  Created by HAO on 15-7-28.
//
//
#include "Audio.h"
#include "GameData.h"
#include "GameData.h"
#include "SetLayer.h"
#include "MenuScene.h"

extern bool isMusic;
extern bool isSound;
extern bool isModel;

SetLayer::SetLayer(){

    this->initWithColor(Color4B(150, 150, 150, 150));
    
    Size winSize = Director::getInstance()->getWinSize();
    
//背景
    auto bg = Sprite::create("bg_love1.png");
    Rect rectBg  = bg->getBoundingBox();
    float scalex = winSize.width / rectBg.size.width;
    float scaley = winSize.height/ rectBg.size.height;
    bg->setPosition(winSize.width/2, winSize.height/2);
    bg->setScale(scalex, scaley);
    addChild(bg, -1);
    
//取消按钮
    auto itemCancleBtn = MenuItemImage::create("Btn_close.png",
                                               "Btn_close.png",
                                               CC_CALLBACK_1(SetLayer::itemCancelFunc, this));
    itemCancleBtn->setPosition(Vec2(winSize.width - 120, winSize.height-80));
    itemCancleBtn->setScale(0.8f);
    
   
    
//音乐滑块
    sliderMusic = ControlSlider::create("Slider_Back.png",
                                        "Slider_PressBar.png",
                                        "SliderNode_Normal.png");
    
    sliderMusic->setPosition(Vec2(itemCancleBtn->getPosition() + Vec2(-100, -200)));
    sliderMusic->setMaximumValue(100.0f);
    //sliderMusic->setEnabled(false);
    
    //如果启用，只能滑动一半
    //mySlider->setMaximumAllowedValue(50);
    sliderMusic->setValue(50.0f);
    sliderMusic->setMinimumValue(0.0f);
    sliderMusic->setScale(1.5f);
    sliderMusic->setTag(1);
    
    sliderMusic->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::valueChanged), Control::EventType::VALUE_CHANGED);
    
    addChild(sliderMusic);
 

//音效滑块
    sliderSound = ControlSlider::create("Slider_Back.png",
                                             "Slider_PressBar.png",
                                             "SliderNode_Normal.png");
    
    sliderSound->setPosition(Vec2(sliderMusic->getPosition() + Vec2(0, -100)));
    sliderSound->setMaximumValue(100.0f);
    //sliderSound->setEnabled(false);
    
    //如果启用，只能滑动一半
    //sliderSound->setMaximumAllowedValue(50);
    sliderSound->setValue(50.0f);
    sliderSound->setMinimumValue(0.0f);
    sliderSound->setScale(1.5f);
    sliderSound->setTag(2);
    
    sliderSound->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::valueChanged), Control::EventType::VALUE_CHANGED);
    
    addChild(sliderSound);
    
    
//音乐复选框
    checkBoxMusic = MenuItemImage::create("CheckBox_off.png",
                                          "CheckBox_on.png",
                                          CC_CALLBACK_1(SetLayer::checkBoxChangeFunc, this));
    checkBoxMusic->setPosition(Vec2(sliderMusic->getPosition() + Vec2(-200, 0)));
    checkBoxMusic->setScale(0.25f);
    checkBoxMusic->setTag(1);

//音效复选框
    checkBoxSound = MenuItemImage::create("CheckBox_off.png",
                                          "CheckBox_on.png",
                                          CC_CALLBACK_1(SetLayer::checkBoxChangeFunc, this));
    checkBoxSound->setPosition(Vec2(sliderSound->getPosition() + Vec2(-200, 0)));
    checkBoxSound->setScale(0.25f);
    checkBoxSound->setTag(2);
    
  
    
//单选框
//星星模式选择
    sigCheckBoxStarsOne = MenuItemImage::create("CheckBox_sigOff.png",
                                                "CheckBox_sigOn.png",
                                                CC_CALLBACK_1(SetLayer::sigcheckBoxChangeFunc, this));
    sigCheckBoxStarsOne->setPosition(Vec2(winSize.width/2 - 130, sliderSound->getPositionY() - 150));
    sigCheckBoxStarsOne->setScale(0.2f);
    sigCheckBoxStarsOne->setTag(3);
    
    
    sigCheckBoxStarsTwo = MenuItemImage::create("star_red.png",
                                                "star_red.png",
                                                CC_CALLBACK_1(SetLayer::sigcheckBoxChangeFunc, this));
    sigCheckBoxStarsTwo->setPosition(Vec2(sigCheckBoxStarsOne->getPosition() + Vec2(0, -130)));
    sigCheckBoxStarsTwo->setScale(1.0f);
    sigCheckBoxStarsTwo->setTag(4);

//心模式
    sigCheckBoxHeartsOne = MenuItemImage::create("CheckBox_sigOff.png",
                                                "CheckBox_sigOn.png",
                                                CC_CALLBACK_1(SetLayer::sigcheckBoxChangeFunc, this));
    sigCheckBoxHeartsOne->setPosition(Vec2(winSize.width/2 + 130, sliderSound->getPositionY() - 150));
    sigCheckBoxHeartsOne->setScale(0.2f);
    sigCheckBoxHeartsOne->setTag(5);
    
    
    sigCheckBoxHeartsTwo = MenuItemImage::create("heart_red.png",
                                                 "heart_red.png",
                                                 CC_CALLBACK_1(SetLayer::sigcheckBoxChangeFunc, this));
    sigCheckBoxHeartsTwo->setPosition(Vec2(sigCheckBoxHeartsOne->getPosition() + Vec2(0, -130)));
    sigCheckBoxHeartsTwo->setScale(1.0f);
    sigCheckBoxHeartsTwo->setTag(6);

//默认为Hearts模式
    if (isModel) {
        sigCheckBoxHeartsOne->setEnabled(false);
        sigCheckBoxHeartsTwo->setEnabled(false);
        sigCheckBoxHeartsOne->selected();
        sigCheckBoxHeartsTwo->selected();
        
        
        sigCheckBoxStarsOne->unselected();
        sigCheckBoxStarsTwo->unselected();
        sigCheckBoxStarsOne->setEnabled(true);
        sigCheckBoxStarsTwo->setEnabled(true);
    }
    else{
        sigCheckBoxHeartsOne->unselected();
        sigCheckBoxHeartsTwo->unselected();
        sigCheckBoxHeartsOne->setEnabled(true);
        sigCheckBoxHeartsTwo->setEnabled(true);
        
        sigCheckBoxStarsOne->setEnabled(false);
        sigCheckBoxStarsTwo->setEnabled(false);
        sigCheckBoxStarsOne->selected();
        sigCheckBoxStarsTwo->selected();
    }
    

    auto menu = Menu::create(itemCancleBtn, checkBoxMusic, checkBoxSound, sigCheckBoxStarsOne, sigCheckBoxHeartsOne, sigCheckBoxStarsTwo, sigCheckBoxHeartsTwo, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
    
//音乐标签
    auto sprMusic = Sprite::create("Pic_music.png");
    sprMusic->setPosition(Vec2(checkBoxMusic->getPosition() + Vec2(-110, 0)));
    sprMusic->setScale(0.5f);
    addChild(sprMusic);
    
//音效标签
    auto sprSound = Sprite::create("Pic_sound.png");
    sprSound->setPosition(Vec2(checkBoxSound->getPosition() + Vec2(-110, 0)));
    sprSound->setScale(0.5f);
    addChild(sprSound);
    
    
    if (isMusic) {
        checkBoxMusic->selected();
        Audio::getInstance()->resumeMusic();
    }
    else{
        checkBoxMusic->unselected();
        Audio::getInstance()->pauseMusic();
    }
    
    if (isSound) {
        checkBoxSound->selected();
        Audio::getInstance()->resumeSound();
    }
    else{
        checkBoxSound->unselected();
        Audio::getInstance()->pauseMusic();
    }

//触摸
    auto callFunc = [](Touch*, Event*){
        
        return true;
    };
    
    auto listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->onTouchBegan = callFunc;
    
    listenerTouch->setSwallowTouches(true);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);
}

void SetLayer::itemCancelFunc(Ref* sender){
    printf("SetLayer_itemCancelFunc()");
    
    this->removeFromParentAndCleanup(true);
    
    auto scene = MenuScene::scene();
    Director::getInstance()->replaceScene(scene);
}

void SetLayer::valueChanged(Ref* sender, Control::EventType type){
    printf("SetLayer_valueChanged()\n");
    
    auto mySlider = (ControlSlider*)sender;
    
    if (mySlider->getTag() == 1) {
        Audio::getInstance()->setValueMusic(mySlider->getValue()/100);
    }
    if (mySlider->getTag() == 2) {
        Audio::getInstance()->setValueSound(mySlider->getValue()/100);
    }
}

void SetLayer::checkBoxChangeFunc(Ref* sender){

    auto item = (Menu*)sender;
    
    if (item->getTag() == 1) {
        if (isMusic) {
            isMusic = false;
            checkBoxMusic->unselected();
            sliderMusic->setEnabled(false);
            Audio::getInstance()->pauseMusic();
        }
        else{
            isMusic = true;
            checkBoxMusic->selected();
            sliderMusic->setEnabled(true);
            Audio::getInstance()->resumeMusic();
        }
    }
    
    if (item->getTag() == 2) {
        if (isSound) {
            isSound = false;
            checkBoxSound->unselected();
            sliderSound->setEnabled(false);
            Audio::getInstance()->pauseSound();
        }
        else{
            isSound = true;
            checkBoxSound->selected();
            sliderSound->setEnabled(true);
            Audio::getInstance()->resumeSound();
        }
    }
}

void SetLayer::sigcheckBoxChangeFunc(Ref* sender){
    
    auto item = (Menu*)sender;
    
    //星星
    if (item->getTag() == 3 || item->getTag() == 4) {
        printf("Stars\n");
        if (isModel) {
            isModel = false;
            sigCheckBoxStarsOne->setEnabled(false);
            sigCheckBoxStarsTwo->setEnabled(false);
            sigCheckBoxStarsOne->selected();
            sigCheckBoxStarsTwo->selected();
            
            
            sigCheckBoxHeartsOne->setEnabled(true);
            sigCheckBoxHeartsTwo->setEnabled(true);
            sigCheckBoxHeartsOne->unselected();
            sigCheckBoxHeartsTwo->unselected();
        }
    }
    
    //心
    if (item->getTag() == 5 || item->getTag() == 6) {
        printf("Hearts\n");
        if (!isModel) {
            isModel = true;
            sigCheckBoxStarsOne->setEnabled(true);
            sigCheckBoxStarsTwo->setEnabled(true);
            sigCheckBoxStarsOne->unselected();
            sigCheckBoxStarsTwo->unselected();
            
            sigCheckBoxHeartsOne->setEnabled(false);
            sigCheckBoxHeartsTwo->setEnabled(false);
            sigCheckBoxHeartsOne->selected();
            sigCheckBoxHeartsTwo->selected();           
        }
    }
}








