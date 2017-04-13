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

	_isTouched = false;
	_isSelected = false;
	_canTouched = true;

	_index = index;

	loadData(index, ve);
	loadUI();

	return true;
};

void BuildingSprite::loadData(int index, Vec2 ve) {


	ValueMap data = DM()->_building.at(index).asValueMap();

	_id = data["ID"].asInt();
	_BuildingID = data["BuildingID"].asInt();
	//_pos = Vec2(data["PositionX"].asInt(), data["PositionY"].asInt());

	//测试代码
	_pos = ve;

	log("%d, %f, %f", index, _pos.x, _pos.y);

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

	//覆盖地面
	GM()->setCoverd(_pos, 1);
};

void BuildingSprite::loadUI() {

	this->setTexture(IMG_BUILDING_Floor);

	_size = this->getContentSize();

	this->setPosition(GM()->getMapPos(_pos));

};

void BuildingSprite::onToucheBegan(const std::vector<Touch*>& touches, Event* event) {

};

void BuildingSprite::onToucheMoved(const std::vector<Touch*>& touches, Event* event) {

};

void BuildingSprite::onToucheEnded(const std::vector<Touch*>& touches, Event* event) {

};
