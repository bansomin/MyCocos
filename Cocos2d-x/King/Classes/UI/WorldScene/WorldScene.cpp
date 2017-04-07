#include "WorldScene.h"

bool WorldScene::init() {

	if(!Layer::init()) {
		return false;
	}

	return true;
};

Scene* WorldScene::createScene() {
	auto scene = Scene::create();
	auto layer = WorldScene::create();
	scene->addChild(layer);

	return scene;
};
