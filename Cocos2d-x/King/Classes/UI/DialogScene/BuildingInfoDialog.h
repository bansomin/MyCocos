/*************************BEGIN****************************************************
Created by HAO on 2017/04/07
BRIEF	:	������Ϣ��
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __BUILDINGINFODIALOG_H_
#define __BUILDINGINFODIALOG_H_

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "Model\BuildingSprite.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;

class BuildingInfoDialog : public Layer {

public:
	static BuildingInfoDialog* create(BuildingSprite* spr);
	virtual bool init(BuildingSprite* spr);

public:
	void removeFunc();		//�Ƴ�		
	void showInfo();		//��������
	void showDialog();		//��ʾ��Ϣ��
	void hideDialog();		//������Ϣ��
	void btnCloseFunc(Ref* sender, Widget::TouchEventType type);

private:
	Size _Wsize;
	TextureCache*_cache;	//������
	BuildingSprite* _buildingSprite;

};

#endif // __BUILDINGINFODIALOG_H_


