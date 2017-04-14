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

	//先创建背景层
	_bgLayer = LayerColor::create();
	this->addChild(_bgLayer, -1);

	//在背景层上添加绿色拖动层
	//_bgMap = Sprite::create(IMG_BG_MAP);
	_bgMap = Sprite::createWithTexture(_cache->getTextureForKey(IMG_BG_MAP));
	//_bgMap->setAnchorPoint(Vec2::ZERO);
	//_bgMap->setPosition(Vec2::ZERO);
	_bgMap->setPosition(_Wsize/2);
	_bgLayer->addChild(_bgMap);

	//拖动层上添加玩家城池（map）
	//auto map = Sprite::create(IMG_HOME_BG);
	//Texture2D* text = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_HOME_BG);
	auto map = Sprite::createWithTexture(_cache->getTextureForKey(IMG_HOME_BG));
	//map->setAnchorPoint(Vec2::ZERO);
	//map->setPosition(Vec2::ZERO);
	map->setPosition(Vec2(_bgMap->getContentSize().width/2, _bgMap->getContentSize().height/2));
	_bgMap->addChild(map, 1);

	//初始缩小
	_bgMap->setScale(0.8f);
	//初始动画
	_bgMap->runAction(EaseBackInOut::create(ScaleTo::create(1.0f, 0.5f)));

	addFloor();
	addTouch();

};

//添加触摸
void HomeMapLayer::addTouch() {

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HomeMapLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HomeMapLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HomeMapLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _bgMap);
};

//加载地板
void HomeMapLayer::addFloor() {
				   
	//清空占地情况
	GM()->clearCovered();

	auto size = _bgMap->getContentSize();

	ValueVector building = DM()->_building;
	for(int i = 0; i<(int)building.size(); i++) {
		BuildingSprite* spr = BuildingSprite::create(i, Vec2::ZERO);
		_bgMap->addChild(spr, 2);
	}

	//测试代码
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

	if(touches.size()==1) {	 //单点移动
		//log("SIG");

		//获取第一个触摸点
		auto touch = touches[0];
		//获取前后两次位置的偏移量，基于OpenGL坐标 
		// 计算滑动过程中的滑动增量
		auto delta = touch->getDelta();

		//_bgMap当前的位置
		auto currentPos = _bgMap->getPosition();
		//_bgMap移动之后的位置
		auto afterPos = currentPos+delta;

		/*注意*/
		//getBoundingBox函数来获得经过缩放和旋转之后的外框盒大小，而不用getContentSize函数来获得节点原始的大小
		auto size = _bgMap->getBoundingBox().size;

		/*******************边界控制，约束_bgMap的位置*******************/
		//左右范围
		auto x1 = size.width * _bgMap->getAnchorPoint().x;	  //(向左侧滑动)
		auto x2 = -size.width+_Wsize.width+size.width * _bgMap->getAnchorPoint().x;	 //(向右侧滑动)
		afterPos.x = MIN(afterPos.x, x1);
		afterPos.x = MAX(afterPos.x, x2);

		//上下范围
		auto y1 = size.height * _bgMap->getAnchorPoint().y;
		auto y2 = -size.height+_Wsize.height+size.height * _bgMap->getAnchorPoint().y;
		afterPos.y = MIN(afterPos.y, y1);
		afterPos.y = MAX(afterPos.y, y2);

		_bgMap->setPosition(afterPos);

		/*******************更新原点位置*******************/
		if((afterPos.x>=x1)||(afterPos.x<=x2)) {
			delta.x = 0;
		}

		if((afterPos.y>=y1)||(afterPos.y<=y2)) {
			delta.y = 0;
		}

		_origin += delta;

	}
	else {	//多点缩放
		//log("MUL");

		//获取当前两个触摸点
		auto point1 = touches[0]->getLocation();
		auto point2 = touches[1]->getLocation();

		//当前之间的距离
		auto currdistance = point1.distance(point2);
		// 计算两触摸点上一时刻之间得距离（return sqrt(dx*dx, dy*dy)）
		auto prevdistance = touches[0]->getPreviousLocation().distance(touches[1]->getPreviousLocation());

		//两触摸点与原点的向量差，pointvec1和pointvec2是相对于_bgmap的位置
		auto pointvec1 = point1-_origin;
		auto pointvec2 = point2-_origin;

		//两触摸点的相对中点
		auto relmidx = (pointvec1.x+pointvec2.x)/2;
		auto relmidy = (pointvec1.y+pointvec2.y)/2;

		/*
		_bgmap的尺寸不断变化的，所以计算起锚点或进行边界处理时，一定要用它缩放后的尺寸宽高来计算，而不能是它本身的宽高。
		所以代码中计算bgsprite的尺寸我们用getboundingbox函数来获得经过缩放和旋转之后的外框盒大小，
		而不用getcontentsize函数来获得节点原始的大小
		*/
		//计算_bgmap的锚点
		auto anchorx = relmidx/_bgMap->getBoundingBox().size.width;
		auto anchory = relmidy/_bgMap->getBoundingBox().size.height;

		//相对屏幕的中点
		auto absmidx = (point2.x+point1.x)/2;
		auto absmidy = (point2.y+point1.y)/2;

		//缩放时为了避免出现空白的区域,需要做以下边界处理
		//当bg_grass快要进入到屏幕时，修改_bgmap的位置（absmid）
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

		//重新设定锚点的位置
		_bgMap->setAnchorPoint(Vec2(anchorx, anchory));
		_bgMap->setPosition(Vec2(absmidx, absmidy));

		// 根据两触摸点前后的距离计算缩放倍率
		// 新的距离/老的距离  * 原来的缩放比例，即为新的缩放比例  
		auto scale = _bgMap->getScale() * (currdistance/prevdistance);
		scale = MIN(4, MAX(0.5f, scale));
		_bgMap->setScale(scale);

		//更新原点位置
		_origin = Vec2(absmidx, absmidy)-Vec2(_bgMap->getBoundingBox().size.width * anchorx, _bgMap->getBoundingBox().size.height * anchory);

	}
};

void HomeMapLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event) {
	//log("onTouchesEnded");

};