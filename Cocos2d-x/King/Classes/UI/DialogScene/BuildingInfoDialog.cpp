#include "BuildingInfoDialog.h"

//use
#include "Utils\Config.h"
#include "Utils\GlobalManager.h"

BuildingInfoDialog* BuildingInfoDialog::create(BuildingSprite* spr) {
	BuildingInfoDialog* ret = new(std::nothrow)BuildingInfoDialog();
	if(ret && ret->init(spr)) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};

bool BuildingInfoDialog::init(BuildingSprite* spr) {
	log("BuildingInfoDialog::init");

	if(!Layer::init()) {
		return false;
	}

	_cache = Director::getInstance()->getTextureCache();
	_Wsize = Director::getInstance()->getWinSize();
	_buildingSprite = spr;

	//背景
	auto bg = Sprite::createWithTexture(_cache->getTextureForKey(IMG_GRAY_BG));
	bg->setScale(_Wsize.width/1000.0, _Wsize.height/1000.0);
	bg->setPosition(_Wsize/2);
	bg->setOpacity(200);
	this->addChild(bg, -1);	
	this->setScale(1.0f, 0.0f);

	auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_BUILDING_INFO);
	this->addChild(ui, 1, "UI");
	auto btnClose = (Button*)Helper::seekWidgetByName(ui, "CloseButton");
	btnClose->addTouchEventListener(CC_CALLBACK_2(BuildingInfoDialog::btnCloseFunc, this));

	//加载数据
	showInfo();	

	return true;
};

//先加载数据，后显示动画
void BuildingInfoDialog::showInfo() {

	auto _chnStr = Dictionary::createWithContentsOfFile("fonts/myString.xml"); 
	auto ui = (Widget*)this->getChildByName("UI");

	auto title = (Text*)Helper::seekWidgetByName(ui, "Title");
	auto descr = (Text*)Helper::seekWidgetByName(ui, "Description");
	auto healthPoint = (Text*)Helper::seekWidgetByName(ui, "HealthPoint");
	auto image = (ImageView*)Helper::seekWidgetByName(ui, "BuildingImage");

	string titleStr = _buildingSprite->_name+
		"("+
		((__String*)_chnStr->objectForKey("grade"))->getCString()+GM()->getIntToStr(_buildingSprite->_level)
		+
		")";
	descr->setString(_buildingSprite->_description);
	healthPoint->setString(GM()->getIntToStr(_buildingSprite->_healthPoint));
	image->loadTexture(GM()->getBuildingIMGName(_buildingSprite->_type));
	title->setString(titleStr);

	switch(_buildingSprite->_type) {
		case BUILDING_TYPE_ArrowTower:		//狙击塔
		case BUILDING_TYPE_Cannon:			//火箭发射器
		case BUILDING_TYPE_Laser: {			//激光
		
			auto LB_damage = (Text*)Helper::seekWidgetByName(ui, "lbDamage");
			auto LB_attackSpeed = (Text*)Helper::seekWidgetByName(ui, "lbAttackSpeed");
			auto LB_shootRange = (Text*)Helper::seekWidgetByName(ui, "lbShootRange");
			auto Text_damage = (Text*)Helper::seekWidgetByName(ui, "Damage");
			auto Text_attackSpeed = (Text*)Helper::seekWidgetByName(ui, "AttackSpeed");
			auto Text_shootRange = (Text*)Helper::seekWidgetByName(ui, "ShootRange");

			LB_damage->setVisible(true);
			LB_attackSpeed->setVisible(true);
			LB_shootRange->setVisible(true);

			Text_damage->setString(GM()->getIntToStr(_buildingSprite->_damage));
			Text_attackSpeed->setString(GM()->getIntToStr(_buildingSprite->_attackSpeed));
			Text_shootRange->setString(GM()->getIntToStr(_buildingSprite->_shootRange));
		
		}
			break;
		default:
			break;
	}

	//显示动画
	showDialog();
};

void BuildingInfoDialog::showDialog() {
	
	auto callfunc = CallFunc::create(CC_CALLBACK_0(BuildingInfoDialog::showInfo, this));
	//动画
	this->runAction(
		Sequence::create(
			EaseBackOut::create(ScaleTo::create(0.3f, 1.0f, 1.0f)),
			callfunc, 
			nullptr
		)
	);

};

void BuildingInfoDialog::hideDialog() {

	auto callfunc = CallFunc::create(CC_CALLBACK_0(BuildingInfoDialog::removeFunc, this));
	//动画
	this->runAction(
		Sequence::create(
		EaseBackIn::create(ScaleTo::create(0.3f, 1.0f, 0.0f)),
		callfunc,
		nullptr
		)
	);

};

//移除
void BuildingInfoDialog::removeFunc() {

	this->removeFromParent();
};

void BuildingInfoDialog::btnCloseFunc(Ref* sender, Widget::TouchEventType type) {

	if(type==Widget::TouchEventType::ENDED) {
		auto btn = (Button*)sender;
		btn->setTouchEnabled(false);
		hideDialog();
	}
};