/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	: ���ݿ����
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef _DBMANAGER_H__
#define	_DBMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

//use
#include "Helper\Sqlite3\sqlite3.h"

#define DBM() DBManager::getInstance()

class DBManager : public Ref {

public:
	DBManager();
	~DBManager();
	virtual bool init();
	static DBManager* getInstance();

private:
	static DBManager* _instance;
	sqlite3* _pdb;


public:
	void createTable();					//����Table

	void createPlayerInfo();			//����Player����
	void createTownStateInfo();			//����Town����
	void createMiwuStateInfo();			//����MiWu����
	void createBuildingListInfo();		//����BuildingList����
	void createSoilderListInfo();		//����SoilderList����
	void createHeroListInfo();			//����SoilderList����

	bool open();						//�򿪹ر����ݿ�
	void close();
	ValueVector executeQuery(string sql);	//��ѯ���ݿ�	
	void executeUpdate(string sql);			//�������ݿ�

	void loadCsvData(string file, ValueVector& data);	//����csv�ļ�
};

#endif // !_DBMANAGER_H__