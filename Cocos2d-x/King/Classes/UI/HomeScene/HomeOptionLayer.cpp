#include "HomeOptionLayer.h"

#include "Utils\Config.h"
//#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"
//#include "UI\DialogScene\NewBuildDialog.h"

HomeOptionLayer::HomeOptionLayer() {

};

HomeOptionLayer::~HomeOptionLayer() {

};

bool HomeOptionLayer::init() {
	if(!Layer::init()) {
		return false;
	}

	_h = -150;
	_Wsize = Director::getInstance()->getWinSize();

	this->loadData();
	this->loadUI();

	return true;
};


void HomeOptionLayer::loadData() {

};

void HomeOptionLayer::loadUI() {

	auto _chnStr = Dictionary::createWithContentsOfFile("fonts/myString.xml");
							   
	btnInfo = Button::create(IMG_BUTTON_INFOOPT);
	btnEnter = Button::create(IMG_BUTTON_ENTEROPT);
	btnUpgrade = Button::create(IMG_BUTTON_UPGRADEOPT);

	btnInfo->setPosition(Vec2(_Wsize.width/2 - btnInfo->getContentSize().width, _h)); 
	btnEnter->setPosition(Vec2(_Wsize.width/2, _h));
	btnUpgrade->setPosition(Vec2(_Wsize.width/2 + btnUpgrade->getContentSize().width, _h)); 

	btnInfo->addTouchEventListener(CC_CALLBACK_2(HomeOptionLayer::infoCallback, this));
	btnEnter->addTouchEventListener(CC_CALLBACK_2(HomeOptionLayer::enterCallback, this));
	btnUpgrade->addTouchEventListener(CC_CALLBACK_2(HomeOptionLayer::upGradeCallback, this));

	//文字
	auto labelInfo = Text::create(((__String*)_chnStr->objectForKey("info"))->getCString(), "", 20);
	auto labelEnter = Text::create(((__String*)_chnStr->objectForKey("enter"))->getCString(), "", 20);
	auto labelUpGrade = Text::create(((__String*)_chnStr->objectForKey("update"))->getCString(), "", 20);
	//司令部
	_headquarters = Text::create(((__String*)_chnStr->objectForKey("headquarters"))->getCString(), "", 32);

	labelInfo->setPosition(Vec2(btnInfo->getContentSize().width/2, btnInfo->getContentSize().height));
	labelEnter->setPosition(Vec2(btnEnter->getContentSize().width/2, btnEnter->getContentSize().height));
	labelUpGrade->setPosition(Vec2(btnUpgrade->getContentSize().width/2, btnUpgrade->getContentSize().height));
	_headquarters->setPosition(Vec2(_Wsize.width/2, 140));

	btnInfo->addChild(labelInfo);
	btnEnter->addChild(labelEnter);
	btnUpgrade->addChild(labelUpGrade, 0, "BTNUPGRADE");
	_headquarters->setOpacity(0);

	this->addChild(btnInfo);
	this->addChild(btnEnter);
	this->addChild(btnUpgrade);
	this->addChild(_headquarters, 1);

};

//ID为设施ID
void HomeOptionLayer::show(BuildingSprite* spr) {

	_buildingSprite = nullptr;
	_buildingSprite = spr;

	btnInfo->stopAllActions();
	btnEnter->stopAllActions();
	btnUpgrade->stopAllActions();
	_headquarters->stopAllActions();

	_headquarters->setOpacity(255);
	_headquarters->setColor(Color3B::WHITE);
	string title = _buildingSprite->_name+"(等级"+GM()->getIntToStr(_buildingSprite->_level)+")";
	_headquarters->setString(title);

	//是否满级或是升级
	auto lab = (Text*)btnUpgrade->getChildByName("BTNUPGRADE");
	if(_buildingSprite->_baseLevelRequire != -1) {
		if(_buildingSprite->_buildState == BUILDING_STATE_BUILDING) {
			lab->setString("升级中");
			btnUpgrade->loadTextureNormal(IMG_BUTTON_CANTUPGRADEOPT);
		}
		else {
			lab->setString("升级");
			btnUpgrade->loadTextureNormal(IMG_BUTTON_UPGRADEOPT);
		}
	}
	else {
		lab->setString("已满级");
		btnUpgrade->loadTextureNormal(IMG_BUTTON_CANTUPGRADEOPT);
	}

	//研究所、兵营、英雄旅馆是否可进入
	if(_buildingSprite->_type != BUILDING_TYPE_Camp &&
	   _buildingSprite->_type != BUILDING_TYPE_HeroHotel &&
	   _buildingSprite->_type != BUILDING_TYPE_ResearchLab) {
		
		btnInfo->setPosition(Vec2(_Wsize.width/2-btnInfo->getContentSize().width, _h));
		btnEnter->setPosition(Vec2(_Wsize.width/2, _h));
		btnUpgrade->setPosition(Vec2(_Wsize.width/2+btnUpgrade->getContentSize().width, _h));

		showAction(btnInfo, 0.5f);
		showAction(btnUpgrade, 0.5f);
	}
	else {
		btnInfo->setPosition(Vec2(_Wsize.width/2-btnInfo->getContentSize().width, _h));
		btnEnter->setPosition(Vec2(_Wsize.width/2, _h));
		btnUpgrade->setPosition(Vec2(_Wsize.width/2+btnUpgrade->getContentSize().width, _h));
	
		showAction(btnInfo, 0.5f);
		showAction(btnEnter, 0.5f);
		showAction(btnUpgrade, 0.5f);
	}

};

void HomeOptionLayer::hide(BuildingSprite* spr) {

	btnInfo->stopAllActions();
	btnEnter->stopAllActions();
	btnUpgrade->stopAllActions();
	_headquarters->stopAllActions();

	hideAction(btnInfo, 0.2f);
	hideAction(btnEnter, 0.2f);
	hideAction(btnUpgrade, 0.2f);
	_headquarters->setOpacity(0);
};

void HomeOptionLayer::showAction(Button* btn, float delay) {  

	btn->runAction(EaseBackIn::create(MoveBy::create(delay, Vec2(0, 300))));
};

void HomeOptionLayer::hideAction(Button* btn, float delay) {

	btn->runAction(EaseBackOut::create(MoveBy::create(delay, Vec2(0, -200))));
};

void HomeOptionLayer::infoCallback(Ref* sender, Widget::TouchEventType type) {

	if(type==Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)sender;
	}
};

void HomeOptionLayer::enterCallback(Ref* sender, Widget::TouchEventType type) {
	
	if(type==Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)sender;
	}
};

void HomeOptionLayer::upGradeCallback(Ref* sender, Widget::TouchEventType type) {
	
	if(type==Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)sender;
	}
};
