
/*************************BEGIN**************************************************** 
    			Created by HAO on 2016/9/7
    BRIEF	: 	GameScene.h
    VERSION	: 
    HISTORY	:
***************************END****************************************************/
#pragma once

#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"

#include "ChooseLayer.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace ui;		//ע������֮���˳��

typedef enum {
	GROUND = 1,		//�ݵ�
	CROPS = 2,
	CROPS_HARVEST = 3,
	OTHER = 4
} TileType;


class GameScene : public Layer {

public:
	GameScene ();
	~GameScene ();
	static Scene* createScene ();
	virtual bool init ();
	CREATE_FUNC (GameScene);

public:
	void addUI ();
	void checkTileType ();	//���ؿ�����
	void initMapLayerFunc ();
	Vec2 convertTotileCoord (Vec2 position);		//��Ƭ��ͼ����ת��
	Vec2 convertToScreenCoord (Vec2 tilePoint);
	void moveItemCheckFunc (Vec2 position, int tag);	//����Ƿ�ɷ���Ʒ

	void clickShopBtnFunc (Ref* sender, Widget::TouchEventType type);	//���shop��ť
	void selectItemFunc (Ref* pSender, Widget::TouchEventType type);	//ѡ����Ʒ

	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);	

	//update
	void updatePress (float dt);

private:

	bool longPress;

	TileType tiletype;

	Size Wsize;
	Vec2 origin;

	Sprite* tempSpr;	//�ƶ��е���ʱͼƬ
	Sprite* bg_tree;
	Sprite* bg_grass;

	Layer* maplayer;

	
	bool	isOut;		//panel_shop�Ƿ񵯳���־
	bool	isCanBulid;	//�Ƿ���Դ�����Ʒ

	Layer* rootLayer;	//��
	Layout* panel_game;	//game����
	Layout* panel_shop;	//shop����
	Layout* panel_item;	//item����

	//map
	Size mapSize;
	TMXTiledMap* map;			//map
	TMXLayer* map_bglayer;		//map�е�bgLayer
	TMXLayer* map_tipslayer;	//map�е�tipsLayer
	TMXLayer* map_goodslayer;	//map�е�goodsLayer

	Vec2 touchObjectPos;//����λ��
	Vec2 currPos;		//��ǰtilePoint
	Vec2 perPos;		//��ǰtilePoint

	ScrollView* scrollview;

	Button* btn_shop;
};

#endif /!__GAMESCENE_SCENE_H__
