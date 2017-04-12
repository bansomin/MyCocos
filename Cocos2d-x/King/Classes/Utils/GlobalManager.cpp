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
	_instance = nullptr;
};

bool GlobalManager::init() {

	return true;
};

// 获取时间戳
int GlobalManager::getTimeStamp() {
	
	timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec;
};

//intתstring
string GlobalManager::getIntToStr(int value) {
	if(value<=0) return "0";
	string str = "";
	while(value) {
		str += value%10+'0';
		value /= 10;
	}
	reverse(str.begin(), str.end());
	return str;
};

// stringתint
int GlobalManager::getStrToInt(string value) {
	int x = 0;
	for(int i = 0; i < (int)value.length(); i++) {
		x = x*10+(value[i]-'0');
	}
	return x;
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

