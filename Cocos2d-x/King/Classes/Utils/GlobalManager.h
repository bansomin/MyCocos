/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: 界面统一管理文件
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _GLOBALMANAGER_H__
#define _GLOBALMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

#define GM() GlobalManager::getInstance()

class GlobalManager : public Ref {

public:
	GlobalManager();
	~GlobalManager();
	virtual bool init();
	static GlobalManager* getInstance();

private:
	static GlobalManager* _instance;
	__Dictionary* _chnString;				//中文

public:
	int _townID;
	int _cover[40][40];

	bool _newBuild;

public:
	int getTimeStamp();						// 获取时间戳
	string getIntToStr(int value);			//int转string
	int getStrToInt(string value);			//string转int
	const char* getCN(string key);			//解决中文乱码

	void clearCovered();					// 清空占地情况
	void setCoverd(Vec2 pos, int delta);	// 占据/释放地面：delta=1占据，=-1释放

	Vec2 getSpaceTiled();                   // 获取空地
	ValueVector getNextSpace(Vec2 pos);     // 随机获取当前位置周围的空地

	Vec2 getMapPos(Vec2 pos);				// 瓦片坐标 转 地图坐标
	Vec2 getTiledPos(Vec2 pos);				// 地图坐标 转 瓦片坐标

	Vec2 getMapDelta(int index);            // 根据瓦片坐标的偏移方向，获取地图坐标的偏移量
											  
	Sprite* getBuildingIMG(int type);		// 获取建筑的图片名
	Sprite* getBuildingBrokenIMG(int type);  // 获取建筑被摧毁后的图片名

	bool isPointInDiamond(Vec2 centerPoint, Size size, Vec2 p);// 点是否在菱形内
	float xmult(Vec2 p1, Vec2 p2, Vec2 p0);
	
	bool isOutMap(Vec2 pos);				//瓦片是否越界
	bool isCovered(Vec2 pos);				// 地面是否被占据

	//场景切换
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
