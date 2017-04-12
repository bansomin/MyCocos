/*************************BEGIN****************************************************
Created by HAO on 2017/04/10
BRIEF	: 数据库管理
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
	void createTable();					//创建Table

	void createPlayerInfo();			//创建Player数据
	void createTownStateInfo();			//创建Town数据
	void createMiwuStateInfo();			//创建MiWu数据
	void createBuildingListInfo();		//创建BuildingList数据
	void createSoilderListInfo();		//创建SoilderList数据
	void createHeroListInfo();			//创建SoilderList数据

	bool open();						//打开关闭数据库
	void close();
	ValueVector executeQuery(string sql);	//查询数据库	
	void executeUpdate(string sql);			//更新数据库

	void loadCsvData(string file, ValueVector& data);	//加载csv文件
};

#endif // !_DBMANAGER_H__