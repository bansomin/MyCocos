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

public:
	int getTimeStamp();						// 获取时间戳
	string getIntToStr(int value);			//int转string
	int getStrToInt(string value);			//string转int

	//场景切换
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
