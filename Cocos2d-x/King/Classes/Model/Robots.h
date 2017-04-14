/*************************BEGIN****************************************************
Created by HAO on 2017/04/12
BRIEF	:
VERSION	:
HISTORY	:
***************************END****************************************************/
#ifndef __ROBOTS_H__
#define __ROBOTS_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace std;
//using namespace cocostudio;

class Robots : public Sprite {

public:
	virtual bool init(int index);
	static Robots* create(int index);

public:
	void loadUI(int index);
	void idle();		//ÓÆÏÐ×´Ì¬

private:

	Vec2 _pos;
	cocostudio::Armature* _arm;

};

#endif // !__ROBOTS_H__
