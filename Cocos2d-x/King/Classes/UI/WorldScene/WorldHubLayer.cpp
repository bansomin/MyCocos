#include "WorldHubLayer.h"

//use
#include "Utils\Config.h"
#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"

WorldHubLayer::WorldHubLayer() {

};

WorldHubLayer::~WorldHubLayer() {

};

bool WorldHubLayer::init() {
	if(!Layer::init()) {
		return false;
	}

	_Wsize = Director::getInstance()->getWinSize();

	this->loadData();
	this->loadUI();

	return true;
};

void WorldHubLayer::loadData() {

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

void WorldHubLayer::loadUI() {

	auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_LAYER_WORLDHUD);
	this->addChild(ui, 0, "UI");

	//HomeButton
	auto worldBtn = (Button*)Helper::seekWidgetByName(ui, "HomeButton");
	worldBtn->addTouchEventListener(CC_CALLBACK_2(WorldHubLayer::btnCallback, this));
	
	//Player
	auto playerName = (Text*)Helper::seekWidgetByName(ui, "PlayerName");
	auto playerLevel = (Text*)Helper::seekWidgetByName(ui, "PlayerLevel");
	auto playerBar = (LoadingBar*)Helper::seekWidgetByName(ui, "PlayerBar");
	playerName->setString(_name);
	playerLevel->setString(GM()->getIntToStr(_level));
	playerBar->setPercent((_exp*100.0)/_expRequire);

	//Gold
	_goldCountText = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
	//_goldCapacityText = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
	_goldBar		= (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
	_goldCountText->setString(StringUtils::format("%d / %d", _goldCount, _goldCapacity));
	//_goldCapacityText->setString("10000");
	_goldBar->setPercent((_goldCount*100.0)/_goldCapacity);

	//Wood
	_woodCountText = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
	//_woodCapacityText = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
	_woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
	_woodCountText->setString(StringUtils::format("%d / %d", _woodCount, _woodCapacity));
	//_woodCapacityText->setString("10000");
	_woodBar->setPercent((_woodCount*100.0)/_woodCapacity);

	//Ring
	auto ringCount = (Text*)Helper::seekWidgetByName(ui, "RingCount");
	ringCount->setString(StringUtils::format("%d", _ringCount));
};

//加金币
void WorldHubLayer::addGold(int count) {

};

//加木头
void WorldHubLayer::addWood(int count) {

};

void WorldHubLayer::btnCallback(Ref* sender, Widget::TouchEventType type) {
	if(type==Widget::TouchEventType::ENDED) {

		DM()->loadPlayerInfo();
		GM()->enterHomeScene();
	}
};