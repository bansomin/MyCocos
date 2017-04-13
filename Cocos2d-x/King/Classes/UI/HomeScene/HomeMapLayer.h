/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: Íæ¼Ò³Ç³Ø
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
	void addMap();
	void setHudLayer(Layer* layer);

private:
	Size _Wsize;
	Vec2 _origin;

	TMXTiledMap* _tileMap;	//ÍßÆ¬µØÍ¼
	Layer* _bgLayer;		//±³¾°²ã
	Layer* _hubLayer;		//
	Sprite* _bgMap;			//±³¾°Í¼	

	TextureCache*_cache;	//ÎÆÀí»º´æ
};

#endif // _HOMEMAPLAYER_H__

