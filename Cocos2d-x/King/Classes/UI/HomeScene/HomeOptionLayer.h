/*************************BEGIN****************************************************
Created by HAO on 2017/04/12
BRIEF	:	
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _HOMEOPTIONLAYER_H__
#define _HOMEOPTIONLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

//use
#include "Model\BuildingSprite.h"
//#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
//using namespace cocostudio;
using namespace ui;
//using namespace std;

class HomeOptionLayer : public Layer {

public:
	HomeOptionLayer();
	~HomeOptionLayer();
	virtual bool init();
	CREATE_FUNC(HomeOptionLayer);

public:
	void loadData();
	void loadUI();
	void show(BuildingSprite* spr);
	void hide(BuildingSprite* spr);
	void showAction(Button* btn, float delay);
	void hideAction(Button* btn, float delay);

	void infoCallback(Ref* sender, Widget::TouchEventType type);
	void enterCallback(Ref* sender, Widget::TouchEventType type);
	void upGradeCallback(Ref* sender, Widget::TouchEventType type);

private:
	Size _Wsize;

	int _h;					//
	Text* label;
	Text* _headquarters;	//˾�

	Button* btnInfo;
	Button* btnEnter;
	Button* btnUpgrade;

	BuildingSprite* _buildingSprite;
};

#endif // _HOMEOPTIONLAYER_H__
