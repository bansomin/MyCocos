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
											
	Vec2 getMapPos(Vec2 pos);				// 瓦片坐标 转 地图坐标
	Vec2 getTiledPos(Vec2 pos);				// 地图坐标 转 瓦片坐标

	//场景切换
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
