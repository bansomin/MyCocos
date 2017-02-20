//
//  GameScene.cpp
//  Stars
//
//  Created by HAO on 15-7-17.
//
//

#include "Audio.h"
#include "GameData.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "PauseLayer.h"
#include "StarMatrix.h"
#include "GameOverLayer.h"

extern bool isSound;

Scene* GameScene::scene(){
    
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init(){

    if (!Layer::init()) {
        
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _winSize     = Director::getInstance()->getWinSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
    char tempScore[20];
    sprintf(tempScore, "cur_level_score%d",GAMEDATA::getInstance()->getCurLevel());
    
    printf("GameScene_init()_UserDefault = %f", UserDefault::getInstance()->getFloatForKey(tempScore));
    
//背景
    auto bg = Sprite::create("bg_mainscene.jpg");
    Rect rectBg = bg->getBoundingBox();
    float scalex = _winSize.width / rectBg.size.width;
    float scaley = _winSize.height/ rectBg.size.height;
    bg->setPosition(_visibleSize.width/2, _visibleSize.height/2);
    bg->setScale(scalex, scaley);
    addChild(bg, -1);
    
//设置按钮
    auto itemSet = MenuItemImage::create("Btn_link.png",
                                         "Btn_link.png",
                                         CC_CALLBACK_1(GameScene::setGameMenuFunc, this));
    itemSet->setPosition(Vec2(_winSize.width - 50, _winSize.height- 20));
    itemSet->setScale(0.2f);
    
//菜单
    auto menu = Menu::create(itemSet, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
//加载ToMenu
    _menu = TopMenu::create();
    this->addChild(_menu);
    
//linkNum
    _linkNum = Label::createWithSystemFont("linkNum", "Arial", 40);
    _linkNum->setPosition(_winSize.width/2, _winSize.height - 200);
    _linkNum->setVisible(false);
    this->addChild(_linkNum, 1);
    
//显示字
     this->floatLevelWord();

//_matrix初始化
    _matrix = nullptr;
    
//时间调度
    this->scheduleUpdate();    
    
//触摸
    EventListenerTouchOneByOne* listenerTouch = EventListenerTouchOneByOne::create();
    listenerTouch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);
    
//安卓平台返回键监听
    auto listenerKeyBoard = EventListenerKeyboard::create();
    listenerKeyBoard->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
    
    return true;
}


//飘出关卡信息
void GameScene::floatLevelWord(){
    
    printf("GameScene_floatLevelWord()_getNextLevel = %d",GAMEDATA::getInstance()->getNextLevel());
    
    _levelMsg = FloatWord::create(__String::createWithFormat("第%d关",GAMEDATA::getInstance()->getNextLevel())->_string,
                                  50, Point(_visibleSize.width, _visibleSize.height-200)
                                  );
    
    this->addChild(_levelMsg, 1);
    
    _levelMsg->floatIn(1.0f, CC_CALLBACK_0(GameScene::floatTargetScoreWord, this));
    
    if (isSound) {
        Audio::getInstance()->playReadyGo();
    }
}

//飘出目标分数信息
void GameScene::floatTargetScoreWord(){
    
    _targetScoreMsg = FloatWord::create(__String::createWithFormat("目标:%d分",GAMEDATA::getInstance()->getNextScore())->_string,
                                  50, Point(_visibleSize.width,_visibleSize.height-250)
                                  );
    this->addChild(_targetScoreMsg);
    
    _targetScoreMsg->floatIn(1.0f, CC_CALLBACK_0(GameScene::removeFloatWord, this));
}


//移除关卡信息和目标分数
void GameScene::removeFloatWord(){
    
    _levelMsg->floatOut(1.5f, nullptr);
    _targetScoreMsg->floatOut(1.5f, CC_CALLBACK_0(GameScene::showStarMatrix, this));
}

//创造星星矩阵(所有星星)
void GameScene::showStarMatrix(){

    printf("showStarMatrix");
    
    _matrix = StarMatrix::create(this);
    
    this->addChild(_matrix);
}

//显示连击信息
void GameScene::showLinkNum(int size){
    
    string str ="连击" +  __String::createWithFormat("%d ",size)->_string +"奖励" + __String::createWithFormat("%d", size*size*5)->_string + "分";
    _linkNum->setString(str);
    _linkNum->setVisible(true);
}

//隐藏连击信息
void GameScene::hideLinkNum(){
    
    _linkNum->setVisible(false);
}

//调到下一关
void GameScene::gotoNextLevel(){
    
    refreshMenu();
    floatLevelWord();
}

//刷新顶部信息
void GameScene::refreshMenu(){
    
    _menu->refresh();
}


//游戏结束
void GameScene::gotoGameOver(){
    
    GAMEDATA::getInstance()->saveHighestScore();
    
    FloatWord* gameOver = FloatWord::create("游戏结束!", 80, Point(_visibleSize.width, _visibleSize.height*2/3));
    addChild(gameOver);
    
    gameOver->floatIn(3.0f, NULL);
    
    auto layer = new GameOverLayer();
    addChild(layer);
}

void GameScene::floatLeftStarMsg(int leftNum){
    
    FloatWord* leftStarMsg = FloatWord::create(__String::createWithFormat("剩余%d个星星", leftNum)->_string, 35, Vec2(_visibleSize.width, _visibleSize.height-250));
    
    this->addChild(leftStarMsg);
    
    //获取奖励分数
    int jiangli = GAMEDATA::getInstance()->getJiangli(leftNum);
    
    FloatWord* jingliMsg = FloatWord::create(__String::createWithFormat("奖励%d分!!", jiangli)->_string, 35, Vec2(_visibleSize.width, _visibleSize.height-300));
    this->addChild(jingliMsg);
    
    leftStarMsg->floatInOut(1.0f, 3.0f,
                            
                            [=](){
                            
                                this->hideLinkNum();
                                _matrix->setNeedClear(true);
                                GAMEDATA* data = GAMEDATA::getInstance();
                                
                                data->setCurScore(data->getCurScore() + jiangli);
                                
                                if (data->getCurScore() > data->getHistoryScore()) {
                                    data->setHistoryScore(data->getCurScore());
                                }
                                refreshMenu();
                            });

    jingliMsg->floatInOut(1.0f, 4.0f, nullptr);
}

//设置按钮函数
void GameScene::setGameMenuFunc(Ref* sender){
    
    scaleSelf(sender, 0.23f, 0.2f);
    
    PauseLayer* layer = new PauseLayer();
    this->addChild(layer);
    Director::getInstance()->pause();
}

//缩放
void GameScene::scaleSelf(Ref* sender, float before, float after){
    
    auto self    = (Menu*)sender;
    
    auto scaleBg = ScaleTo::create(0.1, before);
    auto scaleLt = ScaleTo::create(0.1, after);
    auto seq     = Sequence::create(scaleBg, scaleLt, NULL);
    
    self->runAction(seq);
}

//每帧刷新调用的回调函数
void GameScene::update(float delta){
    
    if (_matrix) {
        _matrix->updateStar(delta);
    }
}

//触摸事件发生回调的函数
bool GameScene::onTouchBegan(Touch* touch, Event* event){
    
    Point point = touch->getLocationInView();
    point = Director::getInstance()->convertToGL(point);
    
    if (_matrix) {
        _matrix->onTouch(point);
    }
    return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event){
    
    switch (keycode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE:{  //返回
            
            if (isBack) {   //进入暂停层
                isBack = false;
                PauseLayer* layer = new PauseLayer();
                layer->setName("PauseLayer");
                this->addChild(layer);
                Director::getInstance()->pause();
            }
            else{
                isBack = true;
                this->removeChildByName("PauseLayer");
                Director::getInstance()->resume();
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_MENU:{   //菜单
            printf("KEY_MENU!!");
            break;
        }
        default:
            break;
    }
}





