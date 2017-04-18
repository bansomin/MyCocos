/*************************BEGIN****************************************************
Created by HAO on 2017/04/12
BRIEF	: 
VERSION	:
HISTORY	:
***************************END****************************************************/
#ifndef __BUILDINGSPRITE_H__
#define __BUILDINGSPRITE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class BuildingSprite : public Sprite {

public:
	virtual bool init(int index, Vec2 ve);
	static BuildingSprite* create(int index, Vec2 ve);

public:
	void addTouch();
	bool onToucheBegan(Touch* touch, Event* event);
	void onToucheMoved(Touch* touch, Event* event);
	void onToucheEnded(Touch* touch, Event* event);

public:
	void loadData(int index);
	void loadUI();
	void moveBuilding(Vec2 delta);	//�ƶ�����
	void selectedAction();			// ��ѡ��ʱ�Ķ���Ч��
	void unselectedAction();		// ȥ��ѡ�ж���  
	void setTiledPos();				// ������Ƭ����

public:
	void upgrade();                 // ��������
	void showUpgradePro();			// ��������������
	void upgradeFinished();			// �������

public:
    // ��������
    int _index;                 // �ڴ��е������±�
    int _id;                    // ���
    int _BuildingID;            // �������ID
    int _buildState;            // ����״̬��1�ѽ��ɣ�2���ڽ��졣
    int _lastBuildTime;         // �����ʱ�䡣
    int _lastGoldHarvest;       // ����ջ�ʱ�䡣��󳡽�Ҳ���
    int _lastWoodHarvest;       // ľ���ջ�ʱ�䡣ľ�ĳ�ľ�Ĳ�����
	
    int _type;                  // ����
    int _level;                 // �ȼ�
    int _healthPoint;           // ����ֵ
    string _name;               // ��������
    string _description;        // ����
    
    int _goldRequire;           // ����������
    int _woodRequire;           // ��������ľ��
    int _timeRequire;           // ��������ʱ��
    int _playerLevelRequire;    // ������ҵȼ�
    int _baseLevelRequire;      // ��������˾��ȼ�
    int _expReward;             // ���������Ҿ���
    
    // ��������
    int _goldProduct;           // ÿСʱ��Ҳ���
    int _woodProduct;           // ÿСʱľ�Ĳ���
    
    // ��Դ����
    int _goldCapacity;          // �������
    int _woodCapacity;          // ľ������
    
    // ��������
    bool _isBroken;             // �Ƿ񱻴ݻ�
    bool _canAttack;            // �Ƿ�Ϊ������ʩ
    int _damage;                // ������
    int _attackSpeed;           // �����ٶ�
    int _shootRange;            // ��̷�Χ
    int _damageRange;           // �������˷�Χ
    Node* _attackTarget;        // ����Ŀ��
    
    // ��������
    bool _canTouched;           // �Ƿ�����ƶ�
    bool _isTouched;            // �Ƿ񱻴���
    bool _isSelected;           // �Ƿ�ѡ��
    bool _isShowOpt;            // �Ƿ���ʾ��opt����
    float _deltaPos;            // �ƶ�ƫ��
    EventListenerTouchOneByOne* _listener;
    
    // ͼƬ
    Size _size;			// �ߴ�
	Vec2 _pos;          // ����

    Sprite* _normal;    // ����ͼƬ
    Sprite* _broken;    // �ٻ�ͼƬ
    Sprite* _tip;       // ��ͷ

	TextureCache*_cache;	//������

    
    //HarvestBubble* bubble;

};


#endif // !__BUILDINGSPRITE_H__
