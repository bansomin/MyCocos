#include "BuildingInfoDialog.h"

//use
#include "Utils\Config.h"
#include "Utils\DataManager.h"
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
	addData();

	return true;
};

//先加载数据，后显示动画
void BuildingInfoDialog::addData() {
	log("BuildingInfoDialog::addData");

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

		case BUILDING_TYPE_MineFactory : {		//金库
			auto LB_goldProduct = (Text*)Helper::seekWidgetByName(ui, "lbGoldProduct");
			auto Text_goldProduct = (Text*)Helper::seekWidgetByName(ui, "GoldProduct");

			LB_goldProduct->setVisible(true);
			Text_goldProduct->setString(GM()->getIntToStr(_buildingSprite->_goldProduct));
		}
			break;

		case BUILDING_TYPE_WoodFactory : {		//木厂
			auto LB_woodProduct = (Text*)Helper::seekWidgetByName(ui, "lbWoodProduct");
			auto Text_woodProduct = (Text*)Helper::seekWidgetByName(ui, "WoodProduct");

			LB_woodProduct->setVisible(true);
			Text_woodProduct->setString(GM()->getIntToStr(_buildingSprite->_woodProduct));
		}
			break;

		case BUILDING_TYPE_BaseTower : {
			auto LB_goldCapacity = (Text*)Helper::seekWidgetByName(ui, "lbGoldCapacity");
			auto LB_woodCapacity = (Text*)Helper::seekWidgetByName(ui, "lbWoodCapacity");
			auto Text_goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
			auto Text_woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");

		/*	LB_goldCapacity->setScale(1.5f);
			LB_woodCapacity->setScale(1.5f);
			Text_goldCapacity->setScale(1.5f);
			Text_woodCapacity->setScale(1.5f);*/

			LB_goldCapacity->setVisible(true);
			LB_woodCapacity->setVisible(true);
			Text_goldCapacity->setString(GM()->getIntToStr(_buildingSprite->_goldCapacity));
			Text_woodCapacity->setString(GM()->getIntToStr(_buildingSprite->_woodCapacity));

			//BuildingLimit
			auto scrollView = (ScrollView*)Helper::seekWidgetByName(ui, "ScrollView");
			auto mineFactory = (Text*)Helper::seekWidgetByName(ui, "MineFactoryLimit");
			auto woodFactory = (Text*)Helper::seekWidgetByName(ui, "WoodFactoryLimit");
			auto arrowTower = (Text*)Helper::seekWidgetByName(ui, "ArrowTowerLimit");
			auto cannon = (Text*)Helper::seekWidgetByName(ui, "CannonLimit");
			auto laser = (Text*)Helper::seekWidgetByName(ui, "LaserLimit");

			auto baseLevel = DM()->getBaseTowerLevel();
			auto limitMap = DM()->getBuildingLimit(baseLevel);
			log("baseLevel:%d", baseLevel);

			scrollView->setVisible(true);
			mineFactory->setString("x"+limitMap["MineFactoryCapacity"].asString());
			woodFactory->setString("x"+limitMap["WoodFactoryCapacity"].asString());
			arrowTower->setString("x"+limitMap["ArrowTowerCapacity"].asString());
			cannon->setString("x"+limitMap["CannonCapacity"].asString());
			laser->setString("x"+limitMap["LaserCapacity"].asString());


		}
			break;
		default:
			break;
	}

	//显示动画
	showDialog();
};

void BuildingInfoDialog::showDialog() {
	
	//动画
	this->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f, 1.0f))); 
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