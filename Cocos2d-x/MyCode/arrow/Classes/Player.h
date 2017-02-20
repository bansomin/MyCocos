/**
* Created by HAO on 2016/9/2.
*/

#pragma once
#ifndef __Arrow_Player__
#define __Arrow_Player__

#include "cocos2d.h"

#include "ArrowBezier.h"

USING_NS_CC;

class Player : public Sprite {

public:
	Player();
	~Player();

	virtual bool init(Vec2 pos);
	static Player* create(Vec2 pos);

public:
	void createPlayer();		//创建player
	void createPlayerHpBar();	//创建血条
	void rotateArrow(Point touchPos);	//箭的旋转
    void initRotateArrow (Point touchPos);   //箭的初始化位置

	void createAndShootArrow (Point touchPos);	//拔箭动作
	void shootArrow ();	//创建箭
	void finishRunAction ();

	void update (float dt);

	CC_SYNTHESIZE(int, playerHp, playerHpFunc);
	CC_SYNTHESIZE(bool, startDraw, startDrawFunc);
	CC_SYNTHESIZE(bool, isRunAction, isRunActionFunc);

private:
	Size Wsize;

	Vec2 playerPos;         //角色在tmx地图上的位置
	Size playerSize;

	Sprite* hpBg;			//血条
	Sprite* playerBody;		//Hero
	Sprite* playerArrow;	//箭

	ProgressTimer* hpBar;   //血槽条

	DrawNode* drawNode;		//画线
	QuadBezierConfig bezier;
};


#endif	//!__Arrow_Player__


