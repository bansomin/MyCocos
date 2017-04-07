/*************************BEGIN****************************************************
Created by HAO on 2017/04/05
BRIEF	: 全局
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef long long LL;

// 相关数值
//static const float  EPS = 1e-6;
//static const float  INF = 0x7fffffff;
static const float  LIMIT_DELTA = 10.0f;
static const float  MAP_X = 1005;
static const float  MAP_Y = 1373;
static const float  SX = 1030;
static const float  SY = 1400;
static const float  TILED_WIDTH = 45;
static const float  TILED_HEIGHT = 32.5;
static const int    TILED_TOTAL_X = 38;
static const int    TILED_TOTAL_Y = 38;
//static const CCSize TILED_SIZE = CCSize(45, 32.5);
static const int DX[] = {1, 1, 1, 0, -1, -1, -1, 0, 0};
static const int DY[] = {1, 0, -1, -1, -1, 0, 1, 1, 0};

//地图城池状态
static const int TOWN_TYPE_HOME = 1;		//玩家城池
static const int TOWN_TYPE_CHAPTER = 1;		//玩家城池
static const int TOWN_TYPE_LIBERATE = 1;		//玩家城池

												// 迷雾状态
static const int MIWU_TYPE_LOCK = 1;				// 未解锁
static const int MIWU_TYPE_UNLOCK = 2;				// 已解锁

													// 进入关卡状态
static const int CHAPTER_TYPE_SEEK = 1;				// 侦查
static const int CHAPTER_TYPE_FIGHT = 1;			// 进攻

													// 收获状态
static const int HARVEST_TYPE_GOLD = 1;				// 收获金币
static const int HARVEST_TYPE_WOOD = 2;				// 收获木材
static const int HARVEST_TYPE_BOTH = 3;				// 收获金币、木材

													// 建筑类型											
static const int BUILDING_TYPE_BaseTower = 1;		// 司令部
static const int BUILDING_TYPE_Raider = 2;			// 雷达
static const int BUILDING_TYPE_HeroHotel = 3;		// 英雄旅馆
static const int BUILDING_TYPE_Camp = 4;			// 兵营
static const int BUILDING_TYPE_ResearchLab = 5;		// 研究所
static const int BUILDING_TYPE_MineFactory = 6;		// 采矿场
static const int BUILDING_TYPE_WoodFactory = 7;		// 木材厂
static const int BUILDING_TYPE_ArrowTower = 8;		// 箭塔
static const int BUILDING_TYPE_Cannon = 9;			// 炮塔
static const int BUILDING_TYPE_Laser = 10;			// 激光炮

													// 建造状态
static const int BUILDING_STATE_FINISHED = 1;		// 已建成
static const int BUILDING_STATE_BUILDING = 2;		// 正在建设

													// 士兵类型
static const int SOILDER_TYPE_FIGHTER = 1;			// 人类士兵
static const int SOILDER_TYPE_BOWMAN = 2;			// 精灵弓箭手
static const int SOILDER_TYPE_GUNNER = 3;			// 矮人炮手
static const int SOILDER_TYPE_MEAT = 4;				// 兽人肉盾

													// 英雄类型
static const int HERO_TYPE_ARAGORN = 1;				// Aragorn

													// 英雄状态
static const int HERO_STATE_REST = 1;				// 休息中
static const int HERO_STATE_BATTLE = 2;				// 参战中

													// 游戏结束
static const int GAME_OVER_SUCCESS = 1;				// 胜利
static const int GAME_OVER_FAILED = 2;				// 失败

													//动画
													// 士兵动画
static const char* ANIM_FIGHTER = "animation/Anim_Fighter/Anim_Fighter.ExportJson";
static const char* ANIM_BOWMAN = "animation/Anim_Bowman/Anim_Bowman.ExportJson";
static const char* ANIM_GUNNER = "animation/Anim_Gunner/Anim_Gunner.ExportJson";
static const char* ANIM_MEATSHIELD = "animation/Anim_MeatShield/Anim_MeatShield.ExportJson";
// 士兵动画名称
static const char* ANIM_NAME_FIGHTER = "Anim_Fighter";
static const char* ANIM_NAME_BOWMAN = "Anim_Bowman";
static const char* ANIM_NAME_GUNNER = "Anim_Gunner";
static const char* ANIM_NAME_MEATSHIELD = "Anim_MeatShield";

// 英雄动画
static const char* ANIM_HERO_ARAGORN = "animation/Anim_Hero_Aragorn/Anim_Hero_Aragorn.ExportJson";
// 英雄动画名称
static const char* ANIM_NAME_ARAGORN = "Anim_Hero_Aragorn";

// 技能动画
static const char* ANIM_SKILL_1 = "animation/Effect0/Effect.ExportJson";
static const char* ANIM_SKILL_2 = "animation/Effort1/Effort1.ExportJson";
// 技能名称
static const char* ANIM_NAME_SKILL_1 = "Effect";
static const char* ANIM_NAME_SKILL_2 = "Effort1";

// 图片
// Background
static const char* IMG_BG_MAP = "common/1.png";		
static const char* IMG_LOADING_BG = "images/background/LoadingBG.png";
static const char* IMG_WORLD_BG = "images/background/WorldBG.png";
static const char* IMG_HOME_BG = "images/background/HomeBG.png";
static const char* IMG_CHAPTER_BG = "images/background/ChapterBG.png";
static const char* IMG_GRAY_BG = "images/background/GrayBG.png";

#endif // !__CONFIG_H__

