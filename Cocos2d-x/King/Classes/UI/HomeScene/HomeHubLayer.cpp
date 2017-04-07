#include "HomeHubLayer.h"

#include "Utils\Config.h"
#include "Utils\GlobalManager.h"
#include "UI\DialogScene\NewBuildDialog.h"

HomeHubLayer::HomeHubLayer() {

};

HomeHubLayer::~HomeHubLayer() {

};

bool HomeHubLayer::init() {
	if(!Layer::init()) {
		return false;
	}

	_Wsize = Director::getInstance()->getWinSize();

	this->loadData();
	this->loadUI();

	return true;
};


void HomeHubLayer::loadData() {

};

void HomeHubLayer::loadUI() {

	//auto homehublayercsb = CSLoader::createNode("Layer.csb");
	//homehublayercsb->setScaleX(_Wsize.width/homehublayercsb->getContentSize().width);
	//homehublayercsb->setScaleY(_Wsize.height/homehublayercsb->getContentSize().height);
	//this->addChild(homehublayercsb);

	auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_LAYER_HOMEHUD);
	this->addChild(ui, 0, "UI");	

	//worldBtn
	auto worldBtn = (Button*)Helper::seekWidgetByName(ui, "WorldButton");
	worldBtn->addTouchEventListener(CC_CALLBACK_2(HomeHubLayer::btnCallback, this));

	//buildBtn
	auto buildBtn = (Button*)Helper::seekWidgetByName(ui, "BuildButton");
	buildBtn->addTouchEventListener(CC_CALLBACK_2(HomeHubLayer::btnCallback, this));

};

void HomeHubLayer::btnCallback(Ref* sender, Widget::TouchEventType type) {
	if(type == Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)sender;
		auto name = btn->getName();
		if(name == "WorldButton") {
			log("WorldButton");

			GM()->enterWorldScene();
		}
		else if(name == "BuildButton") {
			log("BuildButton");

			auto buildDialog = NewBuildDialog::create();
			this->getParent()->addChild(buildDialog);
		}
	}
};