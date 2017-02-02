#include "InformationScene.h"

#include <map>
#include <vector>

#include "UserInfoScene.h"
#include "HelloWorldScene.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_UM_SOCIAL;

InformationScene::InformationScene(){

};

InformationScene::~InformationScene() {

};

Scene* InformationScene::createScene() {

	auto scene = Scene::create();
	auto layer = InformationScene::create();
	scene->addChild(layer);

	return scene;
};

bool InformationScene::init() {

	if (!Layer::init()){
		return false;
	}

	auto Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//返回
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(InformationScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height - 50));
	itemBack->setScale(1.5);

	auto dis = 200;

	//获取QQ信息
	auto qqItem = MenuItemImage::create("QQ.png", "QQ.png", CC_CALLBACK_1(InformationScene::GetInfo_QQ, this));
	qqItem->setPosition(Wsize.width/2, Wsize.height - 200);
	qqItem->setScale(1.5, 1.6);

	//微信
	auto wcItem = MenuItemImage::create("WC.png", "WC.png", CC_CALLBACK_1(InformationScene::GetInfo_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY()-dis);
	wcItem->setScale(1.5, 1.6);

	//新浪
	auto sinaItem = MenuItemImage::create("Sina.png", "Sina.png", CC_CALLBACK_1(InformationScene::GetInfo_SINA, this));
	sinaItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	sinaItem->setScale(1.5, 1.6);

	auto menu = Menu::create(itemBack, qqItem, wcItem, sinaItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void InformationScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

void getCallback(int platform, int stCode, map<string, string>& data) {
	log("inforCallback.");

	log("********************************** Code : %d", stCode);
	if(stCode==200) {
		log("Access to information successfully.");

		/*
		map<string, string>::iterator nickname;
		nickname = data.find("screen_name");
		log("**************************************** nickname : %s", nickname->second.c_str());
		*/
		UserDefault* userdef = UserDefault::sharedUserDefault();
		userdef->setStringForKey("token", data.find("access_token")->second.c_str());
		userdef->setStringForKey("uid", data.find("uid")->second.c_str());	

		userdef->setStringForKey("nickname", data.find("screen_name")->second.c_str());	//保存昵称
		userdef->setStringForKey("sex", data.find("gender")->second.c_str());	//保存性别
		userdef->setStringForKey("headimageurl", data.find("profile_image_url")->second.c_str());	//保存头像网址

		userdef->setStringForKey("province", data.find("province")->second.c_str());	
		userdef->setStringForKey("city", data.find("city")->second.c_str());

		Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, UserInfoScene::createScene()));
	}
	else if(stCode==0) {
		log("Failed to get information.");
	}
	else if(stCode==-1) {
		log("Termination of access to information.");
	}
	else {
		log("An unknown error.");
	}

	map<string, string>::iterator it = data.begin();
	for(; it!=data.end(); ++it) {
		log("#### DATA %s -> %s.", it->first.c_str(), it->second.c_str());
	}
}

void InformationScene::GetInfo_QQ(Ref* pSender) {
	log("GetInfo_QQ");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->getPlatformInfo(QQ, auth_selector(getCallback));
};

void InformationScene::GetInfo_WC(Ref* pSender) {
	log("GetInfo_WC");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->getPlatformInfo(WEIXIN, auth_selector(getCallback));
};

void InformationScene::GetInfo_SINA(Ref* pSender) {
	log("GetInfo_SINA");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->getPlatformInfo(SINA, auth_selector(getCallback));
};
