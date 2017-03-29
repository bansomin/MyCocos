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
	void createPlayer();		//����player
	void createPlayerHpBar();	//����Ѫ��
	void rotateArrow(Point touchPos);	//������ת
    void initRotateArrow (Point touchPos);   //���ĳ�ʼ��λ��

	void createAndShootArrow (Point touchPos);	//�μ�����
	void shootArrow ();	//������
	void finishRunAction ();

	void update (float dt);

	CC_SYNTHESIZE(int, playerHp, playerHpFunc);
	CC_SYNTHESIZE(bool, startDraw, startDrawFunc);
	CC_SYNTHESIZE(bool, isRunAction, isRunActionFunc);

private:
	Size Wsize;

	Vec2 playerPos;         //��ɫ��tmx��ͼ�ϵ�λ��
	Size playerSize;

	Sprite* hpBg;			//Ѫ��
	Sprite* playerBody;		//Hero
	Sprite* playerArrow;	//��

	ProgressTimer* hpBar;   //Ѫ����

	DrawNode* drawNode;		//����
	QuadBezierConfig bezier;
};


#endif	//!__Arrow_Player__


