/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: ����ͳһ�����ļ�
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _GLOBALMANAGER_H__
#define _GLOBALMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;

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
	//�����л�
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
