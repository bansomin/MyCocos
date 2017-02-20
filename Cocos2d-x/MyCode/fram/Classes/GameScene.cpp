
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

	 //背景层
	 maplayer = LayerColor::create ();
	 this->addChild (maplayer, -1);

	 //背景草丛
	 bg_grass = Sprite::create ("2.png");
	 bg_grass->setAnchorPoint (Vec2::ZERO);
	 bg_grass->setPosition (Vec2::ZERO);
	 maplayer->addChild (bg_grass);

	 //加载地图
	 map = TMXTiledMap::create ("map.tmx");
	 map->setAnchorPoint (Vec2::ZERO);
	 map->setPosition (Vec2::ZERO);
	 bg_grass->addChild (map, 1);

	 //初始地图层
	 this->initMapLayerFunc ();

	 currPos = Vec2 (0, 0);
	 perPos = currPos;

	 //背景树从
	 bg_tree = Sprite::create ("1.png");
	 bg_tree->setAnchorPoint (Vec2::ZERO);
	 bg_tree->setPosition (Vec2::ZERO);
	 bg_tree->setScale (2);
	 bg_grass->addChild (bg_tree, 2);

	 //底部高亮位置
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

	 //获得容器panel_shop
	 panel_shop = dynamic_cast<Layout*>(rootLayer->getChildByName ("panel_shop"));
	 btn_shop = dynamic_cast<Button*>(panel_shop->getChildByName ("btn_shop"));
	 btn_shop->addTouchEventListener (CC_CALLBACK_2 (GameScene::clickShopBtnFunc, this));

	 //获得滚动容器scrolview
	 scrollview = dynamic_cast<ScrollView*>(panel_shop->getChildByName ("scrolview"));

	 panel_item = dynamic_cast<Layout*>(scrollview->getChildByName ("panel_item"));

	 auto num = panel_item->getChildren ().size ();

	 for (int i = 0; i < num; i++) {

		 //获取底层
		 Sprite* itemSpr = static_cast<Sprite*>(panel_item->getChildren ().at (i));
		 itemSpr->setTag (SHOP_ITEM_SPRITE_TAG + i);

		 //获取商品图片
		 ImageView* image = static_cast<ImageView*>(itemSpr->getChildByName ("image"));
		 image->loadTexture (shop_textures [i]);
		 //绑定回调函数
		 image->addTouchEventListener (CC_CALLBACK_2 (GameScene::selectItemFunc, this));


		 //获取商品信息
		 TextField* text_info = static_cast<TextField*>(itemSpr->getChildByName ("text_info"));
		 text_info->setText (shop_info [i]);

		 //获取商品价格
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
			 //为panel_shop添加一个弹性动作

			 if (isOut && panel_shop) {	//已经弹出(运行隐藏动作)
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
			 else {		//未弹出（运行弹出动作）
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

	 //panel_shop动作
	 if (isOut && panel_shop) {	//已经弹出(运行隐藏动作)
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

	 if (touches.size()==1) {	//单点触摸
		 
		 auto touch = touches [0];
		 auto point = touch->getLocation ();

		 Vec2 pos;
		 pos.x = (point.x - origin.x) / bg_grass->getScale ();
		 pos.y = (point.y - origin.y) / bg_grass->getScale ();

		 auto tilePos = this->convertTotileCoord (pos);
		 if (tilePos.x>=0&&(tilePos.x<=mapSize.width-1) && tilePos.y>=0&&(tilePos.y<=mapSize.height-1)) {
	
			 int gid = map_goodslayer->getTileGIDAt (tilePos);
			 if (gid!=0) {
				 //清空
				 map_tipslayer->removeTileAt (touchObjectPos);
				 map_tipslayer->removeTileAt (perPos);
				 touchObjectPos = tilePos;
				 map_tipslayer->setTileGID (17, tilePos);

				 //按压情况
				 //longPress在开始按下的时候为true，如果移动，则取消设为false，
				 //在抬起的时候如果变量为true，那么执行schedule中的updatePress函数
				 //开启定时
				 this->schedule (schedule_selector (GameScene::updatePress), 2);

				 this->checkTileType ();
			 }
		 }
	 }


 };

 void GameScene::onTouchesMoved (const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	 log ("onTouchesMoved.");
	 log ("size = %d", touches.size ());

	 if (touches.size() >= 2) {	//多点缩放
	 //if (1) {

		 //得到两点
		 auto point1 = touches [0]->getLocation ();
		 //auto point2 = Vec2(100, 100);
		 auto point2 = touches [1]->getLocation ();
		 //log ("point1 = %f, %f", point1.x, point1.y);

		 //计算两触摸点上一时刻之间的距离(return sqrt(dx * dx + dy * dy);)
		 auto predistance = touches [0]->getPreviousLocation ().distance (point2);
		 //log ("predistance = %f", predistance);

		 //计算两点之间的距离
		 auto currdistance = point1.distance (point2);
		 //log ("currdistance = %f", currdistance);

		 //两点与原点的差向量,pointVec1/pointVec2是相对于bg_grass的位置
		 auto pointVec1 = point1 - origin;
		 //log ("pointVec1 = %f, %f", pointVec1.x, pointVec1.y);
		 auto pointVec2 = point2 - origin;
		 //log ("pointVec2 = %f, %f", pointVec2.x, pointVec2.y);

		 //两点的相对中点(point1.x + point2.x) / 2
		 auto relMidx = (pointVec1.x + pointVec2.x) / 2;
		 //log ("relMidx = %f", relMidx);
		 auto relMidy = (pointVec1.y + pointVec2.y) / 2;
		 //log ("relMidy = %f", relMidy);

		 /*
		 bgSprite的尺寸不断变化的，所以计算起锚点或进行边界处理时，一定要用它缩放后的尺寸宽高来计算，而不能是它本身的宽高。 
		 所以代码中计算bgSprite的尺寸我们用getBoundingBox函数来获得经过缩放和旋转之后的外框盒大小，
		 而不用getContentSize函数来获得节点原始的大小
		 */

		 //bg_grass的锚点
		 auto anchorx = relMidx / bg_grass->getBoundingBox ().size.width;
		 auto anchory = relMidy / bg_grass->getBoundingBox ().size.height;
		 //log ("anchor = %f， %f", anchorx, anchory);

		 //相对屏幕的中点
		 auto absMidx = (point1.x + point2.x) / 2;
		 auto absMidy = (point1.y + point2.y) / 2;

		 //缩放时为了避免出现空白的区域,需要做以下边界处理
		 //当bg_grass快要进入到屏幕时，修改bg_grass的位置（absMid）
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

		 //重新设置锚点我位置
		 bg_grass->setAnchorPoint (Vec2 (anchorx, anchory));
		 bg_grass->setPosition (Vec2 (absMidx, absMidy));

		 //计算缩放倍率（1--4之间）
		 auto scale = bg_grass->getScale ()*(currdistance/predistance);
		 scale = MIN (4, MAX(1, scale));
		 bg_grass->setScale (scale);

		 //更新原点位置
		 origin = Vec2 (absMidx, absMidy) - Vec2(bg_grass->getBoundingBox().size.width * anchorx, bg_grass->getBoundingBox().size.height * anchory);
	 }
	 else {		//单点移动

		 auto touch = touches [0];			//获取第一个触摸点
		 auto delta = touch->getDelta ();	//获取前后两次位置的偏移量，基于OpenGL坐标
		 //log ("delta = %f, %f", delta.x, delta.y);
		 auto beforePos = bg_grass->getPosition ();	//得到移动前bg_grass的位置
		 auto afterPos = beforePos + delta;			//得到移动后bg_grass的位置

		 auto size = bg_grass->getContentSize ();	//得到bg_grass的尺寸

		 //边界控制，约束bg_grass的位置
		 //左右范围控制
		 afterPos.x = MIN (afterPos.x, size.width * bg_grass->getAnchorPoint ().x);
		 //log ("minx = %f", afterPos.x);
		 afterPos.x = MAX (afterPos.x, -size.width + Wsize.width + size.width * bg_grass->getAnchorPoint ().x);
		 //log ("maxx = %f", afterPos.x);

		 //上下范围控制
		 afterPos.y = MIN (afterPos.y, size.height * bg_grass->getAnchorPoint ().y);
		 //log ("miny = %f", afterPos.y);
		 afterPos.y = MAX (afterPos.y, -size.height + Wsize.height + size.height * bg_grass->getAnchorPoint ().y);
		 //log ("maxy = %f", afterPos.y);

		 bg_grass->setPosition (afterPos);

		 //更新原点位置
		 if (afterPos.x >= (size.width * bg_grass->getAnchorPoint ().x) ||
			 afterPos.x <= (-size.width + Wsize.width + size.width * bg_grass->getAnchorPoint ().x)) {
			 delta.x = 0;
		 }

		 if (afterPos.y >= (size.height * bg_grass->getAnchorPoint ().y) ||
			 afterPos.y <= (-size.height + Wsize.height + size.height * bg_grass->getAnchorPoint ().y)) {
			 delta.y = 0;
		 }
		 origin += delta;

		 //有移动,则不为长按
		 longPress = false;
		 this->unschedule (schedule_selector (GameScene::updatePress));
	 }

 };

 void GameScene::onTouchesEnded (const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	 log ("onTouchesEnded.");
	 
	 this->unschedule (schedule_selector (GameScene::updatePress));

	 if (touches.size()==1) {	//单触点

		 auto touch = touches [0];
		 auto position = touch->getLocation ();

		 if (longPress) {

			 if (tiletype == GROUND) {
				 log ("onTouchesEnded_GROUND.");

				 //加载播种层
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

 //点击滚动容器中的ImageView触发
 void GameScene::selectItemFunc (Ref* pSender, Widget::TouchEventType type) {
	 log ("selectItemFunc.");

	 //获取所选择的Widget和他的父Widget
	 auto widget = static_cast<Widget*>(pSender);
	 auto parentWidget = static_cast<Widget*>(widget->getParent ());
	 int tag = parentWidget->getTag ();
	 switch (type) {
		 case cocos2d::ui::Widget::TouchEventType::BEGAN:
			 log ("**********************BEGAN***************************");

			 //点击商品,放大选中商品
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1.5), 0.2f));	
			 break;
		 case cocos2d::ui::Widget::TouchEventType::MOVED:
			 log ("**********************MOVED***************************");

			 //隐藏商品面板
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

			 //检测tempSpr是否存在,如果不存在，先创建;如果存在则直接移动
			 if (tempSpr==NULL) {
				 tempSpr = Sprite::create (shopMove_textures[tag - SHOP_ITEM_SPRITE_TAG]);
				 // 把tempSpr添加到bg_grass上，这样tempSpr的位置就是相对于bgSprite了
				 tempSpr->setAnchorPoint (Vec2(0.5f, 0.25f));
				 bg_grass->addChild (tempSpr, 100);
			 }
			 else {
				 Vec2 pos;
				 pos.x = (widget->getTouchMovePos ().x - origin.x) / bg_grass->getScale ();
				 pos.y = (widget->getTouchMovePos ().y - origin.y) / bg_grass->getScale ();
				 log ("pos = %f, %f", pos.x, pos.y);
				 tempSpr->setPosition (pos);

				 //移动中时实的检测当前物品能否被放置（相对于bg_grass的坐标, item的标记）
				 this->moveItemCheckFunc (pos, tag-SHOP_ITEM_SPRITE_TAG);
			 }

			 break;
		 case cocos2d::ui::Widget::TouchEventType::ENDED:
			 log ("**********************ENDED***************************");

			 //缩小选中商品
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1), 0.2f));

			 isCanBulid = false;
			 break;
		 case cocos2d::ui::Widget::TouchEventType::CANCELED:
			 log ("**********************CANCELED***************************");

			 //缩小选中商品
			 widget->runAction (EaseElasticInOut::create (ScaleTo::create (0.1f, 1), 0.2f));

			 auto endPos = Vec2 ((widget->getTouchEndPos().x - origin.x)/bg_grass->getScale(), (widget->getTouchEndPos().y - origin.y)/bg_grass->getScale());
			 auto tilePoint = this->convertTotileCoord (endPos);

			 //可以建设,改变该点的gid
			 if (isCanBulid) {

				 //在nowPoint位置上设置一个GID为（9 + tag - SHOP_ITEM_SPRITE_TAG）的瓦片,这对应着滚动层中的商品
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
			 else { //不能建设，显示提示图片

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

	 //坐标转换为瓦片坐标
	 auto tilePoint = this->convertTotileCoord (position);
	 
	 //移动过程中,时实的变换tempSpr的图片（可用、禁用）
	 // 在瓦片地图的范围之内
	 if (tilePoint.x>=0&&(tilePoint.x<=mapSize.width-1) && tilePoint.y>=0&&(tilePoint.y<=mapSize.height-1)) {

		 //当前底部高亮的位置
		 currPos = tilePoint;

		 auto gid = map_goodslayer->getTileGIDAt (tilePoint);	//取出当前点的gid
		 if (gid==0) {	//表示此处可以进行建设（可用色）
			 tempSpr->setTexture (shopMove_textures [tag]);
			 isCanBulid = true;
		 }
		 else {	//表示此处已经有物品，不能进行建设（禁用色）
			 tempSpr->setTexture (shopMove_en_textures [tag]);
			 isCanBulid = false;
		 }

		 //优化拖动操作
		 tempSpr->setPosition (this->convertToScreenCoord (tilePoint));

		 //判断物品是否有移动,并高亮显示
		 if (perPos != currPos) {
			 //清空
			 map_tipslayer->removeTileAt (touchObjectPos);
			 map_tipslayer->removeTileAt (perPos);
			 map_tipslayer->setTileGID (17, currPos);
		 }

	 }
	 else {	//在瓦片地图范围之外（禁用色）
		 tempSpr->setPosition (position);
		 tempSpr->setTexture (shopMove_en_textures [tag]);
		 //移除高亮
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

 //屏幕坐标转换为地图坐标
 Vec2 GameScene::convertTotileCoord (Vec2 position) {

	 //计算缩放后每个瓦块的宽度和长度
	 auto tileW = map->getBoundingBox ().size.width / mapSize.width;
	 auto tileH = map->getBoundingBox ().size.height / mapSize.height;

	 //得到瓦块地图坐标x,y
	 int x = mapSize.height - position.y / tileH + position.x / tileW - mapSize.width / 2;
	 int y = mapSize.height - position.y / tileH - position.x / tileW + mapSize.width / 2;
	 
	 return Vec2 (x, y);
 }

 //与convertTotileCoord相反
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

