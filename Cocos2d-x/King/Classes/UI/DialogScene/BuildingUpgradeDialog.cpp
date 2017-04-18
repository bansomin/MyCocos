#include "BuildingUpgradeDialog.h"

//use
#include "Model\Notice.h"
#include "Utils\Config.h"
#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"
#include "UI\HomeScene\HomeScene.h"
#include "UI\HomeScene\HomeHubLayer.h"
#include "UI\HomeScene\HomeOptionLayer.h"

BuildingUpgradeDialog* BuildingUpgradeDialog::create(BuildingSprite* spr) {
	BuildingUpgradeDialog* ret = new(std::nothrow)BuildingUpgradeDialog();
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

bool BuildingUpgradeDialog::init(BuildingSprite* spr) {
	log("BuildingUpgradeDialog::init");

	if(!Layer::init()) {
		return false;
	}

	_cache = Director::getInstance()->getTextureCache();
	_Wsize = Director::getInstance()->getWinSize();
	_buildingSprite = spr;

	//����
	auto bg = Sprite::createWithTexture(_cache->getTextureForKey(IMG_GRAY_BG));
	bg->setScale(_Wsize.width/1000.0, _Wsize.height/1000.0);
	bg->setPosition(_Wsize/2);
	bg->setOpacity(200);
	this->addChild(bg, -1);
	this->setScale(1.0f, 0.0f);

	_ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_BUILDING_UPGRADE);
	this->addChild(_ui, 1, "UI");
	auto upgradeClose = (Button*)Helper::seekWidgetByName(_ui, "UpgradeButton");
	upgradeClose->addTouchEventListener(CC_CALLBACK_2(BuildingUpgradeDialog::upgradeFunc, this));
	auto btnClose = (Button*)Helper::seekWidgetByName(_ui, "CloseButton");
	btnClose->addTouchEventListener(CC_CALLBACK_2(BuildingUpgradeDialog::btnCloseFunc, this));

	//��������
	addData();

	return true;
};

//�ȼ������ݣ�����ʾ����
void BuildingUpgradeDialog::addData() {

	showNowInfo();
	showNextInfo();
	showRequire();
	
	//��ʾ����
	showDialog();
};

//��ʾ
void BuildingUpgradeDialog::showDialog() {

	//����
	this->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f, 1.0f)));
};

//����
void BuildingUpgradeDialog::hideDialog() {

	auto callfunc = CallFunc::create(CC_CALLBACK_0(BuildingUpgradeDialog::removeFunc, this));
	//����
	this->runAction(
		Sequence::create(
		EaseBackIn::create(ScaleTo::create(0.3f, 1.0f, 0.0f)),
		callfunc,
		nullptr
		)
	);
};

//��ǰ��Ϣ
void BuildingUpgradeDialog::showNowInfo() {

	auto title = (Text*)Helper::seekWidgetByName(_ui, "Title");
	auto healthPoint = (Text*)Helper::seekWidgetByName(_ui, "HealthPoint");
	auto image = (ImageView*)Helper::seekWidgetByName(_ui, "BuildingImage");

	string titleStr = _buildingSprite->_name
					+ "Lv."
					+ GM()->getIntToStr(_buildingSprite->_level)
					+ "->"
					+ GM()->getIntToStr(_buildingSprite->_level+1);

	healthPoint->setString(GM()->getIntToStr(_buildingSprite->_healthPoint));
	image->loadTexture(GM()->getBuildingIMGName(_buildingSprite->_type));
	title->setString(titleStr);

	switch(_buildingSprite->_type) {

		case BUILDING_TYPE_ArrowTower:		//�ѻ���
		case BUILDING_TYPE_Cannon:			//���������
		case BUILDING_TYPE_Laser:{			//����

			auto LB_damage = (Text*)Helper::seekWidgetByName(_ui, "lbDamage");
			auto LB_attackSpeed = (Text*)Helper::seekWidgetByName(_ui, "lbAttackSpeed");
			auto LB_shootRange = (Text*)Helper::seekWidgetByName(_ui, "lbShootRange");
			auto Text_damage = (Text*)Helper::seekWidgetByName(_ui, "Damage");
			auto Text_attackSpeed = (Text*)Helper::seekWidgetByName(_ui, "AttackSpeed");
			auto Text_shootRange = (Text*)Helper::seekWidgetByName(_ui, "ShootRange");

			LB_damage->setVisible(true);
			LB_attackSpeed->setVisible(true);
			LB_shootRange->setVisible(true);

			Text_damage->setString(GM()->getIntToStr(_buildingSprite->_damage));
			Text_attackSpeed->setString(GM()->getIntToStr(_buildingSprite->_attackSpeed));
			Text_shootRange->setString(GM()->getIntToStr(_buildingSprite->_shootRange));

		}
		break;

		case BUILDING_TYPE_MineFactory:{		//���
			auto LB_goldProduct = (Text*)Helper::seekWidgetByName(_ui, "lbGoldProduct");
			auto Text_goldProduct = (Text*)Helper::seekWidgetByName(_ui, "GoldProduct");

			LB_goldProduct->setVisible(true);
			Text_goldProduct->setString(GM()->getIntToStr(_buildingSprite->_goldProduct));
		}
		break;

		case BUILDING_TYPE_WoodFactory:{		//ľ��
			auto LB_woodProduct = (Text*)Helper::seekWidgetByName(_ui, "lbWoodProduct");
			auto Text_woodProduct = (Text*)Helper::seekWidgetByName(_ui, "WoodProduct");

			LB_woodProduct->setVisible(true);
			Text_woodProduct->setString(GM()->getIntToStr(_buildingSprite->_woodProduct));
		}
		break;

		case BUILDING_TYPE_BaseTower:{
			auto LB_goldCapacity = (Text*)Helper::seekWidgetByName(_ui, "lbGoldCapacity");
			auto LB_woodCapacity = (Text*)Helper::seekWidgetByName(_ui, "lbWoodCapacity");
			auto Text_goldCapacity = (Text*)Helper::seekWidgetByName(_ui, "GoldCapacity");
			auto Text_woodCapacity = (Text*)Helper::seekWidgetByName(_ui, "WoodCapacity");

			/*	LB_goldCapacity->setScale(1.5f);
			LB_woodCapacity->setScale(1.5f);
			Text_goldCapacity->setScale(1.5f);
			Text_woodCapacity->setScale(1.5f);*/

			LB_goldCapacity->setVisible(true);
			LB_woodCapacity->setVisible(true);
			Text_goldCapacity->setString(GM()->getIntToStr(_buildingSprite->_goldCapacity));
			Text_woodCapacity->setString(GM()->getIntToStr(_buildingSprite->_woodCapacity));

			//BuildingLimit
			auto scrollView = (ScrollView*)Helper::seekWidgetByName(_ui, "ScrollView");
			auto mineFactory = (Text*)Helper::seekWidgetByName(_ui, "MineFactoryLimit");
			auto woodFactory = (Text*)Helper::seekWidgetByName(_ui, "WoodFactoryLimit");
			auto arrowTower = (Text*)Helper::seekWidgetByName(_ui, "ArrowTowerLimit");
			auto cannon = (Text*)Helper::seekWidgetByName(_ui, "CannonLimit");
			auto laser = (Text*)Helper::seekWidgetByName(_ui, "LaserLimit");

			auto baseLevel = DM()->getBaseTowerLevel();
			auto limitMap = DM()->getBuildingLimit(baseLevel);
			log("baseLevel:%d", baseLevel);

			scrollView->setVisible(true);

			//��
	/*		string num = "2323";
			mineFactory->setString("+"+num);
			woodFactory->setString("+"+num);
			arrowTower->setString("+"+num);
			cannon->setString("+"+num);
			laser->setString("+"+num);*/
		}
		break;
		default:
			break;
	}

};

 //��������Ϣ
void BuildingUpgradeDialog::showNextInfo() {

	ValueMap& map = DM()->getBuildingNextInfo(_buildingSprite->_BuildingID);
	
	auto healthPoint = (Text*)Helper::seekWidgetByName(_ui, "AddHealthPoint");
	healthPoint->setString("+" + GM()->getIntToStr(map["HealthPoint"].asInt() - _buildingSprite->_healthPoint));

	switch(_buildingSprite->_type) {

		case BUILDING_TYPE_ArrowTower:		//�ѻ���
		case BUILDING_TYPE_Cannon:			//���������
		case BUILDING_TYPE_Laser:{			//����
			auto Text_damage = (Text*)Helper::seekWidgetByName(_ui, "AddDamage");
			auto Text_attackSpeed = (Text*)Helper::seekWidgetByName(_ui, "AddAttackSpeed");
			auto Text_shootRange = (Text*)Helper::seekWidgetByName(_ui, "AddShootRange");

			Text_damage->setString("+");
			Text_attackSpeed->setString("+");
			Text_shootRange->setString("+");

		}
		break;

		case BUILDING_TYPE_MineFactory:{		//���
			auto Text_goldProduct = (Text*)Helper::seekWidgetByName(_ui, "AddGoldProduct");
			Text_goldProduct->setString("+");
		}
		break;

		case BUILDING_TYPE_WoodFactory:{		//ľ��
			auto Text_woodProduct = (Text*)Helper::seekWidgetByName(_ui, "AddWoodProduct");
			Text_woodProduct->setString("+");
		}
		break;

		case BUILDING_TYPE_BaseTower:{
			auto Text_goldCapacity = (Text*)Helper::seekWidgetByName(_ui, "AddGoldCapacity");
			auto Text_woodCapacity = (Text*)Helper::seekWidgetByName(_ui, "AddWoodCapacity");

			Text_goldCapacity->setString("+" + GM()->getIntToStr(map["GoldCapacity"].asInt() - _buildingSprite->_goldCapacity));
			Text_woodCapacity->setString("+" + GM()->getIntToStr(map["WoodCapacity"].asInt() - _buildingSprite->_woodCapacity));

			//BuildingLimit
			auto minefactory = (Text*)Helper::seekWidgetByName(_ui, "MineFactoryLimit");
			auto woodfactory = (Text*)Helper::seekWidgetByName(_ui, "WoodFactoryLimit");
			auto arrowtower = (Text*)Helper::seekWidgetByName(_ui, "ArrowTowerLimit");
			auto cannon = (Text*)Helper::seekWidgetByName(_ui, "CannonLimit");
			auto laser = (Text*)Helper::seekWidgetByName(_ui, "LaserLimit");

			auto baseLevel = DM()->getBaseTowerLevel();
			auto nowLimit = DM()->getBuildingLimit(baseLevel);
			auto nextLimit = DM()->getBuildingLimit(baseLevel + 1);
			
			//�����ܽ������½�����Ŀ
			minefactory->setString("+"+(GM()->getIntToStr(nextLimit["MineFactoryCapacity"].asInt()-nowLimit["MineFactoryCapacity"].asInt())));
			woodfactory->setString("+"+(GM()->getIntToStr(nextLimit["WoodFactoryCapacity"].asInt()-nowLimit["WoodFactoryCapacity"].asInt())));
			arrowtower->setString("+"+(GM()->getIntToStr(nextLimit["ArrowTowerCapacity"].asInt()-nowLimit["ArrowTowerCapacity"].asInt())));
			cannon->setString("+"+(GM()->getIntToStr(nextLimit["CannonCapacity"].asInt()-nowLimit["CannonCapacity"].asInt())));
			laser->setString("+" + (GM()->getIntToStr(nextLimit["LaserCapacity"].asInt() - nowLimit["LaserCapacity"].asInt())));
		}
		break;
		default:
			break;
	}


};

//��Ҫ����Դ��Ŀ
void BuildingUpgradeDialog::showRequire() {

	auto goldRequire = (Text*)Helper::seekWidgetByName(_ui, "GoldRequire");
	auto woodRequire = (Text*)Helper::seekWidgetByName(_ui, "WoodRequire");
	auto timeRequire = (Text*)Helper::seekWidgetByName(_ui, "TimeRequire");

	_goldRequire = _buildingSprite->_goldRequire;
	_woodRequire = _buildingSprite->_woodRequire;
	_timeRequire = _buildingSprite->_timeRequire;

	goldRequire->setString(GM()->getIntToStr(_goldRequire));
	woodRequire->setString(GM()->getIntToStr(_woodRequire));
	timeRequire->setString(GM()->getIntToStr(_timeRequire));
};

//�Ƴ�
void BuildingUpgradeDialog::removeFunc() {

	this->removeFromParent();
};

//����
void BuildingUpgradeDialog::upgradeFunc(Ref* sender, Widget::TouchEventType type) {

	_chnStr = Dictionary::createWithContentsOfFile("fonts/myString.xml");

	if(type==Widget::TouchEventType::ENDED) {
		//��ҵȼ�or˾��ȼ�����
		int flag = -1;
		if(_buildingSprite->_type==BUILDING_TYPE_BaseTower) {
			int playerLevel = DM()->getPlayerLevel();
			if(_buildingSprite->_playerLevelRequire > playerLevel) {
				flag = 1;
			}
		}
		else {
			int baseLevel = DM()->getBaseTowerLevel();
			if(_buildingSprite->_baseLevelRequire > baseLevel) {
				flag = 2;
			}
		}

		log("flag = %d", flag);

		//(__String*)_chnStr->objectForKey("grade"))->getCString()
		//��ҵȼ�����
		if(flag == 1) {		
			auto notice = Notice::create(((__String*)_chnStr->objectForKey("needPlayerLevel"))->getCString() + GM()->getIntToStr(_buildingSprite->_playerLevelRequire));
			this->getParent()->addChild(notice, 999);
		}
		//˾��ȼ�����
		else if(flag == 2) {
			auto notice = Notice::create(((__String*)_chnStr->objectForKey("needheadquartersLevel"))->getCString() + GM()->getIntToStr(_buildingSprite->_baseLevelRequire));
			this->getParent()->addChild(notice, 999);
		}
		//��Դ�Ƿ����
		else if((_goldRequire>DM()->getGoldCount()) || (_woodRequire>DM()->getWoodCount())) {
			log("Gold:%d, %d", _goldRequire, DM()->getGoldCount());
			log("Wood:%d, %d", _woodRequire, DM()->getWoodCount());
			auto notice = Notice::create(((__String*)_chnStr->objectForKey("lackofres"))->getCString());
			this->getParent()->addChild(notice, 999);
		}
		//������������
		else {

			auto btn = (Button*)sender;
			btn->setTouchEnabled(false);

			auto homeScene = (HomeScene*)this->getParent();

			//���½�ң�ľ����Դ
			auto homeHubLayer = (HomeHubLayer*)homeScene->_hubLayer;
			homeHubLayer->addGold(-_goldRequire);
			homeHubLayer->addWood(-_woodRequire);

			//������������
			_buildingSprite->upgrade();

			//����HomeOptionLayer
			auto optLayer = (HomeOptionLayer*)homeScene->_optionLayer;
			optLayer->show(_buildingSprite);

			//����
			hideDialog();
		}
	}
};

void BuildingUpgradeDialog::btnCloseFunc(Ref* sender, Widget::TouchEventType type) {

	if(type==Widget::TouchEventType::ENDED) {
		auto btn = (Button*)sender;
		btn->setTouchEnabled(false);
		hideDialog();
	}
};