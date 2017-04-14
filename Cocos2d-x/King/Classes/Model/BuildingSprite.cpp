#include "BuildingSprite.h"

//use
#include "Utils\Config.h"
#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"

BuildingSprite* BuildingSprite::create(int index, Vec2 ve) {

	BuildingSprite* ret = new(std::nothrow)BuildingSprite();
	if(ret && ret->init(index, ve)) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};

bool BuildingSprite::init(int index, Vec2 ve) {
	if(!Sprite::init()) {
		return false;
	}

	_cache = Director::getInstance()->getTextureCache();

	_isTouched = false;
	_isSelected = false;
	_canTouched = true;

	_index = index;

	this->setTexture(IMG_BUILDING_Floor);

	loadData(_index);
	addTouch();

	return true;
};

void BuildingSprite::addTouch() {

	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(BuildingSprite::onToucheBegan, this);
	_listener->onTouchMoved = CC_CALLBACK_2(BuildingSprite::onToucheMoved, this);
	//_listener->onTouchEnded = CC_CALLBACK_2(BuildingSprite::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

};

void BuildingSprite::loadData(int index) { 
	log("log = %d", index);

	ValueMap data = DM()->_building.at(index).asValueMap();

	_id = data["ID"].asInt();
	_BuildingID = data["BuildingID"].asInt();
	_pos = Vec2(data["PositionX"].asInt(), data["PositionY"].asInt());

	//测试代码
	//_pos = ve;

	_buildState = data["BuildState"].asInt();
	_lastBuildTime = data["LastBuildTime"].asInt();
	_lastGoldHarvest = data["LastGoldHarvest"].asInt();
	_lastWoodHarvest = data["LastWoodHarvest"].asInt();

	_type = data["Type"].asInt();
	_level = data["Level"].asInt();
	_name = data["Name"].asString();
	_healthPoint = data["HealthPoint"].asInt();
	_description = data["Description"].asString();

	_goldRequire = data["GoldRequire"].asInt();
	_woodRequire = data["WoodRequire"].asInt();
	_timeRequire = data["TimeRequire"].asInt();
	_baseLevelRequire = data["BaseLevelRequire"].asInt();
	_playerLevelRequire = data["PlayerLevelRequire"].asInt();
	_expReward = data["ExpReward"].asInt();

	// 生产属性
	_goldProduct = data["GoldProduct"].asInt();
	_woodProduct = data["WoodProduct"].asInt();
	// 资源属性
	_goldCapacity = data["GoldCapacity"].asInt();
	_woodCapacity = data["WoodCapacity"].asInt();
	// 攻击属性
	_isBroken = false;
	_canAttack = data["CanAttack"].asInt();
	_damage = data["Damage"].asInt();
	_attackSpeed = data["AttackSpeed"].asInt();
	_shootRange = data["ShootRange"].asInt();
	_damageRange = data["DamageRange"].asInt();

	log("%d, %f, %f, %d", index, _pos.x, _pos.y, _type);

	//覆盖地面
	GM()->setCoverd(_pos, 1);
	loadUI();
};

void BuildingSprite::loadUI() {

	_normal = GM()->getBuildingIMG(_type);
	_normal->setAnchorPoint(Vec2::ZERO);
	_normal->setPosition(Vec2(-15, -10));		//微调位置
	_broken = GM()->getBuildingBrokenIMG(_type);
	_broken->setAnchorPoint(Vec2::ZERO);
	_broken->setOpacity(0);
	_tip = Sprite::createWithTexture(_cache->getTextureForKey(IMG_BUILDING_ArrowTip));
	_tip->setAnchorPoint(Vec2::ZERO);
	_tip->setPosition(Vec2(-20, -20));		//微调位置
	_tip->setOpacity(0);

	this->setPosition(GM()->getMapPos(_pos));

	this->addChild(_normal, 1);
	this->addChild(_broken, 1);
	this->addChild(_tip);

	this->setLocalZOrder(_pos.y + _pos.x);
	this->setOpacity(0);
};

bool BuildingSprite::onToucheBegan(Touch* touch, Event* event) {
	log("onToucheBegan");

	if(_canTouched == false) {
		return false;
	}

	if(GM()->_newBuild == true) {
		return false;
	}

	Vec2 pos = this->getParent()->convertToNodeSpace(touch->getLocation());
	_deltaPos = 0.0;

	//点到建筑后，屏蔽map层触摸
	if(GM()->isPointInDiamond(this->getPosition(), TILED_SIZE*2, pos) == 1) {
		log("I'm in.");
		_isTouched = true;
		if(_isSelected == true) {
			log("@@@@@@@@@@@@@@True");
		}
		else {
			log("**************False");	
			_listener->setSwallowTouches(true);
		}
	}
	else {
		log("I'm out.");
		_isTouched = false;
		_isSelected = false;
		_listener->setSwallowTouches(false);
	}
	 
	return true;
};	 

void BuildingSprite::onToucheMoved(Touch* touch, Event* event) {
	log("onToucheMoved");

};

void BuildingSprite::onToucheEnded(Touch* touch, Event* event) {

};
