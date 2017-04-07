#include "HomeScene.h"

//use
#include "Utils\Config.h"

bool HomeScene::init() {
	if(!Layer::init()) {
		return false;
	}

	_origin = Vec2::ZERO;
	_Wsize = Director::getInstance()->getWinSize();

	//�ȴ���������
	_bgLayer = LayerColor::create();
	this->addChild(_bgLayer, -1);

	//�ڱ������������ɫ�϶���
	_bgMap = Sprite::create(IMG_BG_MAP);
	_bgMap->setAnchorPoint(Vec2::ZERO);
	_bgMap->setPosition(Vec2::ZERO);
	_bgLayer->addChild(_bgMap);

	//�϶����������ҳǳأ�map��
	auto map = Sprite::create(IMG_HOME_BG);
	map->setAnchorPoint(Vec2::ZERO);
	map->setPosition(Vec2::ZERO);
	_bgMap->addChild(map, 1);
	//��ʼ��С0.5
	_bgMap->setScale(0.5f);
 	
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HomeScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HomeScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HomeScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _bgMap);

	return true;
};

void HomeScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	//log("onTouchesBegan");

};

void HomeScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	//log("onTouchesMoved");
	
	if(touches.size()==1) {	 //�����ƶ�
		log("SIG");	

		//��ȡ��һ��������
		auto touch = touches[0];		
		//��ȡǰ������λ�õ�ƫ����������OpenGL���� 
		// ���㻬�������еĻ�������
		auto delta = touch->getDelta();	
		
		//_bgMap��ǰ��λ��
		auto currentPos = _bgMap->getPosition();
		//_bgMap�ƶ�֮���λ��
		auto afterPos  = currentPos + delta;		

		/*ע��*/
		//getBoundingBox��������þ������ź���ת֮������д�С��������getContentSize��������ýڵ�ԭʼ�Ĵ�С
		auto size = _bgMap->getBoundingBox().size;	

		/*******************�߽���ƣ�Լ��_bgMap��λ��*******************/
		//���ҷ�Χ
		auto x1 = size.width * _bgMap->getAnchorPoint().x;
		auto x2 = -size.width+_Wsize.width+size.width*_bgMap->getAnchorPoint().x;
		afterPos.x = MIN(afterPos.x, x1);
		afterPos.x = MAX(afterPos.x, x2);

		//���·�Χ
		auto y1 = size.height*_bgMap->getAnchorPoint().y;
		auto y2 = -size.height+_Wsize.height+size.height*_bgMap->getAnchorPoint().y;
		afterPos.y = MIN(afterPos.y, y1);
		afterPos.y = MAX(afterPos.y, y2);

		_bgMap->setPosition(afterPos);

		/*******************����ԭ��λ��*******************/
		if((afterPos.x >= x1) || (afterPos.x <= x2)) {
			delta.x = 0;
		}

		if((afterPos.y >= y1) || (afterPos.y <= y2)) {
			delta.y = 0;
		}

		_origin += delta;
		
	}
	else {	//�������
		log("MUL");

		//��ȡ��ǰ����������
		auto point1 = touches[0]->getLocation();
		auto point2 = touches[1]->getLocation();

		//��ǰ֮��ľ���
		auto currdistance = point1.distance(point2);
		// ��������������һʱ��֮��þ��루return sqrt(dx*dx, dy*dy)��
		auto prevdistance = touches[0]->getPreviousLocation().distance(touches[1]->getPreviousLocation());

		//����������ԭ��������pointvec1��pointvec2�������_bgmap��λ��
		auto pointvec1 = point1 - _origin;
		auto pointvec2 = point2 - _origin;

		//�������������е�
		auto relmidx = (pointvec1.x + pointvec2.x)/2;
		auto relmidy = (pointvec1.y + pointvec2.y)/2;

		/*
		_bgmap�ĳߴ粻�ϱ仯�ģ����Լ�����ê�����б߽紦��ʱ��һ��Ҫ�������ź�ĳߴ��������㣬��������������Ŀ�ߡ�
		���Դ����м���bgsprite�ĳߴ�������getboundingbox��������þ������ź���ת֮������д�С��
		������getcontentsize��������ýڵ�ԭʼ�Ĵ�С
		*/
		//����_bgmap��ê��
		auto anchorx = relmidx/_bgMap->getBoundingBox().size.width;
		auto anchory = relmidy/_bgMap->getBoundingBox().size.height;

		//�����Ļ���е�
		auto absmidx = (point2.x + point1.x)/2;
		auto absmidy = (point2.y + point1.y)/2;

		//����ʱΪ�˱�����ֿհ׵�����,��Ҫ�����±߽紦��
		//��bg_grass��Ҫ���뵽��Ļʱ���޸�_bgmap��λ�ã�absmid��
		if(_origin.x > 0) {
			absmidx -= _origin.x;
		}
		if(_origin.x < -_bgMap->getBoundingBox().size.width + _Wsize.width) {
			absmidx += -_bgMap->getBoundingBox().size.width + _Wsize.width - _origin.x;
		}
		
		if(_origin.y > 0) {
			absmidy -= _origin.y;
		}
		if(_origin.y < -_bgMap->getBoundingBox().size.height + _Wsize.height) {
			absmidy += -_bgMap->getBoundingBox().size.height + _Wsize.height - _origin.y;
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

void HomeScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	log("onTouchesEnded");

	//auto touch = touches[0];
	//log("EndPos:%d", touch->getLocation());
};

Scene* HomeScene::createScene() {

	auto scene = Scene::create();
	auto layer = HomeScene::create();
	scene->addChild(layer);

	return scene;
};