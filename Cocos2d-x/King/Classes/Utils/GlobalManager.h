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

	Vec2 getSpaceTiled();                   // ��ȡ�յ�
	ValueVector getNextSpace(Vec2 pos);     // �����ȡ��ǰλ����Χ�Ŀյ�

	Vec2 getMapPos(Vec2 pos);				// ��Ƭ���� ת ��ͼ����
	Vec2 getTiledPos(Vec2 pos);				// ��ͼ���� ת ��Ƭ����

	Vec2 getMapDelta(int index);            // ������Ƭ�����ƫ�Ʒ��򣬻�ȡ��ͼ�����ƫ����
											  
	Sprite* getBuildingIMG(int type);		// ��ȡ������ͼƬ��
	Sprite* getBuildingBrokenIMG(int type);  // ��ȡ�������ݻٺ��ͼƬ��

	bool isPointInDiamond(Vec2 centerPoint, Size size, Vec2 p);// ���Ƿ���������
	float xmult(Vec2 p1, Vec2 p2, Vec2 p0);
	
	bool isOutMap(Vec2 pos);				//��Ƭ�Ƿ�Խ��
	bool isCovered(Vec2 pos);				// �����Ƿ�ռ��

	//�����л�
	void enterWorldScene();
	void enterHomeScene();
	void enterChapterScene(int townID, int type);

};

#endif // !_GLOBALMANAGER_H__
