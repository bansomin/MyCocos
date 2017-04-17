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

	for(int i = 0; i < 9; i++) {
		int x = pos.x + DX[i];
		int y = pos.y + DY[i];
		if(x < 0||x > TILED_TOTAL_X||y < 0||y > TILED_TOTAL_Y) continue;
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

// 获取空地
Vec2 GlobalManager::getSpaceTiled() {

	queue<int> que;
	bool vis[TILED_TOTAL_X+1][TILED_TOTAL_Y+1];
	memset(vis, false, sizeof(vis));

	que.push(19);
	que.push(19);
	vis[19][19] = true;

	/*
	while(!que.empty()) {
		int x = que.front();
		que.pop();
		int y = que.front();
		que.pop();

		if(_cover[x][y] == 0) {
			return Vec2(x, y);
		}

		for(int i = 0; i<NUMBER_NINE; i++) {
			if(DX[i]==0 && DY[i]==0) continue;
			int xx = x + DX[i];
			int yy = y + DY[i];
			if(xx<0 || xx>TILED_TOTAL_X || yy<0 || yy>TILED_TOTAL_Y)continue;
			if(vis[xx][yy]) continue;
			vis[xx][yy] = true;
			que.push(xx);
			que.push(yy);
		}
	}
	return Vec2(19, 19);
	*/

	return Vec2(random(0, 38), random(0, 38));
};

// 随机获取当前位置周围的空地
ValueVector GlobalManager::getNextSpace(Vec2 pos) {

	ValueVector vv;
	for(int i = 0; i < 9; i++) {
		if(DX[i]==0&&DY[i]==0) continue;
		int xx = pos.x+DX[i];
		int yy = pos.y+DY[i];
		if(xx < 0||xx > TILED_TOTAL_X||yy < 0||yy > TILED_TOTAL_Y) continue;
		if(_cover[xx][yy]) continue;

		ValueMap map;
		map["x"] = xx; map["y"] = yy; map["dir"] = i;
		vv.push_back((Value)map);
	}
	return vv;
};

// 根据瓦片坐标的偏移方向，获取地图坐标的偏移量
Vec2 GlobalManager::getMapDelta(int index) {

	switch(index) {
		case 0: return Vec2(0, -TILED_HEIGHT);
			break;
		case 1: return Vec2(-TILED_WIDTH/2, -TILED_HEIGHT/2);
			break;
		case 2: return Vec2(-TILED_WIDTH, 0);
			break;
		case 3: return Vec2(-TILED_WIDTH/2, TILED_HEIGHT/2);
			break;
		case 4: return Vec2(0, TILED_HEIGHT);
			break;
		case 5: return Vec2(TILED_WIDTH/2, TILED_HEIGHT/2);
			break;
		case 6: return Vec2(TILED_WIDTH, 0);
			break;
		case 7: return Vec2(TILED_WIDTH/2, -TILED_HEIGHT/2);
			break;
		default:
			break;
	}
	return Vec2(0, 0);
};

// 获取建筑的图片名
Sprite* GlobalManager::getBuildingIMG(int type) {
	log("GlobalManager::getBuildingIMG = %d", type);

	auto tempSprite = Sprite::create();
	switch(type) {
		case BUILDING_TYPE_BaseTower:
			tempSprite->setTexture(IMG_BUILDING_BaseTower);
			break;
		case BUILDING_TYPE_Raider:
			tempSprite->setTexture(IMG_BUILDING_Raider);
			break;
		case BUILDING_TYPE_HeroHotel:
			tempSprite->setTexture(IMG_BUILDING_HeroHotel);
			break;
		case BUILDING_TYPE_Camp:
			tempSprite->setTexture(IMG_BUILDING_Camp);
			break;
		case BUILDING_TYPE_ResearchLab:
			tempSprite->setTexture(IMG_BUILDING_ResearchLab);
			break;
		case BUILDING_TYPE_MineFactory:
			tempSprite->setTexture(IMG_BUILDING_MineFactory);
			break;
		case BUILDING_TYPE_WoodFactory:
			tempSprite->setTexture(IMG_BUILDING_WoodFactory);
			break;
		case BUILDING_TYPE_ArrowTower:
			tempSprite->setTexture(IMG_BUILDING_ArrowTower);
			break;
		case BUILDING_TYPE_Cannon:
			tempSprite->setTexture(IMG_BUILDING_Cannon);
			break;
		case BUILDING_TYPE_Laser:
			tempSprite->setTexture(IMG_BUILDING_Laser);
			break;
		default:
			break;
	}
	return tempSprite;
};

// 获取建筑被摧毁后的图片名
Sprite* GlobalManager::getBuildingBrokenIMG(int type) {
	log("GlobalManager::getBuildingBrokenIMG = %d", type);

	auto tempSprite = Sprite::create();
	switch(type) {
		case BUILDING_TYPE_BaseTower:
			tempSprite->setTexture(IMG_BUILDING_BaseTower_Broken);
			break;
		case BUILDING_TYPE_Raider:
			tempSprite->setTexture(IMG_BUILDING_Raider_Broken);
			break;
		case BUILDING_TYPE_HeroHotel:
			tempSprite->setTexture(IMG_BUILDING_HeroHotel_Broken);
			break;
		case BUILDING_TYPE_Camp:
			tempSprite->setTexture(IMG_BUILDING_Camp_Broken);
			break;
		case BUILDING_TYPE_ResearchLab:
			tempSprite->setTexture(IMG_BUILDING_ResearchLab_Broken);
			break;
		case BUILDING_TYPE_MineFactory:
			tempSprite->setTexture(IMG_BUILDING_MineFactory_Broken);
			break;
		case BUILDING_TYPE_WoodFactory:
			tempSprite->setTexture(IMG_BUILDING_WoodFactory_Broken);
			break;
		case BUILDING_TYPE_ArrowTower:
			tempSprite->setTexture(IMG_BUILDING_ArrowTower_Broken);
			break;
		case BUILDING_TYPE_Cannon:
			tempSprite->setTexture(IMG_BUILDING_Cannon_Broken);
			break;
		case BUILDING_TYPE_Laser:
			tempSprite->setTexture(IMG_BUILDING_Laser_Broken);
			break;
		default:
			break;
	}

	return tempSprite;
};

//获取图片的名称
string GlobalManager::getBuildingIMGName(int type) {

	auto tempName = "";
	switch(type) {
		case BUILDING_TYPE_BaseTower:
			tempName = IMG_BUILDING_BaseTower;
			break;
		case BUILDING_TYPE_Raider:
			tempName = IMG_BUILDING_Raider;
			break;
		case BUILDING_TYPE_HeroHotel:
			tempName = IMG_BUILDING_HeroHotel;
			break;
		case BUILDING_TYPE_Camp:
			tempName = IMG_BUILDING_Camp;
			break;
		case BUILDING_TYPE_ResearchLab:
			tempName = IMG_BUILDING_ResearchLab;
			break;
		case BUILDING_TYPE_MineFactory:
			tempName = IMG_BUILDING_MineFactory;
			break;
		case BUILDING_TYPE_WoodFactory:
			tempName = IMG_BUILDING_WoodFactory;
			break;
		case BUILDING_TYPE_ArrowTower:
			tempName = IMG_BUILDING_ArrowTower;
			break;
		case BUILDING_TYPE_Cannon:
			tempName = IMG_BUILDING_Cannon;
			break;
		case BUILDING_TYPE_Laser:
			tempName = IMG_BUILDING_Laser;
			break;
		default:
			break;
	}
	return tempName;
};

// 点是否在菱形内
bool GlobalManager::isPointInDiamond(Vec2 centerPoint, Size size, Vec2 p) {

	Vec2 p1 = centerPoint + Vec2(0, size.height/2);
	Vec2 p2 = centerPoint + Vec2(size.width/2, 0);
	Vec2 p3 = centerPoint + Vec2(0, -size.height/2);
	Vec2 p4 = centerPoint + Vec2(-size.width/2, 0);

	bool a = xmult(p, p2, p1) > 0;
	bool b = xmult(p, p3, p2) > 0;
	bool c = xmult(p, p4, p3) > 0;
	bool d = xmult(p, p1, p4) > 0;

	return (a==b)&&(a==c)&&(a==d);
};

// 叉乘
float GlobalManager::xmult(Vec2 p1, Vec2 p2, Vec2 p0) {

	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
};

//瓦片是否越界
bool GlobalManager::isOutMap(Vec2 pos) {
	
	Vec2 tiledPos = getTiledPos(pos);
	if(tiledPos.x < -EPS || tiledPos.x > TILED_TOTAL_X ||
	   tiledPos.y < -EPS || tiledPos.y > TILED_TOTAL_Y) {
		return true;
	}
	return false;
};

// 地面是否被占据
bool GlobalManager::isCovered(Vec2 pos) {

	int x = pos.x;
	int y = pos.y;
	if(x<0 || x>TILED_TOTAL_X ||
	   y<0 || y>TILED_TOTAL_Y) {
		return true;
	}

	return (_cover[x][y]!=0);
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

