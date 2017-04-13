#include "GlobalManager.h"

//use
#include "Utils\Config.h"
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

//解决中文乱码
const char* GlobalManager::getCN(string key) {

	auto chnStr = Dictionary::createWithContentsOfFile("fonts/myString.xml");
	const char* back = ((__String*)chnStr->objectForKey ("back"))->getCString();
	return back;
};

// 清空占地情况
void GlobalManager::clearCovered() {

	//初始化占地情况
	for(int i = 0; i<TILED_TOTAL_X; i++) {
		for(int j = 0; j<TILED_TOTAL_Y; j++) {
			_cover[i][j] = 0;
		}
	}
};

// 占据/释放地面：delta=1占据，=-1释放
void GlobalManager::setCoverd(Vec2 pos, int delta) {

	for(int i = 0; i<9; i++) {
		int x = pos.x + DX[i];
		int y = pos.y + DY[i];
		if(x<0 || x>TILED_TOTAL_X || 
		   y<0 || y>TILED_TOTAL_Y ) {
			continue;
		}
		_cover[x][y] += delta;
	}
};

// 瓦片坐标 转 地图坐标
Vec2 GlobalManager::getMapPos(Vec2 pos) {
	//log("GlobalManager::getMapPos %f, %f", pos.x, pos.y);

	float x = TILED_WIDTH/2.0 * (pos.y-pos.x)+MAP_X;
	float y = -1.0 * (TILED_HEIGHT/2.0) * (pos.y+pos.x)+MAP_Y;
	//log("X : %f, %f", x, y);
	return Vec2(x, y);
};

// 地图坐标 转 瓦片坐标
Vec2 GlobalManager::getTiledPos(Vec2 pos) {

	int x = (pos.x-MAP_X)/(TILED_WIDTH/2.0);
	int y = (-1.0*(pos.y-MAP_Y)/(TILED_HEIGHT/2.0));
	int tx = (y-x)/2;
	int ty = (y+x)/2;
	return Vec2(tx, ty);
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

