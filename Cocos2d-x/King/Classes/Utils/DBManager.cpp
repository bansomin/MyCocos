#include "DBManager.h"

#include "Utils\Config.h"
#include "Utils\GlobalManager.h"
#include "Helper\CSVParser\CSVParser.h"
using namespace CSVParser;

DBManager* DBManager::_instance = nullptr;

DBManager* DBManager::getInstance() {
	if(_instance == nullptr) {
		_instance = new DBManager();
		_instance->init();
	}

	return _instance;
};

DBManager::DBManager() {

};

DBManager::~DBManager() {
	_instance = nullptr;
};

bool DBManager::init() {

	return true;
};

//����Table
void DBManager::createTable() {
	log("createTable");

	string path = FileUtils::getInstance()->getWritablePath() + "/" + DB_NAME;
	if(!FileUtils::getInstance()->isFileExist(path)) {
		log("Create DB!");

		createPlayerInfo();			//��ʼ���Player����
		createTownStateInfo();		//��ʼTown����
		createMiwuStateInfo();		//��ʼMiWU����
		createBuildingListInfo();	//����BuildingList����
		createSoilderListInfo();	//����SoilderList����
		createHeroListInfo();		//����HeroList����
	}
	else {
		log("DB existed!");
	}
};

//�����û�����
void DBManager::createPlayerInfo() {
	log("createPlayerInfo");

	ValueVector data;
	loadCsvData(CSV_PLAYERINFO, data);

	string sql = "create table PlayerInfo(ID integer primary key autoincrement, Name, Level, Exp, RingCount, GoldCount, WoodCount, GoldCapacity, WoodCapacity)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into PlayerInfo values("
			+map["ID"].asString()+", '"
			+map["Name"].asString()+"', '"
			+map["Level"].asString()+"', '"
			+map["Exp"].asString()+"', '"
			+map["RingCount"].asString()+"', '"
			+map["GoldCount"].asString()+"', '"
			+map["WoodCount"].asString()+"', '"
			+map["GoldCapacity"].asString()+"', '"
			+map["WoodCapacity"].asString()+"')";

		executeUpdate(sql);
	}
};

//����������
void DBManager::createTownStateInfo() {
	log("createTownStateInfo");

	ValueVector data;
	loadCsvData(CSV_TOWNSTATEINFO, data);

	//��ǰʱ�䣨s��
	string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
	string sql = "create table TownStateInfo(TownID integer primary key autoincrement, Type, LastHarvest)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into TownStateInfo values("
			+map["TownID"].asString()+", '"
			+map["Type"].asString()+"', '"
			+timeStamp+"')";

		executeUpdate(sql);
	}
};

//����MiWu����
void DBManager::createMiwuStateInfo() {
	log("createMiwuStateInfo");

	ValueVector data;
	loadCsvData(CSV_MIWUSTATEINFO, data);

	string sql = "create table MiwuStateInfo(MiwuID integer primary key autoincrement, Type)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into MiwuStateInfo values("
			+map["MiwuID"].asString()+", '"
			+map["Type"].asString()+"')";

		executeUpdate(sql);
	}
};

//����BuildingList����
void DBManager::createBuildingListInfo() {
	log("createBuildingListInfo");

	ValueVector data;
	loadCsvData(CSV_BUILDINGLISTINFO, data);

	//��ǰʱ�䣨s��
	string timeStamp = StringUtils::format("%d", GM()->getTimeStamp());
	string sql = "create table BuildingListInfo(ID integer primary key autoincrement, BuildingID, PositionX, PositionY, BuildState, LastBuildTime, LastGoldHarvest, LastWoodHarvest)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into BuildingListInfo values("
			+map["ID"].asString()+", '"
			+map["BuildingID"].asString()+"', '"
			+map["PositionX"].asString()+"', '"
			+map["PositionY"].asString()+"', '"
			+map["BuildState"].asString()+"', '"
			+timeStamp+"', '"
			+timeStamp+"', '"
			+timeStamp+"')";

		executeUpdate(sql);
	}
};

//����SoilderList����
void DBManager::createSoilderListInfo() {
	log("createSoilderListInfo");

	ValueVector data;
	loadCsvData(CSV_SOILDER_LISTINFO, data);

	//��ǰʱ�䣨s��
	//string timeStamp = StringUtils::format("%d", GM()->getTimeStamp());
	string sql = "create table SoilderListInfo(ID integer primary key autoincrement, SoilderID, Count)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into SoilderListInfo values("
			+map["ID"].asString()+", '"
			+map["SoilderID"].asString()+"', '"
			+map["Count"].asString()+"')";

		executeUpdate(sql);
	}
};

//����HeroList����
void DBManager::createHeroListInfo() {
	log("createHeroListInfo");

	ValueVector data;
	loadCsvData(CSV_HERO_LISTINFO, data);

	//��ǰʱ�䣨s��
	//string timeStamp = StringUtils::format("%d", GM()->getTimeStamp());
	string sql = "create table HeroListInfo(ID integer primary key autoincrement, HeroID, Exp, State)";
	executeUpdate(sql);

	log("Size = %d", (int)data.size());
	for(int i = 1; i<(int)data.size(); i++) {
		ValueMap& map = data.at(i).asValueMap();
		sql = "insert into HeroListInfo values("
			+map["ID"].asString()+", '"
			+map["HeroID"].asString()+"', '"
			+map["Exp"].asString()+"', '"
			+map["State"].asString()+"')";

		executeUpdate(sql);
	}
};





//����csv�ļ�
void DBManager::loadCsvData(string file, ValueVector& data) {

	Csv csv = Csv(file.c_str());
	for(int i = 0; i < csv.getRowCount(); i++) {
		ValueMap map;
		for(int j = 0; j < csv[i].size(); j++) {
			map[csv[0][j]] = csv[i][j];
		}
		data.push_back((Value)map);
	}
};

bool DBManager::open() {

	string path = FileUtils::getInstance()->getWritablePath() + "/" + DB_NAME;
	log("Opening...path = ************ %s", path.c_str());

	int ret = sqlite3_open(path.c_str(), &_pdb);
	if(ret != SQLITE_OK) {
		const char* errmsg = sqlite3_errmsg(_pdb);
		log("sqlite open error : %s", errmsg);
		sqlite3_close(_pdb);
		return false;
	}
	log("sqlite opened.");

	return true;
};

void DBManager::close() {

	sqlite3_close(_pdb);
	_pdb = nullptr;
};

//int sqlite3_get_table(
//sqlite3 *db,          /* An open database */
//const char *zSql,     /* SQL to be evaluated */
//char ***pazResult,    /* Results of the query */
//int *pnRow,           /* Number of result rows written here */
//int *pnColumn,        /* Number of result columns written here */
//char **pzErrmsg       /* Error msg written here */
//);
// ��ѯ���ݿ�
ValueVector DBManager::executeQuery(std::string sql) {
	
	ValueVector v;
	if(open()) {
		char** table;   // ��ѯ���
		int r, c;       // ����������  
		sqlite3_get_table(_pdb, sql.c_str(), &table, &r, &c, nullptr);

		// ��0�У�0 ~ c-1����Ϊ�ֶ���
		// ��1~r�У�c ~ 2*c-1������һ����¼
		for(int i = 0; i<=r; i++) {
			ValueMap map;
			for(int j = 0; j < c; j++) {
				map[table[j]] = table[i * c+j];
				//log("executeQuery : map[x] : %s table[x] �� %s", table[j], table[i*c+j]);
			}
			v.push_back((Value)map);
		}
		// �ǵ��ͷŲ�ѯ��
		sqlite3_free_table(table);
	}
	return v;
};

//int sqlite3_exec(
//	sqlite3* ppDb,                             /* An open database */
//	const char *sql,                           /* SQL to be evaluated */
//	int(*callback)(void*, int, char**, char**),  /* Callback function */
//	void *,                                    /* 1st argument to callback */
//	char **errmsg                              /* Error msg written here */
//);
//�������ݿ�
void DBManager::executeUpdate(string sql) {
	log("executeUpdate");

	if(open() == true) {
		int ret = sqlite3_exec(_pdb, sql.c_str(), nullptr, nullptr, nullptr);
		if(ret != SQLITE_OK) {
			log("update data failed!");
		}
		log("Update Completed!");
		close();
	}
};			

