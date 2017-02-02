#pragma once

#ifndef __AUTHORIZE_SCENE_H__
#define __AUTHORIZE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;

class AuthorizeScene : public Layer {

	public:
	AuthorizeScene();
	~AuthorizeScene();
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(AuthorizeScene);

	public:
	void backFunc(Ref* pSender);

	void Auth_QQ(Ref* pSender);
	void Auth_QQCancel(Ref* pSender);

	void Auth_WC(Ref* pSender);
	void Auth_WCCancel(Ref* pSender);

	void Auth_SINA(Ref* pSender);
	void Auth_SINACancel(Ref* pSender);

	void Auth_FACEBOOK(Ref* pSender);
	void Auth_FACEBOOKCancel(Ref* pSender);

	void Auth_Twitter(Ref* pSender);
	void Auth_TwitterCancel(Ref* pSender);

};

#endif //__AUTHORIZE_SCENE_H__
