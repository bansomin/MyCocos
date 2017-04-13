#include "HomeHubLayer.h"

#include "Utils\Config.h"
#include "Utils\DataManager.h"
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

	ValueMap data = DM()->_player.at(1).asValueMap();

	_name = data["Name"].asString();
	_level = data["Level"].asInt();
	_exp = data["Exp"].asInt();
	_expRequire = DM()->getPlayerExpRequire(_level);
	_ringCount = data["RingCount"].asInt();
	_goldCount = data["GoldCount"].asInt();
	_woodCount = data["WoodCount"].asInt();
	_goldCapacity = data["GoldCapacity"].asInt();
	_woodCapacity = data["WoodCapacity"].asInt();

	log("%s %d %d %d", _name.c_str(), _level, _exp, _expRequire);
	log("(%d,%d,%d) (%d,%d)", _goldCount, _woodCount, _ringCount, _goldCapacity, _woodCapacity);
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

	//Player
	_playerName		= (Text*)Helper::seekWidgetByName(ui, "PlayerName");
	_playerLevel	= (Text*)Helper::seekWidgetByName(ui, "PlayerLevel");
	_playerBar		= (LoadingBar*)Helper::seekWidgetByName(ui, "PlayerBar");
	_playerName->setString(_name);
	_playerLevel->setString(GM()->getIntToStr(_level));
	_playerBar->setPercent((_exp*100.0)/_expRequire);

	//Gold
	_goldCountText		= (Text*)Helper::seekWidgetByName(ui, "GoldCount");
	//_goldCapacityText	= (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
	_goldBar		= (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
	_goldCountText->setString(StringUtils::format("%d / %d", _goldCount, _goldCapacity));
	//_goldCapacityText->setString(GM()->getIntToStr(_goldCapacity));
	_goldBar->setPercent((_goldCount*100.0)/_goldCapacity);

	//Wood
	_woodCountText = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
	//_woodCapacityText = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
	_woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
	_woodCountText->setString(StringUtils::format("%d / %d", _woodCount, _woodCapacity));
	//_woodCapacityText->setString(GM()->getIntToStr(_woodCapacity));
	_woodBar->setPercent((_woodCount*100.0)/_woodCapacity);

	//Ring
	_ringCountText = (Text*)Helper::seekWidgetByName(ui, "RingCount");
	_ringCountText->setString(StringUtils::format("%d", _ringCount));
};

void HomeHubLayer::addGold(int count) {
	
	//判断是否超过最大容量 
	int nowGold = _goldCount + count;
	_goldCount = MIN(nowGold, _goldCapacity);
	DM()->updateGold(_goldCount);

	_goldCountText->setString(StringUtils::format("%d / %d", _goldCount, _goldCapacity));
	_goldBar->setPercent((_goldCount*100.0)/_goldCapacity);
};

void HomeHubLayer::addWood(int count) {

	//判断是否超过最大容量 
	int newCount = _woodCount + count;
	_woodCount = MIN(newCount, _woodCapacity);
	DM()->updateGold(_woodCount);

	_woodCountText->setString(StringUtils::format("%d / %d", _woodCount, _woodCapacity));
	_woodBar->setPercent((_woodCount*100.0)/_woodCapacity);
};

void HomeHubLayer::addPlayerExp(int count) {

	DM()->updatePlayerExp(count);
	loadData();

	_playerLevel->setString(GM()->getIntToStr(_level));
	_playerBar->setPercent((_exp*100.0)/_expRequire);
};

void HomeHubLayer::setGoldCapacity(int count) {

	_goldCapacity = count;
	DM()->updateGoldCapacity(_goldCapacity);

	_goldCountText->setString(StringUtils::format("%d / %d", _goldCount, _goldCapacity));
	_goldBar->setPercent((_goldCount*100.0)/_goldCapacity);
};

void HomeHubLayer::setWoodCapacity(int count) {

	_woodCapacity = count;
	DM()->updateGoldCapacity(_woodCapacity);

	 _woodCountText->setString(StringUtils::format("%d / %d", _woodCount, _woodCapacity));
	_woodBar->setPercent((_woodCount*100.0)/_woodCapacity);
};

void HomeHubLayer::setMapLayer(Layer* layer) {

	_mapLayer = layer;
};

void HomeHubLayer::btnCallback(Ref* sender, Widget::TouchEventType type) {

	if(type==Widget::TouchEventType::ENDED) {

		//测试
		//addGold(100);
		//addWood(100);
		//addPlayerExp(100);
		//setGoldCapacity(2000);
		//setWoodCapacity(2000);

		Button* btn = (Button*)sender;
		auto name = btn->getName();
		if(name == "WorldButton") {
			log("WorldButton");

			GM()->enterWorldScene();
		}
		else if(name == "BuildButton") {
			log("BuildButton");

			auto buildDialog = NewBuildDialog::create();
			this->getParent()->addChild(buildDialog, 99);
		}
	}
};