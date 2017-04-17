/*************************BEGIN****************************************************
Created by HAO on 2017/04/07
BRIEF	:	建筑信息栏
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
	void removeFunc();		//移除		
	void showInfo();		//加载数据
	void showDialog();		//显示信息栏
	void hideDialog();		//隐藏信息栏
	void btnCloseFunc(Ref* sender, Widget::TouchEventType type);

private:
	Size _Wsize;
	TextureCache*_cache;	//纹理缓存
	BuildingSprite* _buildingSprite;

};

#endif // __BUILDINGINFODIALOG_H_


