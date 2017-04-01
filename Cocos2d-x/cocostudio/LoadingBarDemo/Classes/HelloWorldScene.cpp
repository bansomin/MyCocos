#include "HelloWorldScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if(!Layer::init()) {
		return false;
	}
    
	_loadingBarNode = CSLoader::createNode("LoadingLayer.csb");
    addChild(_loadingBarNode);

	//获取csb中的进度条
	_loadingBar = static_cast<LoadingBar*>(_loadingBarNode->getChildByName("LoadingBar_1"));
	//获取csb中的文字
	_text = static_cast<Text*>(_loadingBar->getChildByName("Text_1"));

	//更新
	this->schedule(schedule_selector(HelloWorld::update), 0.01);
	//scheduleUpdate();

    return true;
}

//帧循环调用方法
void HelloWorld::update(float dt) {

	int num = _loadingBar->getPercent();
	_loadingBar->setPercent(++num);

	//CCLOG("%s", _text->getString().c_str());

	_text->setString(StringUtils::format("Loading...%d%c", (int)_loadingBar->getPercent(), '%'));

	if(num>=100) {
		//_loadingBarNode->removeFromParent();
		auto label = Label::create("WARING : Completed!!", "arial", 20);
		label->setPosition(_loadingBar->getPositionX(), _loadingBar->getPositionY()*1.4);
		this->addChild(label, 10);
	}

};

Scene* HelloWorld::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
