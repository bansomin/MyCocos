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
	__Dictionary* _chnString;				//����

public:
	int _townID;
	int _cover[40][40];

	bool _newBuild;


public:
	int getTimeStamp();						// ��ȡʱ���
	string getIntToStr(int value);			//intתstring
	int getStrToInt(string value);			//stringתint
	const char* getCN(string key);			//�����������

	void clearCovered();					// ���ռ�����
	void setCoverd(Vec2 pos, int delta);	// ռ��/�ͷŵ��棺delta=1ռ�ݣ�=-1�ͷ�
											
	Vec2 getMapPos(Vec2 pos);				// ��Ƭ���� ת ��ͼ����
	Vec2 getTiledPos(Vec2 pos);				// ��ͼ���� ת ��Ƭ����

	//�����л�
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
