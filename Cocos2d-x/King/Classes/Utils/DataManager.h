/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	: ���ݹ���
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
	ValueVector _player;			//�����Ϣ
	ValueVector _playerLevelExp;	//��ҵȼ�����
	ValueVector _town;				//�ǳ���Ϣ
	ValueVector _miwu;				//������Ϣ

	ValueVector _buildingInfo;		// ���н�����Ϣ
	ValueVector _building;			// ��ҽ�����Ϣ
	ValueVector _buildingLimit;		// �������Ʊ�	

	ValueVector _soilderInfo;		// ����ʿ����Ϣ
	ValueVector _soilder;			// ���ʿ����Ϣ
	ValueVector _soilderLimit;		// ʿ���������Ʊ�

	ValueVector _heroInfo;			// ����Ӣ����Ϣ
	ValueVector _hero;				// Ӣ����Ϣ
	ValueVector _skillInfo;			// ���м�����Ϣ

	ValueVector _battleBuilding;	// �ؿ���ʩ

	int _baseID;					// ˾���ID�������±�
	int _campID;					// ��Ӫ��ID�������±�
	int _labID;						// �о���ID�������±�

public:
	// ����Vector�±������ID
	map<string, int> _indexPlayerLevel;		//Level���±�
	map<string, int> _indexTown;			//Town���±�
	map<string, int> _indexMiwu;            //MiwuID���±�

	map<string, int> _indexBuilding;        // ID���±�
	map<string, int> _indexBuildingInfo;    // BuildingID���±�
	map<string, int> _indexBuildingLimit;   // ˾�Level���±�

	map<string, int> _indexSoilder;         // ID���±�
	map<string, int> _indexSoilderInfo;     // SoilderID���±�
	map<string, int> _indexSoilderLimit;    // ��ӪLevel���±�

	map<string, int> _indexHero;            // ID���±�
	map<string, int> _indexHeroInfo;        // HeroID���±�
	map<string, int> _indexSkillInfo;       // SkillID���±�

public:
	void loadPlayerInfo();					//���������Ϣ
	void loadPlayerLevelInfo();				//������ҵȼ���Ϣ	
	void loadTownInfo();					// ���سǳ���Ϣ
	void loadMiwuInfo();					// ����������Ϣ
	void loadBuildingInfo();				// ���ؽ�����Ϣ
	void loadBuildingLimitInfo();			// ���ؽ������Ʊ���Ϣ��˾��ȼ���Ӧ������������

	void loadSoilderInfo();					// ����ʿ����Ϣ
	void loadSoilderLimitInfo();			//���ر�Ӫʿ���������Ʊ�
									
	void loadHeroInfo();					// ����Ӣ����Ϣ
					
	void loadSkillInfo();					// ���ؼ�����Ϣ

	void loadBattleInfo();					// ���عؿ���Ϣ


public:
	void updateGold(int count);				//���½��
	void updateWood(int count);				//����ľ��
	void updateGoldCapacity(int count);		//���½������
	void updateWoodCapacity(int count);		//����ľ������
	void updateRing(int count);				//���½���
	void updatePlayerExp(int count);		//������Ҿ���

	int getPlayerExpRequire(int level);				//��ȡ��ҵĵȼ�����							
	ValueMap& getBuildingInfo(int buildingID);		// ���ݽ���ID����ȡ������Ϣ
	void bindingIndex(ValueVector &data, map<string, int>& index, string ID);// ���±�


};

#endif // !_DATAMANAGER_H__



