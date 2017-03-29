/**
* Created by HAO on 2016/9/2.
*/

#include "Player.h"

Player::Player() {

	Wsize = Director::getInstance()->getWinSize();
	playerArrow = NULL;
	hpBar = NULL;
	hpBg = NULL;

	startDraw = false;
	drawNode = NULL;

	bezier.controlPoint = Vec2 (0, 0);
	bezier.endPoint = Vec2 (0, 0);
};

Player::~Player() {

};

bool Player::init(Vec2 pos) {
	log("Player_init");

	if (!Sprite::init()) {
		return false;
	}

	this->playerPos = pos;

	//player
	this->createPlayer();
	//血条
	this->createPlayerHpBar();
	//开启定时器
	this->scheduleUpdate ();

	return true;
};

Player* Player::create(Vec2 pos) {
	log("Player_create");

	Player* player = new Player();
	if (player && player->init(pos)) {
		player->autorelease();
		return player;
	}
	else {
		delete player;
		player = NULL;
		return NULL;
	}
};

void Player::createPlayer() {
	log("Player_createPlayer");

	playerBody = Sprite::createWithSpriteFrameName ("playerbody.png");
	playerSize = Size(playerBody->getContentSize().width / 2, playerBody->getContentSize().height / 3 * 2);
	playerBody->setAnchorPoint (Vec2 (0.7f, 0.4f));
	this->addChild (playerBody);
	this->setPosition(Vec2(playerPos.x, playerPos.y + playerSize.height * 0.4f));


	playerArrow = Sprite::createWithSpriteFrameName ("playerarrow.png");
	playerArrow->setPosition(Vec2(0, 0));
	playerArrow->setAnchorPoint(Vec2(0.2f, 0.5f));
	this->addChild(playerArrow);
};

void Player::createPlayerHpBar() {

	//血条在后，血条背景在前
	//血条(加在player上)
	hpBar = ProgressTimer::create (Sprite::createWithSpriteFrameName ("hp1.png"));
	hpBar->setType (ProgressTimer::Type::BAR);
	hpBar->setMidpoint (Vec2 (0, 0.5));
	hpBar->setBarChangeRate (Vec2 (1, 0));
	hpBar->setPercentage (100);
	hpBar->setPosition (Vec2 (playerBody->getContentSize ().width / 2 + 5, playerBody->getContentSize ().height + 5));
	playerBody->addChild(hpBar);

	//血条背景(加在hpBar上）
	hpBg = createWithSpriteFrameName("hpbg.png");
	hpBg->setPosition(Vec2(hpBar->getContentSize().width / 2, hpBar->getContentSize().height));
	hpBar->addChild(hpBg);
};

void Player::initRotateArrow (Point touchPos) {

    auto playerPos = this->getPosition ();
    auto pos = playerPos + playerArrow->getPosition ();

    Point vector = touchPos - pos;	//触摸点与弓箭之间的向量

    auto rotateRadians = vector.getAngle ();    //获取该向量和x轴的夹角（弧度）。    
    log ("angle = %f", rotateRadians);
    auto rotateDegress = CC_RADIANS_TO_DEGREES (-1 * rotateRadians);	//将弧度转化为角度（顺时针方向为正，*-1）
    log ("degress = %f", rotateDegress);

    if (rotateDegress >= -180 && rotateDegress <= -90) {//左上（超出范围）
        rotateDegress = -90;
    }
    else if (rotateDegress >= 90 && rotateDegress <= 180) {//左下（超出范围）
        rotateDegress = 90;
    }

    playerArrow->setRotation (rotateDegress);
};

void Player::rotateArrow (Point touchPos) {
        
	auto playerPos = this->getPosition ();
	auto pos = playerPos + playerArrow->getPosition ();

	Point vector = touchPos - pos;

    auto rotateRadians = vector.getAngle ();    //获取该向量和x轴的夹角（弧度）。    
    log ("angle = %f", rotateRadians);
    auto rotateDegress = CC_RADIANS_TO_DEGREES (-1 * rotateRadians);   
    log ("degress = %f", rotateDegress);

    if (rotateDegress >= -180 && rotateDegress <= -90) {//左上（超出范围）
        rotateDegress = -90;
    } 
    else if(rotateDegress >= 90 && rotateDegress <= 180){//左下（超出范围）
        rotateDegress = 90;
    }

	auto speed = 2 * 3.1415;	//1s转一个圆
    auto rotateDuration = fabs (rotateRadians/speed);
    playerArrow->runAction (
        Sequence::create (
            RotateTo::create(rotateDuration, rotateDegress),    //持续时间,以秒为单位; 目标角度，以角度值计;
            NULL
        )
    );

	//检测路径贝赛尔的控制点和终点
	auto mid = Wsize.width / 2;
	auto x = MAX (mid / 10, MIN (vector.x, mid));
	auto y = vector.y;

	Point endPoint = Vec2 (4 * x, -this->convertToWorldSpace (Vec2 (4 * x, y > 0 ? 0 : abs (y * 10))).y);

	Point q = Point (2 * x, 2 * y);
	bezier.controlPoint = q;
	bezier.endPoint = endPoint;

	startDraw = true;
};

void Player::createAndShootArrow (Point touchPos) {

	isRunAction = true;	

	auto animation = AnimationCache::getInstance ()->getAnimation ("player");
	auto animate = Animate::create (animation);

	auto delay = DelayTime::create (0.5f);
	auto func1 = CallFunc::create (CC_CALLBACK_0 (Player::shootArrow, this));
	auto func2 = CallFunc::create (CC_CALLBACK_0 (Player::finishRunAction, this));

	playerBody->runAction (
		Sequence::create(
			animate,
			func1,
			delay,
			func2,
			NULL
		)
	);
};

void Player::shootArrow (){

	//创建箭
	Sprite* arrow = Sprite::createWithSpriteFrameName ("arrow1.png");
	arrow->setRotation (playerArrow->getRotation ());
	arrow->setPosition (Vec2 (playerArrow->getPositionX()/2, playerArrow->getPositionY()));
	this->addChild (arrow);

	//测试专用
	//ccBezierConfig config;
	//config.controlPoint_1 = Vec2 (100, 200);
	//config.controlPoint_2 = Vec2 (200, 200);
	//config.endPosition	  = Vec2 (300, 0);
	//auto action = BezierTo::create(2, config);

	auto action = ArrowBezier::creat (2, bezier);
	arrow->runAction (action);
};

void Player::finishRunAction () {

	isRunAction = false;
};

void Player::update (float dt) {

	if (!startDraw) {
		return;
	}

	if (drawNode) {
		drawNode->removeFromParentAndCleanup (true);
	}

	drawNode = DrawNode::create ();
	drawNode->drawQuadBezier (Vec2 (playerArrow->getPositionX()/ 2, playerArrow->getPositionY()), 
							  bezier.controlPoint, 
							  bezier.endPoint, 
							  100, 
							  Color4F (1.0, 0.0, 0.0, 1.0));

	this->addChild (drawNode, -2);
};