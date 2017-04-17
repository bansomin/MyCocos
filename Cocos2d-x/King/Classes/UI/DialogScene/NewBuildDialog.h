/*************************BEGIN****************************************************
Created by HAO on 2017/04/14
BRIEF	:	建筑
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __NEWBUILDDIALOG_H_
#define __NEWBUILDDIALOG_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace cocostudio;
using namespace ui;
using namespace std;

class NewBuildDialog : public Layer {
	
public:
	static NewBuildDialog* create();
	virtual bool init();

public:
	void showDialog();
	void hideDialog();
	void removeDialog();
	void buildCallback(Ref* sender, Widget::TouchEventType type);	//新建回调
	void closeCallback(Ref *sender, Widget::TouchEventType type); //关闭按钮回调

	void showNotice(string info);

private:
	Size _Wsize;

};

#endif // __NEWBUILDDIALOG_H_
