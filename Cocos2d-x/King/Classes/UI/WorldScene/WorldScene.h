/*************************BEGIN****************************************************
Created by HAO on 2017/04/07
BRIEF	:  ¿ΩÁµÿÕº
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __WORLDSCENE_H__
#define __WORLDSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class WorldScene : public Layer {

public:
	static Scene* createScene();
	virtual bool init(); 
	CREATE_FUNC(WorldScene);

};

#endif // __WORLDSCENE_H__
