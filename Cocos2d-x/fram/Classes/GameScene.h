
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
using namespace ui;		//注意两者之间的顺序

typedef enum {
	GROUND = 1,		//草地
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
	void checkTileType ();	//检测地块类型
	void initMapLayerFunc ();
	Vec2 convertTotileCoord (Vec2 position);		//瓦片地图坐标转换
	Vec2 convertToScreenCoord (Vec2 tilePoint);
	void moveItemCheckFunc (Vec2 position, int tag);	//检测是否可放物品

	void clickShopBtnFunc (Ref* sender, Widget::TouchEventType type);	//点击shop按钮
	void selectItemFunc (Ref* pSender, Widget::TouchEventType type);	//选择商品

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

	Sprite* tempSpr;	//移动中的临时图片
	Sprite* bg_tree;
	Sprite* bg_grass;

	Layer* maplayer;

	
	bool	isOut;		//panel_shop是否弹出标志
	bool	isCanBulid;	//是否可以创建物品

	Layer* rootLayer;	//根
	Layout* panel_game;	//game容器
	Layout* panel_shop;	//shop容器
	Layout* panel_item;	//item容器

	//map
	Size mapSize;
	TMXTiledMap* map;			//map
	TMXLayer* map_bglayer;		//map中的bgLayer
	TMXLayer* map_tipslayer;	//map中的tipsLayer
	TMXLayer* map_goodslayer;	//map中的goodsLayer

	Vec2 touchObjectPos;//触摸位置
	Vec2 currPos;		//当前tilePoint
	Vec2 perPos;		//先前tilePoint

	ScrollView* scrollview;

	Button* btn_shop;
};

#endif /!__GAMESCENE_SCENE_H__
