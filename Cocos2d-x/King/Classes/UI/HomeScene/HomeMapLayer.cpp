#include "HomeMapLayer.h"

//use
#include "Utils\Config.h"
#include "Model\Robots.h"
#include "Utils\DataManager.h"
#include "Utils\GlobalManager.h"
#include "Model\BuildingSprite.h"

HomeMapLayer::HomeMapLayer() {

};

HomeMapLayer::~HomeMapLayer() {

};

bool HomeMapLayer::init() {
	if(!Layer::init()) {
		return false;
	}

	_origin = Vec2::ZERO;
	_Wsize = Director::getInstance()->getWinSize();
	_cache = Director::getInstance()->getTextureCache();

	addMap();
	addRobots();
	addObscale();

	return true;
};

void HomeMapLayer::addMap() {

	//�ȴ���������
	_bgLayer = LayerColor::create();
	this->addChild(_bgLayer, -1);

	//�ڱ������������ɫ�϶���
	//_bgMap = Sprite::create(IMG_BG_MAP);
	_bgMap = Sprite::createWithTexture(_cache->getTextureForKey(IMG_BG_MAP));
	//_bgMap->setAnchorPoint(Vec2::ZERO);
	//_bgMap->setPosition(Vec2::ZERO);
	_bgMap->setPosition(_Wsize/2);
	_bgLayer->addChild(_bgMap);

	//�϶����������ҳǳأ�map��
	//auto map = Sprite::create(IMG_HOME_BG);
	//Texture2D* text = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_HOME_BG);
	auto map = Sprite::createWithTexture(_cache->getTextureForKey(IMG_HOME_BG));
	//map->setAnchorPoint(Vec2::ZERO);
	//map->setPosition(Vec2::ZERO);
	map->setPosition(Vec2(_bgMap->getContentSize().width/2, _bgMap->getContentSize().height/2));
	_bgMap->addChild(map, 1);

	//��ʼ��С
	_bgMap->setScale(0.8f);
	//��ʼ����
	_bgMap->runAction(EaseBackInOut::create(ScaleTo::create(1.0f, 0.5f)));

	addFloor();
	addTouch();

};

//��Ӵ���
void HomeMapLayer::addTouch() {

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HomeMapLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HomeMapLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HomeMapLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _bgMap);
};

//���صذ�
void HomeMapLayer::addFloor() {
				   
	//���ռ�����
	GM()->clearCovered();

	auto size = _bgMap->getContentSize();

	ValueVector building = DM()->_building;
	for(int i = 0; i<(int)building.size(); i++) {
		BuildingSprite* spr = BuildingSprite::create(i, Vec2::ZERO);
		_bgMap->addChild(spr, 2);
	}

	//���Դ���
	/*for(int i = 0; i<=38; i++) {
		for(int j = 0; j<=38; j++) {
			BuildingSprite* spr = BuildingSprite::create(1, Vec2(i, j));
			_bgMap->addChild(spr, 99);
		}
	}*/
};

void HomeMapLayer::addRobots() {

	for(int i = 1; i<=4; i++) {
		auto robot = Robots::create(i);
		_bgMap->addChild(robot);
	}
};

void HomeMapLayer::addObscale() {

	auto tree1 = Sprite::createWithTexture(_cache->getTextureForKey(IMG_TREE));
	auto tree2 = Sprite::createWithTexture(_cache->getTextureForKey(IMG_TREE));
	auto tree3 = Sprite::createWithTexture(_cache->getTextureForKey(IMG_TREE));
	auto tree4 = Sprite::createWithTexture(_cache->getTextureForKey(IMG_TREE));

	auto pos = GM()->getMapPos(Vec2(33, 33));
	tree1->setPosition(GM()->getMapPos(Vec2(5, 5)));
	tree2->setPosition(GM()->getMapPos(Vec2(33, 33)));
	tree3->setPosition(GM()->getMapPos(Vec2(5, 33)));
	tree4->setPosition(GM()->getMapPos(Vec2(33, 5)));

	tree1->setLocalZOrder(10);
	tree2->setLocalZOrder(66);
	tree3->setLocalZOrder(38);
	tree4->setLocalZOrder(38);

	GM()->setCoverd(Vec2(5, 5), 1);
	GM()->setCoverd(Vec2(33, 33), 1);
	GM()->setCoverd(Vec2(5, 33), 1);
	GM()->setCoverd(Vec2(33, 5), 1);

	_bgMap->addChild(tree1);
	_bgMap->addChild(tree2);
	_bgMap->addChild(tree3);
	_bgMap->addChild(tree4);

};

void HomeMapLayer::setHudLayer(Layer* layer) {

	_hubLayer = layer;
};

void HomeMapLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event) {
	//log("onTouchesBegan");

};

void HomeMapLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
	//log("onTouchesMoved");

	if(touches.size()==1) {	 //�����ƶ�
		//log("SIG");

		//��ȡ��һ��������
		auto touch = touches[0];
		//��ȡǰ������λ�õ�ƫ����������OpenGL���� 
		// ���㻬�������еĻ�������
		auto delta = touch->getDelta();

		//_bgMap��ǰ��λ��
		auto currentPos = _bgMap->getPosition();
		//_bgMap�ƶ�֮���λ��
		auto afterPos = currentPos+delta;

		/*ע��*/
		//getBoundingBox��������þ������ź���ת֮������д�С��������getContentSize��������ýڵ�ԭʼ�Ĵ�С
		auto size = _bgMap->getBoundingBox().size;

		/*******************�߽���ƣ�Լ��_bgMap��λ��*******************/
		//���ҷ�Χ
		auto x1 = size.width * _bgMap->getAnchorPoint().x;	  //(����໬��)
		auto x2 = -size.width+_Wsize.width+size.width * _bgMap->getAnchorPoint().x;	 //(���Ҳ໬��)
		afterPos.x = MIN(afterPos.x, x1);
		afterPos.x = MAX(afterPos.x, x2);

		//���·�Χ
		auto y1 = size.height * _bgMap->getAnchorPoint().y;
		auto y2 = -size.height+_Wsize.height+size.height * _bgMap->getAnchorPoint().y;
		afterPos.y = MIN(afterPos.y, y1);
		afterPos.y = MAX(afterPos.y, y2);

		_bgMap->setPosition(afterPos);

		/*******************����ԭ��λ��*******************/
		if((afterPos.x>=x1)||(afterPos.x<=x2)) {
			delta.x = 0;
		}

		if((afterPos.y>=y1)||(afterPos.y<=y2)) {
			delta.y = 0;
		}

		_origin += delta;

	}
	else {	//�������
		//log("MUL");

		//��ȡ��ǰ����������
		auto point1 = touches[0]->getLocation();
		auto point2 = touches[1]->getLocation();

		//��ǰ֮��ľ���
		auto currdistance = point1.distance(point2);
		// ��������������һʱ��֮��þ��루return sqrt(dx*dx, dy*dy)��
		auto prevdistance = touches[0]->getPreviousLocation().distance(touches[1]->getPreviousLocation());

		//����������ԭ��������pointvec1��pointvec2�������_bgmap��λ��
		auto pointvec1 = point1-_origin;
		auto pointvec2 = point2-_origin;

		//�������������е�
		auto relmidx = (pointvec1.x+pointvec2.x)/2;
		auto relmidy = (pointvec1.y+pointvec2.y)/2;

		/*
		_bgmap�ĳߴ粻�ϱ仯�ģ����Լ�����ê�����б߽紦��ʱ��һ��Ҫ�������ź�ĳߴ��������㣬��������������Ŀ�ߡ�
		���Դ����м���bgsprite�ĳߴ�������getboundingbox��������þ������ź���ת֮������д�С��
		������getcontentsize��������ýڵ�ԭʼ�Ĵ�С
		*/
		//����_bgmap��ê��
		auto anchorx = relmidx/_bgMap->getBoundingBox().size.width;
		auto anchory = relmidy/_bgMap->getBoundingBox().size.height;

		//�����Ļ���е�
		auto absmidx = (point2.x+point1.x)/2;
		auto absmidy = (point2.y+point1.y)/2;

		//����ʱΪ�˱�����ֿհ׵�����,��Ҫ�����±߽紦��
		//��bg_grass��Ҫ���뵽��Ļʱ���޸�_bgmap��λ�ã�absmid��
		if(_origin.x > 0) {
			absmidx -= _origin.x;
		}
		if(_origin.x < -_bgMap->getBoundingBox().size.width+_Wsize.width) {
			absmidx += -_bgMap->getBoundingBox().size.width+_Wsize.width-_origin.x;
		}

		if(_origin.y > 0) {
			absmidy -= _origin.y;
		}
		if(_origin.y < -_bgMap->getBoundingBox().size.height+_Wsize.height) {
			absmidy += -_bgMap->getBoundingBox().size.height+_Wsize.height-_origin.y;
		}

		//�����趨ê���λ��
		_bgMap->setAnchorPoint(Vec2(anchorx, anchory));
		_bgMap->setPosition(Vec2(absmidx, absmidy));

		// ������������ǰ��ľ���������ű���
		// �µľ���/�ϵľ���  * ԭ�������ű�������Ϊ�µ����ű���  
		auto scale = _bgMap->getScale() * (currdistance/prevdistance);
		scale = MIN(4, MAX(0.5f, scale));
		_bgMap->setScale(scale);

		//����ԭ��λ��
		_origin = Vec2(absmidx, absmidy)-Vec2(_bgMap->getBoundingBox().size.width * anchorx, _bgMap->getBoundingBox().size.height * anchory);

	}
};

void HomeMapLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event) {
	//log("onTouchesEnded");

};