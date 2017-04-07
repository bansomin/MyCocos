#include "GlobalManager.h"

//use
#include "UI\HomeScene\HomeScene.h"
#include "UI\WorldScene\WorldScene.h"

GlobalManager* GlobalManager::_instance = nullptr;
GlobalManager* GlobalManager::getInstance() {

	if(_instance==nullptr) {
		_instance = new GlobalManager();
		_instance->init();
	}

	return _instance;
};

GlobalManager::GlobalManager() {

};

GlobalManager::~GlobalManager() {

};

bool GlobalManager::init() {

	return true;
};

void GlobalManager::enterWorldScene() {
	//log("enterWorldScene");

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WorldScene::createScene()));
};

void GlobalManager::enterHomeScene() {

	//log("enterWorldScene");
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HomeScene::createScene()));
};

void GlobalManager::enterChapterScene(int townID, int type) {

};
