/*************************BEGIN****************************************************
Created by HAO on 2017/04/18
BRIEF	:	����������
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __BUILDINGUPGRADEDIALOG_H_
#define __BUILDINGUPGRADEDIALOG_H_

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "Model\BuildingSprite.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class BuildingUpgradeDialog : public Layer {

	public:
	static BuildingUpgradeDialog* create(BuildingSprite* spr);
	virtual bool init(BuildingSprite* spr);

	public:
	void removeFunc();		//�Ƴ�		
	void addData();			//��������
	void showDialog();		//��ʾ��Ϣ��
	void hideDialog();		//������Ϣ��
	void showNowInfo();	//��ǰ��Ϣ
	void showNextInfo();	//��������Ϣ
	void showRequire();		//��Ҫ����Դ��Ŀ
	void upgradeFunc(Ref* sender, Widget::TouchEventType type);
	void btnCloseFunc(Ref* sender, Widget::TouchEventType type);

	private:
	Size _Wsize;
	Widget* _ui;
	TextureCache*_cache;	//������
	BuildingSprite* _buildingSprite;

	int _goldRequire;
	int _woodRequire;
	int _timeRequire;

	__Dictionary* _chnStr;
};

#endif // __BUILDINGUPGRADEDIALOG_H_


