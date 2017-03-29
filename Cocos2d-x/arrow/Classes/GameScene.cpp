/**
* Created by HAO on 2016/9/2.
*/

#include "GameScene.h"

GameScene::GameScene() {

	Wsize = Director::getInstance()->getWinSize();
	preTouchPoint = Vec2(0, 0);
	curTouchPoint = Vec2(0, 0);
	player = NULL;
	isMoved = false;
};

GameScene::~GameScene() {

};

bool GameScene::init() {

	if (!Layer::init()) { 
		return false;
	}

	//Ô¤¼ÓÔØ×ÊÔ´
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist", "texture.pvr.ccz");

	//¶¯»­
	auto animation = createAnimation("player", 8, 0.06f);
	AnimationCache::getInstance()->addAnimation(animation, "player");

	//¼ÓÔØ±³¾°
	this->addBgFunc();

	//player
	player = Player::create(Vec2(Wsize.width/4, Wsize.height/5));
	this->addChild(player);

	//´¥Ãþ
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
};

void GameScene::addBgFunc() {

	//±³¾°
	auto bg = Sprite::create("bg1.jpg");
	if (bg) {
		bg->setPosition(Vec2(Wsize.width / 2, Wsize.height / 2));
		this->addChild(bg);
	}

	//µØÍ¼
	map = TMXTiledMap::create("map2.tmx");
	map->setAnchorPoint(Vec2(0.5f, 0));
	map->setPosition(Vec2(Wsize.width / 2, 0));
	this->addChild(map);
};

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
	log("onTouchBegan");

 /*
	auto point = touch->getLocation ();
	auto target = unused_event->getCurrentTarget ();
	curTouchPoint = map->convertToNodeSpace (point);
	log ("point = %f, %f", point.x, point.y);
	log ("curPoint = %f, %f", curTouchPoint.x, curTouchPoint.y);
	curTouchPoint = touch->getLocation ();
    if (!curTouchPoint.equals (preTouchPoint)) {
        player->initRotateArrow (curTouchPoint);
    }
	preTouchPoint = curTouchPoint;
	*/

	return true;
};  
            
void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {               
	log("onTouchMoved");

	curTouchPoint = touch->getLocation ();
	if (!curTouchPoint.equals (preTouchPoint)) {
        player->rotateArrow (curTouchPoint);
		preTouchPoint = curTouchPoint;
		isMoved = true;
    }
};

void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {       
	log("onTouchEnded");

	if (isMoved) {
		isMoved = false;
		curTouchPoint = touch->getLocation ();
		player->createAndShootArrow (curTouchPoint);
	}
};

Animation* GameScene::createAnimation(string prefixName, int framesNum, float delay) {      

	Vector<SpriteFrame*> animaFrames;

	for (int i = 1; i < framesNum; i++) {
		char buffer[20] = { 0 };
		sprintf(buffer, "%i.png", i);
		string str = prefixName + buffer;

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animaFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animaFrames, delay);
};


Scene* GameScene::createScene() {

	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
};
