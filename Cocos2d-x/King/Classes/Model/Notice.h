/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	:	信息提示
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __NOTICE_H__
#define __NOTICE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class Notice:public Node {

public:
	static Notice* create(string info);
	virtual bool init(string info);

public:
	void showUI(string info);
	void remove();

private:
	Size _Wsize;
};

#endif // !__NOTICE_H__
