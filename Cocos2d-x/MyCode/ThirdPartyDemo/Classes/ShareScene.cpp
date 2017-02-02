#include "ShareScene.h"

#include "HelloWorldScene.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_UM_SOCIAL;

ShareScene::ShareScene() {

};

ShareScene::~ShareScene() {

};

Scene* ShareScene::createScene() {

	auto scene = Scene::create();
	auto layer = ShareScene::create();
	scene->addChild(layer);

	return scene;
};

bool ShareScene::init() {

	if (!Layer::init()){
		return false;
	}

	auto Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//返回
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(ShareScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height-50));
	itemBack->setScale(1.5);

	auto dis = 120;

	//QQ分享
	auto qqItem = MenuItemImage::create("shareQQ.png", "shareQQ.png", CC_CALLBACK_1(ShareScene::Share_QQ, this));
	qqItem->setPosition(Wsize.width/2, Wsize.height-200);
	qqItem->setScale(1.5, 1.6);

	//微信分享
	auto wcItem = MenuItemImage::create("shareWC.png", "shareWC.png", CC_CALLBACK_1(ShareScene::Share_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);

	//facebook
	auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(ShareScene::Share_FACEBOOK, this));
	facebookItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);

	//新浪分享
	auto sinaItem = MenuItemImage::create("shareSina.png", "shareSina.png", CC_CALLBACK_1(ShareScene::Share_SINA, this));
	sinaItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY() - dis);
	sinaItem->setScale(1.5, 1.6);

	//QQ空间分享
	auto qqzItem = MenuItemImage::create("shareQQZ.png", "shareQQZ.png", CC_CALLBACK_1(ShareScene::Share_QQZ, this));
	qqzItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	qqzItem->setScale(1.5, 1.6);

	//Twitter
	auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(ShareScene::Share_TWITTER, this));
	twitterItem->setPosition(qqzItem->getPositionX(), qqzItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);

	//MulPlatform
	auto mulItem = MenuItemImage::create("socialshare.png", "socialshare.png", CC_CALLBACK_1(ShareScene::Share_MulPlatform, this));
	mulItem->setPosition(twitterItem->getPositionX(), twitterItem->getPositionY()-dis);
	mulItem->setScale(1.5, 1.6);

	//WeChatC
	auto wccItem = MenuItemImage::create("shareWCC.png", "shareWCC.png", CC_CALLBACK_1(ShareScene::Share_WCC, this));
	wccItem->setPosition(mulItem->getPositionX(), mulItem->getPositionY()-dis);
	wccItem->setScale(1.5, 1.6);

	auto menu = Menu::create(itemBack, qqItem, wcItem, sinaItem, facebookItem, qqzItem, twitterItem, mulItem, wccItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void ShareScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

/*
* 分享回调
* @param platform 要分享到的目标平台
* @param stCode 返回码, 200代表分享成功, 100代表开始分享
* @param errorMsg 分享失败时的错误信息,android平台没有错误信息
*/
void shareCallback(int platform, int stCode, string& errorMsg) {
	log("shareCallback");

	log("********************************** Code : %d", stCode);
	if(stCode==100) {
		log("Share begin.");

	}
	else if(stCode==200) {
		log("Share success.");

	}
	else if(stCode==-1) {
		log("Cancel the share.");

	}
	else {
		log("An unknown error.");
	}

}

void ShareScene::Share_QQ(Ref* pSender) {
	log("Share_QQ");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShareAndroid(3,
							"SinglePlatformTest", "QQShare", "http://pre.im/p/bansomin", "http://dev.umeng.com/images/tab2_1.png",
							share_selector(shareCallback));
};

void ShareScene::Share_WC(Ref* pSender) {
	log("Share_WC");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(1,
					 "SinglePlatformTest201612", "WeChatShare", "http://pre.im/p/bansomin", "http://dev.umeng.com/images/tab2_1.png",
					 share_selector(shareCallback));
};

void ShareScene::Share_WCC(Ref* pSender) {
	log("Share_WCC");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(2,
					 "SinglePlatformTest201612", "WeChatCircleShare", "http://pre.im/p/bansomin", "http://dev.umeng.com/images/tab2_1.png",
					 share_selector(shareCallback));
};

void ShareScene::Share_SINA(Ref* pSender) {
	log("Share_SINA");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(0,
					 "SinglePlatformTest201612", "SinaShare", "http://pre.im/p/bansomin", "http://dev.umeng.com/images/tab2_1.png",
					 share_selector(shareCallback));
};

void ShareScene::Share_FACEBOOK(Ref* pSender) {
	log("Share_FACEBOOK");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(11,
					 "SinglePlatformTest201612", "FacebookShare", "https://twitter.com/good091231", "https://www.facebook.com/photo.php?fbid=114876222342433&set=a.104314560065266.1073741826.100014601664129&type=3&theater",
					 share_selector(shareCallback));
};

void ShareScene::Share_QQZ(Ref* pSender) {
	log("Share_QQZ");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(4,
					 				 "SinglePlatformTest201612", "QzoneShare", "http://pre.im/p/bansomin", "http://dev.umeng.com/images/tab2_1.png",
					 				 share_selector(shareCallback));
};

void ShareScene::Share_TWITTER(Ref* pSender) {
	log("Share_TWITTER");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->directShare(12,
					 "SinglePlatformTest201612", "TwitterShare", "https://www.facebook.com/profile.php?id=100014601664129", "https://pbs.twimg.com/profile_images/810858623643459585/ki6R8vYM.jpg",
					 share_selector(shareCallback));
};

void ShareScene::Share_MulPlatform(Ref* pSender) {
	log("Share_MulPlatform");

	CCUMSocialSDK *sdk = CCUMSocialSDK::create( );
	vector<int>* platforms = new vector<int>();
	platforms->push_back(QQ);
	platforms->push_back(QZONE);
	platforms->push_back(SINA);
	platforms->push_back(WEIXIN);
	platforms->push_back(WEIXIN_CIRCLE);
	platforms->push_back(TWITTER);
	platforms->push_back(FACEBOOK);
	platforms->push_back(SMS);

	sdk->openShare(platforms, "MultiplePlatform201612", "FromBoardShare" ,"https://avatars1.githubusercontent.com/u/11844960?v=3&u=c00034ba9176141ee41257cee748b6a87b9908c0&s=400","http://pre.im/p/bansomin",share_selector(shareCallback));

};
