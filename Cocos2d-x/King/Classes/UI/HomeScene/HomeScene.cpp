#include "HomeScene.h"

//use
#include "Utils\Config.h"

bool HomeScene::init() {
	if(!Layer::init()) {
		return false;
	}

	_mapLayer = HomeMapLayer::create();
	this->addChild(_mapLayer, 1);

	_optionLayer = HomeOptionLayer::create();
	this->addChild(_optionLayer, 9);

	_hubLayer = HomeHubLayer::create();
	this->addChild(_hubLayer, 9);

	return true;
};

Scene* HomeScene::createScene() {

	auto scene = Scene::create();
	auto layer = HomeScene::create();
	scene->addChild(layer);

	return scene;
};