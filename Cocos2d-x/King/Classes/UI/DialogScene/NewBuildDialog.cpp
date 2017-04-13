#include "NewBuildDialog.h"

//use
#include "Utils\Config.h"
#include "Model\Notice.h"

bool NewBuildDialog::init() {
	if(!Layer::init()) {

		return false;
	}

	_Wsize = Director::getInstance()->getWinSize();

	this->setScale(0.0f);
	this->showDialog();

	return true;
};

void NewBuildDialog::showDialog() {

	this->runAction(EaseBackIn::create(ScaleTo::create(0.3f, 1.0f)));

	auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_NEWBUILD);
	this->addChild(ui, 1, "UI");

	//关闭按钮回调
	auto btn = Helper::seekWidgetByName(ui, "CloseButton");
	btn->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::closeCallback, this));

	//各种建筑按钮
	auto btnMine    = Helper::seekWidgetByName(ui, "MineFactoryButton");
	auto btnWood    = Helper::seekWidgetByName(ui, "WoodFactoryButton");
	auto btnArrow   = Helper::seekWidgetByName(ui, "ArrowTowerButton");
	auto btnCannon  = Helper::seekWidgetByName(ui, "CannonButton");
	auto btnLaser   = Helper::seekWidgetByName(ui, "LaserButton");

	btnMine->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));
	btnWood->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));
	btnArrow->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));
	btnMine->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));
	btnCannon->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));
	btnLaser->addTouchEventListener(CC_CALLBACK_2(NewBuildDialog::buildCallback, this));

};

//新建回调
void NewBuildDialog::buildCallback(Ref* sender, Widget::TouchEventType type) {

	if(type == Widget::TouchEventType::ENDED) {
		
		auto btn = (Button*)sender;
		string name = btn->getName();

		this->showNotice(name);

		if(name == "MineFactoryButton") {
			log("MineFactoryButton");

		}
		else if(name == "WoodFactoryButton") {
			log("WoodFactoryButton");

		}
		else if(name=="ArrowTowerButton") {
			log("ArrowTowerButton");

		}
		else if(name=="CannonButton") {
			log("CannonButton");

		}
		else if(name=="LaserButton") {
			log("LaserButton");

		}

	}
};

void NewBuildDialog::hideDialog() {

	auto func = CallFunc::create(CC_CALLBACK_0(NewBuildDialog::removeDialog, this));
	this->runAction(
		Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.2f, 0.0f)), 
			func, 
			nullptr)
	);
};

void NewBuildDialog::showNotice(string info) {
	
	auto notice = Notice::create(info);
	this->getParent()->addChild(notice, 999);
};

void NewBuildDialog::removeDialog() {
	this->removeFromParent();
};

void NewBuildDialog::closeCallback(Ref *sender, Widget::TouchEventType type) {

	if(type == Widget::TouchEventType::ENDED) {
		auto btn = (Button*)sender;
		btn->setTouchEnabled(false);
		this->hideDialog();
	}
};

NewBuildDialog* NewBuildDialog::create() {

	NewBuildDialog* ret = new(nothrow) NewBuildDialog();
	if(ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};
