#include "Notice.h"

#include "Utils\Config.h"

bool Notice::init(string info) {
	if(!Node::init()) {
		return false;
	}

	_Wsize = Director::getInstance()->getWinSize();

	this->showUI(info);

	return true;
};

void Notice::showUI(string info) {

	log("%s", info.c_str());

	auto label = Label::createWithSystemFont(info, FONT_ARIAL, 24);
	label->setPosition(Vec2(_Wsize.width/2, _Wsize.height/2));
	label->setOpacity(0);
	label->setColor(Color3B::RED);
	this->addChild(label);

	auto action1 = Spawn::create(
		MoveBy::create(1.0f, Vec2(0, 100)),
		FadeIn::create(1.0f),
		nullptr);
	auto action2 = Spawn::create(
		MoveBy::create(1.0f, Vec2(0, 100)),
		FadeOut::create(1.0f),
		nullptr);
	auto func = CallFunc::create(CC_CALLBACK_0(Notice::remove, this));

	label->runAction(
		Sequence::create(
			action1,
			//DelayTime::create(1.0f),
			action2,
			func,
			nullptr
		)
	);
};

void Notice::remove() {
	this->removeFromParent();
};

Notice* Notice::create(string info) {

	Notice* ret = new (std::nothrow)Notice();
	if(ret && ret->init(info)) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};



