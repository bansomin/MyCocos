/*************************BEGIN****************************************************
Created by HAO on 2017/04/06
BRIEF	: ��ҳǳ�
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

	TMXTiledMap* _tileMap;	//��Ƭ��ͼ
	Layer* _bgLayer;		//������
	Layer* _hubLayer;		//
	Sprite* _bgMap;			//����ͼ	

	TextureCache*_cache;	//������
};

#endif // _HOMEMAPLAYER_H__

