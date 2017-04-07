/*************************BEGIN****************************************************
Created by HAO on 2017/04/05
BRIEF	: ���ؽ��棨��������ʾ��
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//������
//use
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
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
	Node* _rootNode;				//���ز�
	LoadingBar* _loadingBar;	//������
	Text* _text;				//����

	//int resCount;				//��Դ��Ŀ

public:
	void loadingRes();
	void loadResourcesUpdate();
	void loadResourcesUpdateAmr(float dt);
	void updateLoadingPrg();
	void changeScene();		//������ת
};

#endif // __HELLOWORLD_SCENE_H__
