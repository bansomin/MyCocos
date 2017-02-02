#pragma once

#ifndef __SHARESCENE_SCENE_H__
#define __SHARESCENE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

class ShareScene : public Layer {

	public:
	ShareScene();
	~ShareScene();
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(ShareScene);

	public:
	void backFunc(Ref* pSender);
	void Share_QQ(Ref* pSender);
	void Share_WC(Ref* pSender);
	void Share_WCC(Ref* pSender);
	void Share_QQZ(Ref* pSender);
	void Share_SINA(Ref* pSender);
	void Share_FACEBOOK(Ref* pSender);
	void Share_TWITTER(Ref* pSender);
	void Share_MulPlatform(Ref* pSender);

};

#endif //__SHARESCENE_SCENE_H__
