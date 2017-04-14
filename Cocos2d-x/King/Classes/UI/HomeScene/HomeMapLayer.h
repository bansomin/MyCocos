/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: 玩家城池
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _HOMEMAPLAYER_H__
#define _HOMEMAPLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

class HomeMapLayer : public Layer {

public:
	HomeMapLayer();
	~HomeMapLayer();
	virtual bool init();
	CREATE_FUNC(HomeMapLayer);

public:

	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

public:
	void addMap();					//加载地图
	void addFloor();				//加载地板
	void addRobots();				//加载小机器人
	void addObscale();				//加载花

	void addTouch();				//添加触摸

	void setHudLayer(Layer* layer);

private:
	Size _Wsize;
	Vec2 _origin;

	Layer* _bgLayer;		//背景层
	Layer* _hubLayer;		//
	Sprite* _bgMap;			//背景图	

	TextureCache*_cache;	//纹理缓存
};

#endif // _HOMEMAPLAYER_H__

