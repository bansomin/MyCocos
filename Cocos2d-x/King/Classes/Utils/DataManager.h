/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	: 数据管理
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _DATAMANAGER_H__
#define	_DATAMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

#define DM() DataManager::getInstance()

class DataManager: public Ref{

public:
	DataManager();
	~DataManager();
	virtual bool init();
	static DataManager* getInstance(); 

private:
	static DataManager* _instance;

public:
	ValueVector _player;			//玩家信息
	ValueVector _playerLevelExp;	//玩家等级经验
	ValueVector _town;				//城池信息
	ValueVector _miwu;				//迷雾信息

	ValueVector _buildingInfo;		// 所有建筑信息
	ValueVector _building;			// 玩家建筑信息
	ValueVector _buildingLimit;		// 建筑限制表	

	ValueVector _soilderInfo;		// 所有士兵信息
	ValueVector _soilder;			// 玩家士兵信息
	ValueVector _soilderLimit;		// 士兵数量限制表

	ValueVector _heroInfo;			// 所有英雄信息
	ValueVector _hero;				// 英雄信息
	ValueVector _skillInfo;			// 所有技能信息

	ValueVector _battleBuilding;	// 关卡设施

	int _baseID;					// 司令部的ID，数组下标
	int _campID;					// 兵营的ID，数组下标
	int _labID;						// 研究所ID，数组下标

public:
	// 关联Vector下标和数据ID
	map<string, int> _indexPlayerLevel;		//Level与下标
	map<string, int> _indexTown;			//Town与下标
	map<string, int> _indexMiwu;            //MiwuID与下标

	map<string, int> _indexBuilding;        // ID与下标
	map<string, int> _indexBuildingInfo;    // BuildingID与下标
	map<string, int> _indexBuildingLimit;   // 司令部Level与下标

	map<string, int> _indexSoilder;         // ID与下标
	map<string, int> _indexSoilderInfo;     // SoilderID与下标
	map<string, int> _indexSoilderLimit;    // 兵营Level与下标

	map<string, int> _indexHero;            // ID与下标
	map<string, int> _indexHeroInfo;        // HeroID与下标
	map<string, int> _indexSkillInfo;       // SkillID与下标

public:
	void loadPlayerInfo();					//加载玩家信息
	void loadPlayerLevelInfo();				//加载玩家等级信息	
	void loadTownInfo();					// 加载城池信息
	void loadMiwuInfo();					// 加载迷雾信息
	void loadBuildingInfo();				// 加载建筑信息
	void loadBuildingLimitInfo();			// 加载建筑限制表信息：司令部等级对应建筑数量限制

	void loadSoilderInfo();					// 加载士兵信息
	void loadSoilderLimitInfo();			//加载兵营士兵数量限制表
									
	void loadHeroInfo();					// 加载英雄信息
					
	void loadSkillInfo();					// 加载技能信息

	void loadBattleInfo();					// 加载关卡信息


public:
	void updateGold(int count);				//更新金币
	void updateWood(int count);				//更新木材
	void updateGoldCapacity(int count);		//更新金币容量
	void updateWoodCapacity(int count);		//更新木材容量
	void updateRing(int count);				//更新奖牌
	void updatePlayerExp(int count);		//更新玩家经验

	int getPlayerExpRequire(int level);				//获取玩家的等级需求							
	ValueMap& getBuildingInfo(int buildingID);		// 根据建筑ID，获取建筑信息
	void bindingIndex(ValueVector &data, map<string, int>& index, string ID);// 绑定下标


};

#endif // !_DATAMANAGER_H__



