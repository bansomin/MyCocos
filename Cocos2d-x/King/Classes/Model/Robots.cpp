#include "Robots.h"

//use
#include "Utils\Config.h"
//#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"

Robots* Robots::create(int index) {

	Robots* ret = new(std::nothrow)Robots();
	if(ret && ret->init(index)) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};

bool Robots::init(int index) {
	if(!Sprite::init()) {
		return false;
	}

	loadUI(index);
	idle();

	return true;
};

void Robots::loadUI(int index) {

	switch(index) {
		case SOILDER_TYPE_FIGHTER :
			_arm = cocostudio::Armature::create(ANIM_NAME_FIGHTER);
			break;
		case SOILDER_TYPE_BOWMAN :
			_arm = cocostudio::Armature::create(ANIM_NAME_BOWMAN);
			break;
		case SOILDER_TYPE_GUNNER :
			_arm = cocostudio::Armature::create(ANIM_NAME_GUNNER);
			break;
		case SOILDER_TYPE_MEAT :
			_arm = cocostudio::Armature::create(ANIM_NAME_MEATSHIELD);
			break;
		default:
			break;
	}

	this->addChild(_arm);
	 
	_pos = GM()->getSpaceTiled();
	//log("@@@@@@@@@@@@@@@@ pos : %f, %f", _pos.x, _pos.y);
	auto poss = GM()->getMapPos(_pos);
	//log("################ poss : %f, %f", poss.x, poss.y);
	this->setPosition(poss);
	this->setLocalZOrder((int)_pos.x + (int)_pos.y);

	this->setScale(2);

};

//ÓÆÏÐ×´Ì¬
void Robots::idle() {

	_arm->getAnimation()->stop();
	MoveBy* moveby = nullptr;
	CallFunc* fun = CallFunc::create(CC_CALLBACK_0(Robots::idle, this));

	ValueVector vec = GM()->getNextSpace(_pos);
	int n = vec.size();
	int x = random(0, n-1);
	//log("x = %d", x);
	for(int i = 0; i<n; i++) {
		if(i == x) {
			ValueMap& map = vec.at(i).asValueMap();
			Vec2 delta = GM()->getMapDelta(map["dir"].asInt());
			//log("delta:%f, %f", delta.x, delta.y);
			moveby = MoveBy::create(random(10, 20)*0.1, delta);

			_pos.x = map["x"].asInt();
			_pos.y = map["y"].asInt();

			//log("POS: %f, %f", _pos.x, _pos.y);

			_arm->getAnimation()->play("run" + map["dir"].asString());
			break;
		}		  
	}

	if(moveby != nullptr) {
		this->runAction(
			Sequence::create(moveby, fun, nullptr)
		);
		this->setLocalZOrder((int)_pos.x + (int)_pos.y);
	}
};
