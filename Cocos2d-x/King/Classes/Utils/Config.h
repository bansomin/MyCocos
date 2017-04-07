/*************************BEGIN****************************************************
Created by HAO on 2017/04/05
BRIEF	: ȫ��
VERSION	:
HISTORY	:
***************************END****************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef long long LL;

// �����ֵ
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

//��ͼ�ǳ�״̬
static const int TOWN_TYPE_HOME = 1;		//��ҳǳ�
static const int TOWN_TYPE_CHAPTER = 1;		//��ҳǳ�
static const int TOWN_TYPE_LIBERATE = 1;		//��ҳǳ�

												// ����״̬
static const int MIWU_TYPE_LOCK = 1;				// δ����
static const int MIWU_TYPE_UNLOCK = 2;				// �ѽ���

													// ����ؿ�״̬
static const int CHAPTER_TYPE_SEEK = 1;				// ���
static const int CHAPTER_TYPE_FIGHT = 1;			// ����

													// �ջ�״̬
static const int HARVEST_TYPE_GOLD = 1;				// �ջ���
static const int HARVEST_TYPE_WOOD = 2;				// �ջ�ľ��
static const int HARVEST_TYPE_BOTH = 3;				// �ջ��ҡ�ľ��

													// ��������											
static const int BUILDING_TYPE_BaseTower = 1;		// ˾�
static const int BUILDING_TYPE_Raider = 2;			// �״�
static const int BUILDING_TYPE_HeroHotel = 3;		// Ӣ���ù�
static const int BUILDING_TYPE_Camp = 4;			// ��Ӫ
static const int BUILDING_TYPE_ResearchLab = 5;		// �о���
static const int BUILDING_TYPE_MineFactory = 6;		// �ɿ�
static const int BUILDING_TYPE_WoodFactory = 7;		// ľ�ĳ�
static const int BUILDING_TYPE_ArrowTower = 8;		// ����
static const int BUILDING_TYPE_Cannon = 9;			// ����
static const int BUILDING_TYPE_Laser = 10;			// ������

													// ����״̬
static const int BUILDING_STATE_FINISHED = 1;		// �ѽ���
static const int BUILDING_STATE_BUILDING = 2;		// ���ڽ���

													// ʿ������
static const int SOILDER_TYPE_FIGHTER = 1;			// ����ʿ��
static const int SOILDER_TYPE_BOWMAN = 2;			// ���鹭����
static const int SOILDER_TYPE_GUNNER = 3;			// ��������
static const int SOILDER_TYPE_MEAT = 4;				// �������

													// Ӣ������
static const int HERO_TYPE_ARAGORN = 1;				// Aragorn

													// Ӣ��״̬
static const int HERO_STATE_REST = 1;				// ��Ϣ��
static const int HERO_STATE_BATTLE = 2;				// ��ս��

													// ��Ϸ����
static const int GAME_OVER_SUCCESS = 1;				// ʤ��
static const int GAME_OVER_FAILED = 2;				// ʧ��

													//����
													// ʿ������
static const char* ANIM_FIGHTER = "animation/Anim_Fighter/Anim_Fighter.ExportJson";
static const char* ANIM_BOWMAN = "animation/Anim_Bowman/Anim_Bowman.ExportJson";
static const char* ANIM_GUNNER = "animation/Anim_Gunner/Anim_Gunner.ExportJson";
static const char* ANIM_MEATSHIELD = "animation/Anim_MeatShield/Anim_MeatShield.ExportJson";
// ʿ����������
static const char* ANIM_NAME_FIGHTER = "Anim_Fighter";
static const char* ANIM_NAME_BOWMAN = "Anim_Bowman";
static const char* ANIM_NAME_GUNNER = "Anim_Gunner";
static const char* ANIM_NAME_MEATSHIELD = "Anim_MeatShield";

// Ӣ�۶���
static const char* ANIM_HERO_ARAGORN = "animation/Anim_Hero_Aragorn/Anim_Hero_Aragorn.ExportJson";
// Ӣ�۶�������
static const char* ANIM_NAME_ARAGORN = "Anim_Hero_Aragorn";

// ���ܶ���
static const char* ANIM_SKILL_1 = "animation/Effect0/Effect.ExportJson";
static const char* ANIM_SKILL_2 = "animation/Effort1/Effort1.ExportJson";
// ��������
static const char* ANIM_NAME_SKILL_1 = "Effect";
static const char* ANIM_NAME_SKILL_2 = "Effort1";

// ͼƬ
// Background
static const char* IMG_BG_MAP = "common/1.png";		
static const char* IMG_LOADING_BG = "images/background/LoadingBG.png";
static const char* IMG_WORLD_BG = "images/background/WorldBG.png";
static const char* IMG_HOME_BG = "images/background/HomeBG.png";
static const char* IMG_CHAPTER_BG = "images/background/ChapterBG.png";
static const char* IMG_GRAY_BG = "images/background/GrayBG.png";

#endif // !__CONFIG_H__

