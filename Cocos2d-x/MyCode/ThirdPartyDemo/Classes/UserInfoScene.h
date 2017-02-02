#pragma once

#ifndef __USERINFO_SCENE__
#define __USERINFO_SCENE__

/**
 * Created by HAO on 2016/12/30.
 */

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

//#include "iconv.h"

//#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//#include "../cocos2d/libiconv/include/iconv.h"
//#endif

//#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
//#pragma comment(lib, "libiconv.lib")
//#endif

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace cocos2d;
using namespace network;

class UserInfoScene : public Layer{

public:
	UserInfoScene ();
	~UserInfoScene ();
	static Scene* createScene ();
	virtual bool init ();
	CREATE_FUNC(UserInfoScene);

private:
	Size Wsize;

	string _path;
	Sprite* _headSpr;
	Sprite* _tempSpr;
	UserDefault* _userdef;
	
public:
	static void downloadHttpImage(Object* obj, const char* url);	//从url中获取图片
	void getImageCompleted(HttpClient* sender, HttpResponse* response);	//将图片保存到本地
	void createHeadImage(Texture2D* texture);

	int GBKToUTF8(string & gbkStr, const char* toCode, const char* fromCode);

public:
	void backFunc(Ref* pSender);

};

#endif//__USERINFO_SCENE__