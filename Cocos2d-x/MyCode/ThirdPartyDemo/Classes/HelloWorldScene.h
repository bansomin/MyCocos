#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//授权
	void authorizeFunc(Ref* pSender);
	//分享
	void shareFunc(Ref* pSender);
	//获取信息
	void informationFunc(Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
