#include "WorldScene.h"

bool WorldScene::init() {

	if(!Layer::init()) {
		return false;
	}

	_hubLayer = WorldHubLayer::create();
	this->addChild(_hubLayer, 9);

	return true;
};

Scene* WorldScene::createScene() {
	auto scene = Scene::create();
	auto layer = WorldScene::create();
	scene->addChild(layer);

	return scene;
};
