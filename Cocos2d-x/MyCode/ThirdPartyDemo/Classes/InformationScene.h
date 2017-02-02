#pragma once

#ifndef __INFORMATIONSCENE_SCENE_H__
#define __INFORMATIONSCENE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

class InformationScene : public Layer {

	public:

	InformationScene();
	~InformationScene();
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(InformationScene);

	public:

	void backFunc(Ref* pSender);
	void GetInfo_QQ(Ref* pSender);
	void GetInfo_WC(Ref* pSender);
	void GetInfo_SINA(Ref* pSender);

};

#endif //__INFORMATIONSCENE_SCENE_H__
