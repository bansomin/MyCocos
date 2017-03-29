
/*************************BEGIN**************************************************** 
    			Created by HAO on 2016/9/7
    BRIEF	: 	GameScene.cpp
    VERSION	: 
    HISTORY	:
***************************END****************************************************/

#include "GameScene.h"

#define SHOP_ITEM_SPRITE_TAG    100
#define SEEDPANEL_TAG           888
#define HARVESTPANEL_TAG        889
#define REMOVEPANEL_TAG         890

const char* shop_textures [8] = {

	"Item1.png",
	"Item2.png",
	"Item3.png",
	"Item4.png",
	"Item5.png",
	"Item6.png",
	"Item1.png",
	"Item4.png"
};

const char* shopMove_textures [8] = {

	"itemMove/moveItem1.png",
	"itemMove/moveItem2.png",
	"itemMove/moveItem3.png",
	"itemMove/moveItem4.png",
	"itemMove/moveItem5.png",
	"itemMove/moveItem6.png",
	"itemMove/moveItem1.png",
	"itemMove/moveItem4.png"
};

const char* shopMove_en_textures [8] = {

	"itemMove_en/Item1.png",
	"itemMove_en/Item2.png",
	"itemMove_en/Item3.png",
	"itemMove_en/Item4.png",
	"itemMove_en/Item5.png",
	"itemMove_en/Item6.png",
	"itemMove_en/Item1.png",
	"itemMove_en/Item4.png"
};

const char* shop_info [8] = {

	"ground",
	"fruiter",
	"flower",
	"pavilion",
	"blueflower",
	"wastage",
	"ground",
	"pavilion"
};

const char* shop_money [8] = {
	
	"20g",
	"60g",
	"40g",
	"500g",
	"200g",
	"10g",
	"20g",
	"500g"
};


GameScene::GameScene () {

	tempSpr = NULL;

	isOut = false;
	isCanBulid = false;

	longPress = false;

};

GameScene::~GameScene () {

};

Scene* GameScene::createScene () {

	// 'scene' is an autorelease object
	auto scene = Scene::create ();

	// 'layer' is an autorelease object
	auto layer = GameScene::create ();

	// add layer as a child to scene
	scene->addChild (layer);

	// return the scene
	return scene;
};

 bool GameScene::init () {

	 if (!Layer::init()) {
		 return false;
	 }

	 Wsize = Director::getInstance ()->getWinSize ();
	 origin = Vec2::ZERO;

	 //������
	 maplayer = LayerColor::create ();
	 this->addChild (maplayer, -1);

	 //�����ݴ�
	 bg_grass = Sprite::create ("2.png");
	 bg_grass->setAnchorPoint (Vec2::ZERO);
	 bg_grass->setPosition (Vec2::ZERO);
	 maplayer->addChild (bg_grass);

	 //���ص�ͼ
	 map = TMXTiledMap::create ("map.tmx");
	 map->setAnchorPoint (Vec2::ZERO);
	 map->setPosition (Vec2::ZERO);
	 bg_grass->addChild (map, 1);

	 //��ʼ��ͼ��
	 this->initMapLayerFunc ();

	 currPos = Vec2 (0, 0);
	 perPos = currPos;

	 //��������
	 bg_tree = Sprite::create ("1.png");
	 bg_tree->setAnchorPoint (Vec2::ZERO);
	 bg_tree->setPosition (Vec2::ZERO);
	 bg_tree->setScale (2);
	 bg_grass->addChild (bg_tree, 2);

	 //�ײ�����λ��
	 currPos = Vec2 (0, 0);
	 perPos  = currPos;

	 auto listener = EventListenerTouchAllAtOnce::create ();
	 listener->onTouchesBegan = CC_CALLBACK_2 (GameScene::onTouchesBegan, this);
	 listener->onTouchesMoved = CC_CALLBACK_2 (GameScene::onTouchesMoved, this);
	 listener->onTouchesEnded = CC_CALLBACK_2 (GameScene::onTouchesEnded, this);
	 _eventDispatcher->addEventListenerWithSceneGraphPriority (listener, bg_grass);

	 this->addUI ();

	 return true;
};

 void GameScene::initMapLayerFunc () {

	 if (map) {
		 mapSize = map->getMapSize ();
		 map_bglayer = map->getLayer ("bgLayer");
		 map_tipslayer = map->getLayer ("tipsLayer");
		 map_goodslayer = map->getLayer ("goodsLayer");
	 }
 };

 void GameScene::addUI () {
	 log ("addUI");

	 auto visible = Director::getInstance ()->getVisibleSize ();

	 auto rootLayer = CSLoader::createNode ("Layer.csb");
	 rootLayer->setScaleX (visible.width / rootLayer->getContentSize ().width);
	 rootLayer->setScaleY (visible.height / rootLayer->getContentSize ().height);
	 this->addChild (rootLayer, 10);

	 //�������panel_shop
	 panel_shop = dynamic_cast<Layout*>(rootLayer->getChildByName ("panel_shop"));
	 btn_shop = dynamic_cast<Button*>(panel_shop->getChildByName ("btn_shop"));
	 btn_shop->addTouchEventListener (CC_CALLBACK_2 (GameScene::clickShopBtnFunc, this));

	 //��ù�������scrolview
	 scrollview = dynamic_cast<ScrollView*>(panel_shop->getChildByName ("scrolview"));

	 panel_item = dynamic_cast<Layout*>(scrollview->getChildByName ("panel_item"));

	 auto num = panel_item->getChildren ().size ();

	 for (int i = 0; i < num; i++) {

		 //��ȡ�ײ�
		 Sprite* itemSpr = static_cast<Sprite*>(panel_item->getChildren ().at (i));
		 itemSpr->setTag (SHOP_ITEM_SPRITE_TAG + i);

		 //��ȡ��ƷͼƬ
		 ImageView* image = static_cast<ImageView*>(itemSpr->getChildByName ("image"));
		 image->loadTexture (shop_textures [i]);
		 //�󶨻ص�����
		 image->addTouchEventListener (CC_CALLBACK_2 (GameScene::selectItemFunc, this));


		 //��ȡ��Ʒ��Ϣ
		 TextField* text_info = static_cast<TextField*>(itemSpr->getChildByName ("text_info"));
		 text_info->setText (shop_info [i]);

		 //��ȡ��Ʒ�۸�
		 TextField* text_money = static_cast<TextField*>(itemSpr->getChildByName ("text_money"));
		 //text_money->setText (std::to_string(shop_money[i]));
		 text_money->setText (shop_money [i]);
	 }
	 isOut = false;
 };

 void GameScene::clickShopBtnFunc (Ref* sender, Widget::TouchEventType type) {
	 log ("touchEvent.");

	 switch (type) {
		 case cocos2d::ui::Widget::TouchEventType::ENDED:
			 //Ϊpanel_shop���һ�����Զ���

			 if (isOut && panel_shop) {	//�Ѿ�����(�������ض���)
				 isOut = false;
				 panel_shop->runAction (
					 EaseElasticOut::create (
						 MoveBy::create (1.0f,
										 Vec2 (-panel_shop->getContentSize ().width * 6 / 11, 0)
						 ),
						 0.5f
					 )
				 );
			 }
			 else {		//δ���������е���������
				 isOut = true;
				 panel_shop->runAction (
					 EaseElasticOut::create (
						 MoveBy::create (1.0f,
										 Vec2 (panel_shop->getContentSize ().width * 6 / 11, 0)
						 ),
						 0.5f
					 )
				 );
			 }
			 break;
		 default:
			 break;
	 }
 };

 void GameScene::onTouchesBegan (const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	 log ("onTouchesBegan.");

	 //panel_shop����
	 if (isOut && panel_shop) {	//�Ѿ�����(�������ض���)
		 isOut = false;
		 panel_shop->runAction (
			 EaseElasticOut::create (
				 MoveBy::create (1.0f,
								 Vec2 (-panel_shop->getContentSize ().width * 6 / 11, 0)
				 ),
				 0.5f
			 )
		 );
	 }

	 if (touches.size()==1) {	//���㴥��
		 
		 auto touch = touches [0];
		 auto point = touch->getLocation ();

		 Vec2 pos;
		 pos.x = (point.x - origin.x) / bg_grass->getScale ();
		 pos.y = (point.y - origin.y) / bg_grass->getScale ();

		 auto tilePos = this->convertTotileCoord (pos);
		 if (tilePos.x>=0&&(tilePos.x<=mapSize.width-1) && tilePos.y>=0&&(tilePos.y<=mapSize.height-1)) {
	
			 int gid = map_goodslayer->getTileGIDAt (tilePos);
			 if (gid!=0) {
				 //���
				 map_tipslayer->removeTileAt (touchObjectPos);
				 map_tipslayer->removeTileAt (perPos);
				 touchObjectPos = tilePos;
				 map_tipslayer->setTileGID (17, tilePos);

				 //��ѹ���
				 //longPress�ڿ�ʼ���µ�ʱ��Ϊtrue������ƶ�����ȡ����Ϊfalse��
				 //��̧���ʱ���������Ϊtrue����ôִ��schedule�е�updatePress����
				 //������ʱ
				 this->schedule (schedule_selector (GameScene::updatePress), 2);

				 this->checkTileType ();
			 }
		 }
	 }


 };

 void GameScene::onTouchesMoved (const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	 log ("onTouchesMoved.");
	 log ("size = %d", touches.size ());

	 if (touches.size() >= 2) {	//�������
	 //if (1) {

		 //�õ�����
		 auto point1 = touches [0]->getLocation ();
		 //auto point2 = Vec2(100, 100);
		 auto point2 = touches [1]->getLocation ();
		 //log ("point1 = %f, %f", point1.x, point1.y);

		 //��������������һʱ��֮��ľ���(return sqrt(dx * dx + dy * dy);)
		 auto predistance = touches [0]->getPreviousLocation ().distance (point2);
		 //log ("predistance = %f", predistance);

		 //��������֮��ľ���
		 auto currdistance = point1.distance (point2);
		 //log ("currdistance = %f", currdistance);

		 //������ԭ��Ĳ�����,pointVec1/pointVec2�������bg_grass��λ��
		 auto pointVec1 = point1 - origin;
		 //log ("pointVec1 = %f, %f", pointVec1.x, pointVec1.y);
		 auto pointVec2 = point2 - origin;
		 //log ("pointVec2 = %f, %f", pointVec2.x, pointVec2.y);

		 //���������е�(point1.x + point2.x) / 2
		 auto relMidx = (pointVec1.x + pointVec2.x) / 2;
		 //log ("relMidx = %f", relMidx);
		 auto relMidy = (pointVec1.y + pointVec2.y) / 2;
		 //log ("relMidy = %f", relMidy);

		 /*
		 bgSprite�ĳߴ粻�ϱ仯�ģ����Լ�����ê�����б߽紦��ʱ��һ��Ҫ�������ź�ĳߴ��������㣬��������������Ŀ�ߡ� 
		 ���Դ����м���bgSprite�ĳߴ�������getBoundingBox��������þ������ź���ת֮������д�С��
		 ������getContentSize��������ýڵ�ԭʼ�Ĵ�С
		 */

		 //bg_grass��ê��
		 auto anchorx = relMidx / bg_grass->getBoundingBox ().size.width;
		 auto anchory = relMidy / bg_grass->getBoundingBox ().size.height;
		 //log ("anchor = %f�� %f", anchorx, anchory);

		 //�����Ļ���е�
		 auto absMidx = (point1.x + point2.x) / 2;
		 auto absMidy = (point1.y + point2.y) / 2;

		 //����ʱΪ�˱�����ֿհ׵�����,��Ҫ�����±߽紦��
		 //��bg_grass��Ҫ���뵽��Ļʱ���޸�bg_grass��λ�ã�absMid��
		 if (origin.x > 0) {
			 absMidx -= origin.x;
		 }

		 if (origin.x < (-bg_grass->getBoundingBox().size.width + Wsize.width)) {
			 absMidx += (-bg_grass->getBoundingBox().size.width + Wsize.width - origin.x);
		 }

		 if (origin.y > 0) {
			 absMidy -= origin.y;
		 }

		 if (origin.y < (-bg_grass->getBoundingBox().size.height + Wsize.height)) {
			 absMidy += (-bg_grass->getBoundingBox().size.height + Wsize.height - origin.y);
		 }

		 //��������ê����λ��
		 bg_grass->setAnchorPoint (Vec2 (anchorx, anchory));
		 bg_grass->setPosition (Vec2 (absMidx, absMidy));

		 //�������ű��ʣ�1--4֮�䣩
		 auto scale = bg_grass->getScale ()*(currdistance/predistance);
		 scale = MIN (4, MAX(1, scale));
		 bg_grass->setScale (scale);

		 //����ԭ��λ��
		 origin = Vec2 (absMidx, absMidy) - Vec2(bg_grass->getBoundingBox().size.width * anchorx, bg_grass->getBoundingBox().size.height * anchory);
	 }
	 else {		//�����ƶ�

		 auto touch = touches [0];			//��ȡ��һ��������
		 auto delta = touch->getDelta ();	//��ȡǰ������λ�õ�ƫ����������OpenGL����
		 //log ("delta = %f, %f", delta.x, delta.y);
		 auto beforePos = bg_grass->getPosition ();	//�õ��ƶ�ǰbg_grass��λ��
		 auto afterPos = beforePos + delta;			//�õ��ƶ���bg_grass��λ��

		 auto size = bg_grass->getContentSize ();	//�õ�bg_grass�ĳߴ�

		 //�߽���ƣ�Լ��bg_grass��λ��
		 //���ҷ�Χ����
		 afterPos.x = MIN (afterPos.x, size.width * bg_grass->getAnchorPoint ().x);
		 //log ("minx = %f", afterPos.x);
		 afterPos.x = MAX (afterPos.x, -size.width + Wsize.width + size.width * bg_grass->getAnchorPoint ().x);
		 //log ("maxx = %f", afterPos.x);

		 //���·�Χ����
		 afterPos.y = MIN (afterPos.y, size.height * bg_grass->getAnchorPoint ().y);
		 //log ("miny = %f", afterPos.y);
		 afterPos.y = MAX (afterPos.y, -size.height + Wsize.height + size.height * bg_grass->getAnchorPoint ().y);
		 //log ("maxy = %f", afterPos.y);

		 bg_grass->setPosition (afterPos);

		 //����ԭ��λ��
		 if (afterPos.x >= (size.width * bg_grass->getAnchorPoint ().x) ||
			 afterPos.x <= (-size.width + Wsize.width + size.width * bg_grass->getAnchorPoint ().x)) {
			 delta.x = 0;
		 }

		 if (afterPos.y >= (size.height * bg_grass->getAnchorPoint ().y) ||
			 afterPos.y <= (-size.height + Wsize.height + size.height * bg_grass->getAnchorPoint ().y)) {
			 delta.y = 0;
		 }
		 origin += delta;

		 //���ƶ�,��Ϊ����
		 longPress = false;
		 this->unschedule (schedule_selector (GameScene::updatePress));
	 }

 };

 void GameScene::onTouchesEnded (const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	 log ("onTouchesEnded.");
	 
	 this->unschedule (schedule_selector (GameScene::updatePress));

	 if (touches.size()==1) {	//������

		 auto touch = touches [0];
		 auto position = touch->getLocation ();

		 if (longPress) {

			 if (tiletype == GROUND) {
				 log ("onTouchesEnded_GROUND.");

				 //���ز��ֲ�
				 auto tileW = map->getBoundingBox ().size.width / mapSize.width;
				 auto seedpanel = SeedChooseLayer::create ();
				 seedpanel->setPosition (Vec2(position.x - tileW/2, position.y+tileW/2));
				 seedpanel->setTag (SEEDPANEL_TAG);
				 this->addChild (seedpanel, 10000);
			 }
			 else if(tiletype == CROPS) {
				 log ("onTouchesEnded_CROPS.");

			 }
			 else if(tiletype == CROPS_HARVEST) {
				 log ("onTouchesEnded_CROPS_HARVEST.");

			 }
			 else {
				 log ("onTouchesEnded_OTHER.");

			 }

			 longPress = false;

		 }
	 }

 };

 void GameScene::updatePress (float dt) {
	 log ("updatePress.");

	 longPress = true;
	 this->unschedule (schedule_selector (GameScene::updatePress));	 
 };

 //������������е�ImageView����
 void GameScene::selectItemFunc (Ref* pSender, Widget::TouchEventType type) {
	 log ("selectItemFunc.");

	 //��ȡ��ѡ���Widget�����ĸ�Widget
	 auto widget = static_cast<Widget*>(pSender);
	 auto parentWidget = static_cast<Widget*>(widget->getParent ());
	 int tag = parentWidget->getTag ();
	 switch (type) {
		 case cocos2d::ui::Widget::TouchEventType::BEGAN:
			 log ("**********************BEGAN***************************");

			 //�����Ʒ,�Ŵ�ѡ����Ʒ
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1.5), 0.2f));	
			 break;
		 case cocos2d::ui::Widget::TouchEventType::MOVED:
			 log ("**********************MOVED***************************");

			 //������Ʒ���
			 if (isOut && panel_shop) {		
				 isOut = false;
				 panel_shop->runAction (
					 EaseElasticOut::create (
						 MoveBy::create (1.0f,
										 Vec2 (-panel_shop->getContentSize ().width * 6 / 11, 0)
						 ),
						 0.5f
					 )
				 );
			 }

			 log ("touchMovePos = %f, %f", widget->getTouchMovePos ().x, widget->getTouchMovePos ().y);

			 //���tempSpr�Ƿ����,��������ڣ��ȴ���;���������ֱ���ƶ�
			 if (tempSpr==NULL) {
				 tempSpr = Sprite::create (shopMove_textures[tag - SHOP_ITEM_SPRITE_TAG]);
				 // ��tempSpr��ӵ�bg_grass�ϣ�����tempSpr��λ�þ��������bgSprite��
				 tempSpr->setAnchorPoint (Vec2(0.5f, 0.25f));
				 bg_grass->addChild (tempSpr, 100);
			 }
			 else {
				 Vec2 pos;
				 pos.x = (widget->getTouchMovePos ().x - origin.x) / bg_grass->getScale ();
				 pos.y = (widget->getTouchMovePos ().y - origin.y) / bg_grass->getScale ();
				 log ("pos = %f, %f", pos.x, pos.y);
				 tempSpr->setPosition (pos);

				 //�ƶ���ʱʵ�ļ�⵱ǰ��Ʒ�ܷ񱻷��ã������bg_grass������, item�ı�ǣ�
				 this->moveItemCheckFunc (pos, tag-SHOP_ITEM_SPRITE_TAG);
			 }

			 break;
		 case cocos2d::ui::Widget::TouchEventType::ENDED:
			 log ("**********************ENDED***************************");

			 //��Сѡ����Ʒ
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1), 0.2f));

			 isCanBulid = false;
			 break;
		 case cocos2d::ui::Widget::TouchEventType::CANCELED:
			 log ("**********************CANCELED***************************");

			 //��Сѡ����Ʒ
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1), 0.2f));

			 auto endPos = Vec2 ((widget->getTouchEndPos().x - origin.x)/bg_grass->getScale(), (widget->getTouchEndPos().y - origin.y)/bg_grass->getScale());
			 auto tilePoint = this->convertTotileCoord (endPos);

			 //���Խ���,�ı�õ��gid
			 if (isCanBulid) {

				 //��nowPointλ��������һ��GIDΪ��9 + tag - SHOP_ITEM_SPRITE_TAG������Ƭ,���Ӧ�Ź������е���Ʒ
				 auto tempGid = 9 + tag - SHOP_ITEM_SPRITE_TAG;

				 if (tempGid == 15) {
					 tempGid = 9;
				 }
				 if (tempGid == 16) {
					 tempGid = 12;
				 }

				 log ("tempGid = %d", tempGid);
				 map_goodslayer->setTileGID (tempGid, tilePoint);
			 }
			 else { //���ܽ��裬��ʾ��ʾͼƬ

				 auto screenPos = this->convertToScreenCoord (tilePoint);
				 auto tipSpr = Sprite::create ("tip.png");
				 tipSpr->setPosition (screenPos);
				 bg_grass->addChild (tipSpr, 4000);

				 auto scale1 = ScaleTo::create (0.2, 1.1);
				 auto scale2 = ScaleTo::create (0.2, 1.0);
				 tipSpr->runAction (Sequence::create (scale1,
													  scale2,
													  DelayTime::create (0.5f),
													  CallFunc::create (CC_CALLBACK_0 (Sprite::removeFromParent, tipSpr)),
													  NULL));
				 map_tipslayer->removeTileAt (perPos);
			 }

			 if (tempSpr!=NULL) {
				 tempSpr->removeFromParent ();
				 tempSpr = NULL;
			 }
			 break;
		 //default:
			// break;
	 }

 };

 void GameScene::moveItemCheckFunc (Vec2 position, int tag) {
	 log ("moveItemCheckFunc."); 

	 isCanBulid = false;
	 perPos = currPos;

	 //����ת��Ϊ��Ƭ����
	 auto tilePoint = this->convertTotileCoord (position);
	 
	 //�ƶ�������,ʱʵ�ı任tempSpr��ͼƬ�����á����ã�
	 // ����Ƭ��ͼ�ķ�Χ֮��
	 if (tilePoint.x>=0&&(tilePoint.x<=mapSize.width-1) && tilePoint.y>=0&&(tilePoint.y<=mapSize.height-1)) {

		 //��ǰ�ײ�������λ��
		 currPos = tilePoint;

		 auto gid = map_goodslayer->getTileGIDAt (tilePoint);	//ȡ����ǰ���gid
		 if (gid==0) {	//��ʾ�˴����Խ��н��裨����ɫ��
			 tempSpr->setTexture (shopMove_textures [tag]);
			 isCanBulid = true;
		 }
		 else {	//��ʾ�˴��Ѿ�����Ʒ�����ܽ��н��裨����ɫ��
			 tempSpr->setTexture (shopMove_en_textures [tag]);
			 isCanBulid = false;
		 }

		 //�Ż��϶�����
		 tempSpr->setPosition (this->convertToScreenCoord (tilePoint));

		 //�ж���Ʒ�Ƿ����ƶ�,��������ʾ
		 if (perPos != currPos) {
			 //���
			 map_tipslayer->removeTileAt (touchObjectPos);
			 map_tipslayer->removeTileAt (perPos);
			 map_tipslayer->setTileGID (17, currPos);
		 }

	 }
	 else {	//����Ƭ��ͼ��Χ֮�⣨����ɫ��
		 tempSpr->setPosition (position);
		 tempSpr->setTexture (shopMove_en_textures [tag]);
		 //�Ƴ�����
		 map_tipslayer->removeTileAt (perPos);
		 isCanBulid = false;
	 }
 };

 void GameScene::checkTileType () {
	 log ("CheckTileType.");

	 int gid = map_goodslayer->getTileGIDAt (touchObjectPos);
	 switch (gid) {
		 case 9:
			 tiletype = TileType::GROUND;
			 log ("checkTileType_GROUND");
			 break;
		 case 18:
		 case 20:
		 case 22:
			 tiletype = TileType::CROPS;
			 log ("checkTileType_CROPS");
			 break;
		 case 19:
		 case 21:
		 case 23:
			 tiletype = TileType::CROPS_HARVEST;
			 log ("checkTileType_CROPS_HARVEST");
			 break;
		 default:
			 tiletype = TileType::OTHER;
			 log ("checkTileType_OTHER");
			 break;
	 }
	 
 };

 //��Ļ����ת��Ϊ��ͼ����
 Vec2 GameScene::convertTotileCoord (Vec2 position) {

	 //�������ź�ÿ���߿�Ŀ�Ⱥͳ���
	 auto tileW = map->getBoundingBox ().size.width / mapSize.width;
	 auto tileH = map->getBoundingBox ().size.height / mapSize.height;

	 //�õ��߿��ͼ����x,y
	 int x = mapSize.height - position.y / tileH + position.x / tileW - mapSize.width / 2;
	 int y = mapSize.height - position.y / tileH - position.x / tileW + mapSize.width / 2;
	 
	 return Vec2 (x, y);
 }

 //��convertTotileCoord�෴
 Vec2 GameScene::convertToScreenCoord (Vec2 tilePoint) {

	 auto tileSize = map->getTileSize ();
	 auto tileW = map->getBoundingBox ().size.width / map->getMapSize ().width;
	 auto tileH = map->getBoundingBox ().size.height / map->getMapSize ().height;

	 auto variable1 = (tilePoint.x + mapSize.width / 2 - mapSize.height) * tileW * tileH;
	 auto variable2 = (-tilePoint.y + mapSize.width / 2 + mapSize.height) * tileW * tileH;

	 int x = (variable1 + variable2) / 2 / tileH;
	 int y = (variable2 - variable1) / 2 / tileW;

	 return Vec2 (x, y);
 }

