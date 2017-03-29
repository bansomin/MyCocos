
/*************************BEGIN**************************************************** 
    			Created by HAO on 2016/9/12
    BRIEF	: 	
    VERSION	: 
    HISTORY	:
***************************END****************************************************/
#include "ChooseLayer.h"

#define TAG_IMGEVIEW 100

bool SeedChooseLayer::init () {

	if (!Layer::init()) {

		return false;
	}

	Wsize = Director::getInstance ()->getWinSize ();

	currType = CropsType::NOTHING;

	//加载csb文件
	chooseLayer = CSLoader::createNode ("ChooseLayer.csb");
	chooseLayer->setAnchorPoint (Vec2 (0.5, 0.5));
	this->addChild (chooseLayer);

	auto bgSpr	= dynamic_cast<Sprite*>(chooseLayer->getChildByName ("chooseBg"));

	wheatImg	= static_cast<ImageView*>(bgSpr->getChildByName ("Image_1"));
	wheatImg->setTag (TAG_IMGEVIEW + 1);
	cronTmg		= static_cast<ImageView*>(bgSpr->getChildByName ("Image_2"));
	cronTmg->setTag (TAG_IMGEVIEW + 2);

	carrotImg = static_cast<ImageView*>(bgSpr->getChildByName ("Image_3"));	
	carrotImg->setTag (TAG_IMGEVIEW + 3);

	wheatImg->addTouchEventListener (CC_CALLBACK_2 (SeedChooseLayer::chooseCropFunc, this));
	cronTmg->addTouchEventListener (CC_CALLBACK_2 (SeedChooseLayer::chooseCropFunc, this));
	carrotImg->addTouchEventListener (CC_CALLBACK_2 (SeedChooseLayer::chooseCropFunc, this));

	//触摸监听
	auto listener = EventListenerTouchOneByOne::create ();
	listener->setSwallowTouches (true);	//设置是否向下传递触摸，true表示不向下触摸
	listener->onTouchBegan = CC_CALLBACK_2 (SeedChooseLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority (listener, this);

	return true;
};

bool SeedChooseLayer::onTouchBegan (Touch* touch, Event* event) {
	log ("SeedChooseLayer_onTouchBegan.");

	return true;
};

void SeedChooseLayer::chooseCropFunc (Ref* pSender, Widget::TouchEventType type) {
	log ("chooseCropFunc.");

	auto widget = static_cast<Widget*>(pSender);
	
	int tag = widget->getTag ();
	log ("tag = %d", tag);

	switch (tag) {
		case 101:
			currType = CropsType::WHEAT;
			widget->setOpacity (130);
			//widget->setVisible (false);
			log ("WHEAT.");

			break;
		case 102:
			currType = CropsType::CORN;
			widget->setOpacity (130);
			//widget->setVisible (false);
			log ("WHEAT.");

			break;
		case 103:
			currType = CropsType::CARROT;
			widget->setOpacity (130);
			//widget->setVisible (false);
			log ("CARROT.");
			
			break;;
		default:
			currType = CropsType::NOTHING;
			log ("WHEAT.");

			break;
	}

};









