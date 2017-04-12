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
	log("####################################################");

	loadPlayerInfo();				//���������Ϣ_player
	loadPlayerLevelInfo();			//������ҵȼ���Ϣ_playerLevelExp

	loadTownInfo();					//���سǳ���Ϣ_town
	loadMiwuInfo();					//����������Ϣ
	loadBuildingInfo();				//���ؽ�����Ϣ
	loadBuildingLimitInfo();		//���ؽ������Ʊ���Ϣ��˾��ȼ���Ӧ������������

	loadSoilderInfo();				//����ʿ����Ϣ
	loadSoilderLimitInfo();			//���ر�Ӫʿ���������Ʊ�

	loadHeroInfo();					// ����Ӣ����Ϣ

	loadSkillInfo();				// ���ؼ�����Ϣ

	loadBattleInfo();				// ���عؿ���Ϣ

	return true;
};

//���������Ϣ����ʼ_player��
void DataManager::loadPlayerInfo() {
	log("DataManager : loadPlayerInfo");

	string sql = "select * from PlayerInfo";
	_player = DBM()->executeQuery(sql);
};

//������ҵȼ���Ϣ(��ʼ_playerLevelExp)
void DataManager::loadPlayerLevelInfo() {
	log("DataManager : loadPlayerLevelInfo");

	DBM()->loadCsvData(CSV_PLAYERLEVELINFO, _playerLevelExp);
	bindingIndex(_playerLevelExp, _indexPlayerLevel, "Level");
};

// ���سǳ���Ϣ
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

// ����������Ϣ
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

// ���ؽ�����Ϣ
void DataManager::loadBuildingInfo() {
	log("DataManager : loadBuildingInfo");

	DBM()->loadCsvData(CSV_BUILDINGINFO, _buildingInfo);
	bindingIndex(_buildingInfo, _indexBuildingInfo, "BuildingID");

	string sql = "select * from BuildingListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;

		//i==0 Ϊ�ֶο�ͷ
		if(i==0) {
			map["BuildingID"] = 0;
			_building.push_back((Value)map);
			continue;
		}

		//[1] ����BuildingID���� _buildingInfo �в��Ҷ�Ӧ��������Ϣ
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] ��ȡ��ҽ�����Ϣ
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		//[3] ��ȡ���⽨����ID
		if(map["Type"].asInt() == BUILDING_TYPE_BaseTower) {
			_baseID = i;	//�����±�
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

// ���ؽ������Ʊ���Ϣ��˾��ȼ���Ӧ������������
void DataManager::loadBuildingLimitInfo() {
	log("DataManager : loadBuildingLimitInfo");

	DBM()->loadCsvData(CSV_BUILDINGLIMITINFO, _buildingLimit);
	bindingIndex(_buildingLimit, _indexBuildingLimit, "Level");
};

// ����ʿ����Ϣ
void DataManager::loadSoilderInfo() {
	log("DataManager : loadSoilderInfo");

	DBM()->loadCsvData(CSV_SOILDER_INFO, _soilderInfo);
	bindingIndex(_soilderInfo, _indexSoilderInfo, "SoilderID");

	string sql = "select * from SoilderListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;
		//i==0 Ϊ�ֶο�ͷ

		if(i==0) {
			map["SoilderID"] = 0;
			_soilder.push_back((Value)map);
			continue;
		}

		//[1] ����SoilderID���� _soilderInfo �в��Ҷ�Ӧʿ������Ϣ
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] ��ȡ���ʿ����Ϣ
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		_soilder.push_back((Value)map);
	}

	bindingIndex(_soilder, _indexSoilder, "ID");

};

//���ر�Ӫʿ���������Ʊ�
void DataManager::loadSoilderLimitInfo() {
	log("DataManager : loadSoilderLimitInfo");

	DBM()->loadCsvData(CSV_SOILDER_LIMITINFO, _soilderLimit);
	bindingIndex(_soilderLimit, _indexSoilderLimit, "Level");
};

// ����Ӣ����Ϣ
void DataManager::loadHeroInfo() {
	log("DataManager : loadHeroInfo");

	DBM()->loadCsvData(CSV_HERO_INFO, _heroInfo);
	bindingIndex(_heroInfo, _indexHeroInfo, "HeroID");

	string sql = "select * from HeroListInfo";
	ValueVector data = DBM()->executeQuery(sql);
	for(int i = 0; i<(int)data.size(); i++) {
		ValueMap& mapData = data.at(i).asValueMap();

		ValueMap map;

		//i==0 Ϊ�ֶο�ͷ
		if(i==0) {
			map["HeroID"] = 0;
			_hero.push_back((Value)map);
			continue;
		}

		//[1] ����HeroID���� _HeroInfo �в��Ҷ�ӦӢ�۵���Ϣ
		int id = GM()->getStrToInt(mapData["HeroID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			map[key] = value;
		}

		//[2] ��ȡ���Ӣ����Ϣ
		for(auto it = mapData.begin(); it!=mapData.end(); it++) {
			map[it->first] = it->second.asString();
		}

		_hero.push_back((Value)map);
	}

	bindingIndex(_hero, _indexHero, "ID");
};

// ���ؼ�����Ϣ
void DataManager::loadSkillInfo() {
	log("DataManager : loadSkillInfo");

	DBM()->loadCsvData(CSV_SKILL_INFO, _skillInfo);
	bindingIndex(_skillInfo, _indexSkillInfo, "SkillID");
};

// ���عؿ���Ϣ
void DataManager::loadBattleInfo() {
	log("DataManager : loadBattleInfo");

	DBM()->loadCsvData(CSV_BATTLE_INFO, _battleBuilding);

	for(int i = 0; i<_battleBuilding.size(); i++) {
		ValueMap& mapData = _battleBuilding.at(i).asValueMap();

		//[1] ����BuildingID���� _buildingInfo �в��Ҷ�Ӧ��������Ϣ
		int id = GM()->getStrToInt(mapData["BuildingID"].asString());
		ValueMap& infoMap = getBuildingInfo(id);
		for(auto it = infoMap.begin(); it!=infoMap.end(); it++) {
			string key = (*it).first;
			string value = (*it).second.asString();
			mapData[key] = value;
		}
	}
};


//���ݽ���ID����ȡ������Ϣ
ValueMap& DataManager::getBuildingInfo(int buildingID) {

	string id = GM()->getIntToStr(buildingID);
	return _buildingInfo[_indexBuildingInfo[id]].asValueMap();
};

//��ȡ��ҵĵȼ�����
int DataManager::getPlayerExpRequire(int level) {

	string levelStr = StringUtils::format("%d", level);
	return (_playerLevelExp[_indexPlayerLevel[levelStr]].asValueMap())["ExpRequire"].asInt();
};

//������Ҿ���
void DataManager::updatePlayerExp(int exp) {

	ValueMap& map = _player.at(1).asValueMap();
	int preExp = map["Exp"].asInt();
	int newExp = preExp + exp;
};

// ���±�
void DataManager::bindingIndex(ValueVector &data, map<string, int>& index, string ID) {

	for(int i = 0; i < (int)data.size(); i++) {
		ValueMap map = data.at(i).asValueMap();
		index[map[ID].asString()] = i;
	}
};



