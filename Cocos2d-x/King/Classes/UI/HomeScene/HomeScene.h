/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: Íæ¼Ò³Ç³Ø
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _HOMESCENE_H__
#define _HOMESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HomeScene : public Layer {

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HomeScene);

public:
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

private:
	Size _Wsize;
	Vec2 _origin;

	Layer* _bgLayer;	//±³¾°²ã
	Sprite* _bgMap;		//±³¾°Í¼	
};

#endif // _HOMESCENE_H__
