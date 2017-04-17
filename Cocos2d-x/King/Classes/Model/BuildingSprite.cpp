#include "BuildingSprite.h"

//use
#include "Utils\Config.h"
#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"
#include "UI\HomeScene\HomeScene.h"
#include "UI\HomeScene\HomeMapLayer.h"
#include "UI\HomeScene\HomeOptionLayer.h"


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
	_listener->onTouchEnded = CC_CALLBACK_2(BuildingSprite::onToucheEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
};

void BuildingSprite::loadData(int index) { 
	log("log = %d", index);

	ValueMap data = DM()->_building.at(index).asValueMap();

	_id = data["ID"].asInt();
	_BuildingID = data["BuildingID"].asInt();
	_pos = Vec2(data["PositionX"].asInt(), data["PositionY"].asInt());

	//���Դ���
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

	// ��������
	_goldProduct = data["GoldProduct"].asInt();
	_woodProduct = data["WoodProduct"].asInt();
	// ��Դ����
	_goldCapacity = data["GoldCapacity"].asInt();
	_woodCapacity = data["WoodCapacity"].asInt();
	// ��������
	_isBroken = false;
	_canAttack = data["CanAttack"].asInt();
	_damage = data["Damage"].asInt();
	_attackSpeed = data["AttackSpeed"].asInt();
	_shootRange = data["ShootRange"].asInt();
	_damageRange = data["DamageRange"].asInt();

	log("%d, %f, %f, %d", index, _pos.x, _pos.y, _type);

	//���ǵ���
	GM()->setCoverd(_pos, 1);
	loadUI();
};

void BuildingSprite::loadUI() {

	_normal = GM()->getBuildingIMG(_type);
	_normal->setAnchorPoint(Vec2::ZERO);
	_normal->setPosition(Vec2(-10, -5));		//΢��λ��
	_broken = GM()->getBuildingBrokenIMG(_type);
	_broken->setAnchorPoint(Vec2::ZERO);
	_broken->setOpacity(0);
	_tip = Sprite::createWithTexture(_cache->getTextureForKey(IMG_BUILDING_ArrowTip));
	_tip->setAnchorPoint(Vec2::ZERO);
	_tip->setPosition(Vec2(-20, -20));		//΢��λ��
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

	//�㵽����������map�㴥��
	// ���Ƿ���������
	if(GM()->isPointInDiamond(this->getPosition(), TILED_SIZE*2, pos) == 1) {
		log("I'm in.");
		_isTouched = true;		//�������
		if(_isSelected) {
			log("************** True");
			_listener->setSwallowTouches(true);		//�����²㴥��
		}
		else {
			log("************** False");	
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

	Vec2 pos = this->getParent()->convertToNodeSpace(touch->getLocation());
	Vec2 delta = pos - this->getPosition();
	_deltaPos += Vec2(0, 0).distance(touch->getDelta());
	
	if(_isSelected) {			//�ƶ�����
		moveBuilding(delta);
	}
};

void BuildingSprite::onToucheEnded(Touch* touch, Event* event) {

	//log("_deltaPos = %f", _deltaPos);

	/*****************��һ�δ�������ʱ������������Ϊѡ��״̬����ʾָʾ��ͷ������������*****************/
	if(_isTouched) {
		if(_deltaPos<=LIMIT_DELTA){		//�ƶ�С��ָ������
			
			//��һ�ε��
			if(_isSelected==false) {
				//��ȥ��ռ��
				GM()->setCoverd(_pos, -1);
				log("CHU :��%f, %f", _pos.x, _pos.y);
			}

			_isSelected = true;
			this->setOpacity(255);			//��ʾ��������
			this->setColor(Color3B::GREEN);	//�ײ���ʾΪ��ɫ
			this->setLocalZOrder(TILED_TOTAL_X + TILED_TOTAL_Y + 1);
			_tip->setOpacity(255);			//��ʾ��ͷ

			selectedAction();				//����ѡ��ʱ�Ķ���
		}
	}
	else {
		_isSelected = false;				//ȡ��ѡ��״̬
		this->setOpacity(0);				//���صײ�
		this->setColor(Color3B::WHITE);		//�ײ���ʾΪ��ɫ
		_tip->setOpacity(0);				//���ؼ�ͷ

		this->setTiledPos();				//������Ƭ����

	}

	auto _homeScene = (HomeScene*)((HomeMapLayer*)((LayerColor*)((Sprite*)this->getParent())->getParent())->getParent())->getParent();
	auto _optionLayer = _homeScene->_optionLayer;

	if(_isTouched && (_deltaPos<=LIMIT_DELTA)) {
		if(!_isShowOpt) {
			_isShowOpt = true;
			_optionLayer->show(this);
		}
	}
	else if(_isShowOpt) {
		_isShowOpt = false;
		_optionLayer->hide(this);
	}


};

//�ƶ�����
void BuildingSprite::moveBuilding(Vec2 delta) {
	
	if(fabs(delta.x) >= TILED_WIDTH/2.0 ||
	   fabs(delta.y) >= TILED_HEIGHT/2.0) {

		int sgnX = 1, sgnY = 1;
		if(delta.x < 0) {
			sgnX = -1;
		}
		if(delta.y < 0) {
			sgnY = -1;
		}

		Vec2 poss = this->getPosition()+Vec2(sgnX*TILED_WIDTH/2, sgnY*TILED_HEIGHT/2);

		this->setPosition(poss);
		Vec2 tiledPos = GM()->getTiledPos(this->getPosition());

		//�Ƿ�Խ�磬��������ʩռ��
		if(GM()->isOutMap(this->getPosition()) ||
		   GM()->isCovered(tiledPos)) {
			this->setColor(Color3B::RED);
		}
		else {
			this->setColor(Color3B::GREEN);
		}
	}
};

//������Ƭ����
void BuildingSprite::setTiledPos() {

	auto mapPos = this->getPosition();
	//�Ƿ񳬳���Χ���µ�ַ�Ƿ����
	if(GM()->isOutMap(mapPos) || GM()->isCovered(GM()->getTiledPos(mapPos))) {
		this->setPosition(GM()->getMapPos(_pos));
	}
	else {
		_pos = GM()->getTiledPos(this->getPosition());
		//�������ݿ�
		DM()->updateBuildingPos(_id, _pos);
	}
	this->setLocalZOrder(_pos.y + _pos.x);
	//�ָ�ռ��
	GM()->setCoverd(_pos, 1);
};				

//��ѡ��ʱ�Ķ���Ч��
void BuildingSprite::selectedAction() {

	unselectedAction();		//��ȡ��֮ǰ���� 

	auto scaleUp = ScaleTo::create(0.1f, 1.1f);
	auto scaleDown = ScaleTo::create(0.1f, 1.0f);
	auto moveUp = MoveBy::create(0.1f, Vec2(0, 3));
	auto moveDown = MoveBy::create(0.1f, Vec2(0, -3));
	auto tintIn = TintTo::create(1.0f, Color3B(160, 160, 160));
	auto tintOut = TintTo::create(1.0f, Color3B::WHITE);
	auto act1 = Sequence::create(scaleUp, scaleDown, nullptr);
	auto act2 = Sequence::create(moveUp, moveDown, nullptr);
	auto act3 = RepeatForever::create(Sequence::create(tintIn, tintOut, nullptr));

	_normal->runAction(Spawn::create(act1, act2, nullptr));
	_normal->runAction(act3);
};

// ȥ��ѡ�ж���
void BuildingSprite::unselectedAction() {

	_normal->stopAllActions();
	_normal->setScale(1.0f);
	_normal->setPosition(Vec2(-10, -5));
	_normal->setColor(Color3B::WHITE);
};


