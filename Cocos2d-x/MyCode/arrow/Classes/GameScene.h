/**
* Created by HAO on 2016/9/2.
*/

#pragma once
#ifndef __Arrow_GameScene__
#define __Arrow_GameScene__

#include "cocos2d.h"

#include "Player.h"

using namespace std;
using namespace cocos2d;

class GameScene : public Layer {

public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	static Scene* createScene();

private:
	Size Wsize;

	Player* player;

	TMXTiledMap* map;

	Point preTouchPoint;
	Point curTouchPoint;

public:
	void addBgFunc();
	Animation* createAnimation(string prefixName, int framesNum, float delay);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

private:
	bool isMoved;

};

#endif //!__Arrow_GameScene__