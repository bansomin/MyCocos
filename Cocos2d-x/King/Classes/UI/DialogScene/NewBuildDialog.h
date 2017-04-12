

#ifndef __NewBuildDialog_H__
#define __NewBuildDialog_H__

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
	void buildCallback(Ref* sender, Widget::TouchEventType type);	//�½��ص�
	void closeCallback(Ref *sender, Widget::TouchEventType type); //�رհ�ť�ص�

	void showNotice(string info);

private:
	Size _Wsize;

};

#endif // __NewBuildDialog_H__
