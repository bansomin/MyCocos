/*************************BEGIN****************************************************
Created by HAO on 2017/04/18
BRIEF	: 建设进度条
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __BUILDPROCESS_H_
#define __BUILDPROCESS_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Model\BuildingSprite.h"
using namespace cocos2d;
using namespace ui;

class BuildProcess : public Sprite {

public:
	virtual bool init(BuildingSprite* spr);
	static BuildProcess* create(BuildingSprite* spr);

public:
	void showUI();
	void remove();
	void update(float dt);
	void finish();

	private:
	float _delta;
	Text* _timeRest;
	LoadingBar* _loadingBar;
	BuildingSprite* _buildingSprite;
};

#endif // !__BUILDPROCESS_H_
