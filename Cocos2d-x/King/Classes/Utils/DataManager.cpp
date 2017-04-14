#include "DataManager.h"

//use
#include "Utils\Config.h"
#include "Utils\DBManager.h"
#include "Utils\GlobalManager.h"

DataManager* DataManager::_instance = nullptr;
DataManager* DataManager::getInstance() {
	if(_instance == nullptr) {
		_instance = new DataManager();
		_instance->init();
	}

	return _instance;
};

DataManager::DataManager() {

	_indexPlayerLevel.clear();
};

DataManager::~DataManager() {
	_instance = nullptr;
};

bool DataManager::init() {

	loadPlayerInfo();				//加载玩家信息_player
	loadPlayerLevelInfo();			//加载玩家等级信息_playerLevelExp

	loadTownInfo();					//加载城池信息_town
	loadMiwuInfo();					//加载迷雾信息
	loadBuildingInfo();				//加载建筑信息
	loadBuildingLimitInfo();		//加载建筑限制表信息：司令部等级对应建筑数量限制

	loadSoilderInfo();				//加载士兵信息
	loadSoilderLimitInfo();			//加载兵营士兵数量限制表

	loadHeroInfo();					// 加载英雄信息

	loadSkillInfo();				// 加载技能信息

	loadBattleInfo();				// 加载关卡信息

	return true;
};

//加载玩家信息（初始_player）
void DataManager::loadPlayerInfo() {
	log("DataManager : loadPlayerInfo");

	string sql = "select * from PlayerInfo";
	_player = DBM()->executeQuery(sql);
};

//加载玩家等级信息(初始_playerLevelExp)
void DataManager::loadPlayerLevelInfo() {
	log("DataManager : loadPlayerLevelInfo");

	DBM()->loadCsvData(CSV_PLAYERLEVELINFO, _playerLevelExp);
	bindingIndex(_playerLevelExp, _indexPlayerLevel, "Level");
};

// 加载城池信息
void DataManager::loadTownInfo() {
	log("DataManager : loadTownInfo");

	DBM()->loadCsvData(CSV_TOWNINFO, _town);
	bindingIndex(_town, _indexTown, "TownID");

	string sql = "select * from TownStateInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();
		
		string id = mapData["TownID"].asString();
		ValueMap& map = _town[_indexTown[id]].asValueMap();

		map["Type"] = mapData["Type"].asString();
		map["LastHarvest"] = mapData["LastHarvest"].asString();
	}
};

// 加载迷雾信息
void DataManager::loadMiwuInfo() {
	log("DataManager : loadMiwuInfo");

	DBM()->loadCsvData(CSV_MIWUINFO, _miwu);
	bindingIndex(_miwu, _indexMiwu, "MiwuID");

	string sql = "select * from MiwuStateInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		string id = mapData["MiwuID"].asString();
		ValueMap& map = _miwu[_indexMiwu[id]].asValueMap();

		map["Type"] = mapData["Type"].asString();
	}
};

// 加载建筑信息
void DataManager::loadBuildingInfo() {
	log("DataManager : loadBuildingInfo");

	DBM()->loadCsvData(CSV_BUILDINGINFO, _buildingInfo);
	bindingIndex(_buildingInfo, _indexBuildingInfo, "BuildingID");

	string sql = "select * from BuildingListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;

		//i==0 为字段开头
		if(i==0) {
			map["BuildingID"] = 0;
			_building.push_back((Value)map);
			continue;
		}

		//[1] 根据BuildingID，在 _buildingInfo 中查找对应建筑的信息
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] 读取玩家建筑信息
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		//[3] 读取特殊建筑的ID
		if(map["Type"].asInt() == BUILDING_TYPE_BaseTower) {
			_baseID = i;	//数组下标
		}
		else if(map["Type"].asInt()==BUILDING_TYPE_Camp) {
			_campID = i;
		}
		else if(map["Type"].asInt()==BUILDING_TYPE_ResearchLab) {
			_labID = i;
		}
		_building.push_back((Value)map);
	}

	bindingIndex(_building, _indexBuilding, "ID");
};

// 加载建筑限制表信息：司令部等级对应建筑数量限制
void DataManager::loadBuildingLimitInfo() {
	log("DataManager : loadBuildingLimitInfo");

	DBM()->loadCsvData(CSV_BUILDINGLIMITINFO, _buildingLimit);
	bindingIndex(_buildingLimit, _indexBuildingLimit, "Level");
};

// 加载士兵信息
void DataManager::loadSoilderInfo() {
	log("DataManager : loadSoilderInfo");

	DBM()->loadCsvData(CSV_SOILDER_INFO, _soilderInfo);
	bindingIndex(_soilderInfo, _indexSoilderInfo, "SoilderID");

	string sql = "select * from SoilderListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;
		//i==0 为字段开头

		if(i==0) {
			map["SoilderID"] = 0;
			_soilder.push_back((Value)map);
			continue;
		}

		//[1] 根据SoilderID，在 _soilderInfo 中查找对应士兵的信息
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] 读取玩家士兵信息
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		_soilder.push_back((Value)map);
	}

	bindingIndex(_soilder, _indexSoilder, "ID");

};

//加载兵营士兵数量限制表
void DataManager::loadSoilderLimitInfo() {
	log("DataManager : loadSoilderLimitInfo");

	DBM()->loadCsvData(CSV_SOILDER_LIMITINFO, _soilderLimit);
	bindingIndex(_soilderLimit, _indexSoilderLimit, "Level");
};

// 加载英雄信息
void DataManager::loadHeroInfo() {
	log("DataManager : loadHeroInfo");

	DBM()->loadCsvData(CSV_HERO_INFO, _heroInfo);
	bindingIndex(_heroInfo, _indexHeroInfo, "HeroID");

	string sql = "select * from HeroListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;

		//i==0 为字段开头
		if(i==0) {
			map["HeroID"] = 0;
			_hero.push_back((Value)map);
			continue;
		}

		//[1] 根据HeroID，在 _HeroInfo 中查找对应英雄的信息
		int id = GM()->getStrToInt(mapData["HeroID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] 读取玩家英雄信息
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		_hero.push_back((Value)map);
	}

	bindingIndex(_hero, _indexHero, "ID");
};

// 加载技能信息
void DataManager::loadSkillInfo() {
	log("DataManager : loadSkillInfo");

	DBM()->loadCsvData(CSV_SKILL_INFO, _skillInfo);
	bindingIndex(_skillInfo, _indexSkillInfo, "SkillID");
};

// 加载关卡信息
void DataManager::loadBattleInfo() {
	log("DataManager : loadBattleInfo");

	DBM()->loadCsvData(CSV_BATTLE_INFO, _battleBuilding);

	for(int i = 0; i<(int)_battleBuilding.size(); i++) {
		ValueMap& mapData = _battleBuilding.at(i).asValueMap();

		//[1] 根据BuildingID，在 _buildingInfo 中查找对应建筑的信息
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			mapData[key] = value;
		}
	}
};

//根据建筑ID，获取建筑信息
ValueMap& DataManager::getBuildingInfo(int buildingID) {

	string id = GM()->getIntToStr(buildingID);
	return _buildingInfo[_indexBuildingInfo[id]].asValueMap();
};

//获取玩家的等级需求
int DataManager::getPlayerExpRequire(int level) {

	string levelStr = StringUtils::format("%d", level);
	return (_playerLevelExp[_indexPlayerLevel[levelStr]].asValueMap())["ExpRequire"].asInt();
};

//更新金币
void DataManager::updateGold(int count) {
	log("DataManager::updateGold");

	ValueMap& map = _player.at(1).asValueMap();
	map["GoldCount"] = count;

	//更新数据库
	string sql = "update PlayerInfo set GoldCount='"
				 + map["GoldCount"].asString()
				 + "' where ID="
				 + map["ID"].asString()+";";
	log("SQL = %s", sql.c_str());
	DBM()->executeUpdate(sql);
};

//更新木材资源
void DataManager::updateWood(int count) {
	log("DataManager::updateWood");

	ValueMap& map = _player.at(1).asValueMap();
	map["WoodCount"] = count;

	//更新数据库
	string sql = "update PlayerInfo set WoodCount='"
				+ map["WoodCount"].asString()
				+ "' where ID="
				+ map["ID"].asString()+";";
	log("SQL = %s", sql.c_str());
	DBM()->executeUpdate(sql);
};

//更新金币容量
void DataManager::updateGoldCapacity(int count) {
	log("DataManager::updateGoldCapacity");

	ValueMap& map = _player.at(1).asValueMap();
	map["GoldCapacity"] = count;

	//更新数据库
	string sql = "update PlayerInfo set GoldCapacity='"
				+ map["GoldCapacity"].asString()
				+ "' where ID="
				+ map["ID"].asString()+";";
	log("SQL = %s", sql.c_str());
	DBM()->executeUpdate(sql);
};

//更新木材容量
void DataManager::updateWoodCapacity(int count) {
	log("DataManager::updateWoodCapacity");

	ValueMap& map = _player.at(1).asValueMap();
	map["WoodCapacity"] = count;

	//更新数据库
	string sql = "update PlayerInfo set WoodCapacity='"
				+ map["WoodCapacity"].asString()
				+ "' where ID="
				+ map["ID"].asString()+";";
	log("SQL = %s", sql.c_str());
	DBM()->executeUpdate(sql);
};

//更新奖牌
void DataManager::updateRing(int count) {
	log("DataManager::updateRing");

	ValueMap& map = _player.at(1).asValueMap();
	map["RingCount"] = map["RingCount"].asInt() + count;

	//更新数据库
	string sql = "update PlayerInfo set RingCount='"
				+ map["RingCount"].asString()
				+ "' where ID="
				+ map["ID"].asString()+";";
	log("SQL = %s", sql.c_str());
	DBM()->executeUpdate(sql);
};

//更新玩家经验
void DataManager::updatePlayerExp(int count) {
	log("DataManager::updatePlayerExp");

	ValueMap& map = _player.at(1).asValueMap();
	int preExp = map["Exp"].asInt();
	int newExp = preExp + count;
	int expRequire = getPlayerExpRequire(map["Level"].asInt());

	if(expRequire == -1) {	
		log("EXP_Maximum");
	}
	else {
		//升级
		if(newExp >= expRequire) {
			map["Level"] = map["Level"].asInt() + 1;
			newExp -= expRequire;
		}
		map["Exp"] = newExp;

		//更新数据库
		string sql = "update PlayerInfo set Level='"+map["Level"].asString()
					+ "', Exp='"
					+ map["Exp"].asString()
					+ "' where ID="
					+ map["ID"].asString()+";";
		log("SQL = %s", sql.c_str());
		DBM()->executeUpdate(sql);
	}
};

// 更新设施位置
void DataManager::updateBuildingPos(int ID, Vec2 pos) {

	ValueMap& map = _building.at(_indexBuilding[GM()->getIntToStr(ID)]).asValueMap();
	map["PositionX"] = (int)pos.x;
	map["PositionY"] = (int)pos.y;

	// 更新设施位置(sqlite)
	string sql =  "update BuildingListInfo set PositionX='"+map["PositionX"].asString()
				+ "', PositionY='"+map["PositionY"].asString()
				+ "' where ID="+map["ID"].asString()+";";
	DBM()->executeUpdate(sql);
};

// 绑定下标
void DataManager::bindingIndex(ValueVector &data, map<string, int>& index, string ID) {

	for(int i = 0; i < (int)data.size(); i++) {
		ValueMap map = data.at(i).asValueMap();
		index[map[ID].asString()] = i;
	}
};



