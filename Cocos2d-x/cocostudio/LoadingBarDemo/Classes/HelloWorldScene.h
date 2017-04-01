#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//加载cocostudio
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	Node* _loadingBarNode;		//加载层
	LoadingBar* _loadingBar;	//进度条
	Text* _text;				//文字

public:
	void update(float dt);  //帧循环调用方法
};

#endif // __HELLOWORLD_SCENE_H__
