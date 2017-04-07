#include "HelloWorldScene.h"

//use
#include "Utils\GlobalManager.h"
#include "Utils/Config.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
//using namespace cocostudio::timeline;

//#include "Utils\Config.h"
//#include "cocostudio\CocoStudio.h"
//using namespace cocostudio;

USING_NS_CC;

//资源数目
static int resCount = 0;

bool HelloWorld::init()
{

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//加载CSB
	_rootNode = CSLoader::createNode("LoadingLayer.csb");
	_loadingBar = static_cast<LoadingBar*>(_rootNode->getChildByName("LoadingBar_1"));
	_text = static_cast<Text*>(_rootNode->getChildByName("Text_1"));

    this->addChild(_rootNode);
	_rootNode->setOpacity(0);

	auto loadingResFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::loadingRes, this));
	auto action = Sequence::create(FadeTo::create(1.0f, 255),
								   loadingResFunc,
								   nullptr);
	_rootNode->runAction(action);

    return true;
}

//开始加载资源
void HelloWorld::loadingRes() {

	auto cache = Director::getInstance()->getTextureCache();	//缓存

	//资源异步加载(6)
	cache->addImageAsync(IMG_CHAPTER_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_GRAY_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_HOME_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_LOADING_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_WORLD_BG, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BG_MAP, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_TOWN_HOME, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_TOWN_CHAPTER, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_TOWN_LIBERATE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_MIWU, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_BUBBLE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_GOLD, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_WOOD, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_RING, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_BUTTON_INFOOPT, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUTTON_UPGRADEOPT, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUTTON_CANTUPGRADEOPT, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUTTON_ENTEROPT, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUTTON_CANCLE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUTTON_OK, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_BUILD_PRO, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILD_PRO_BK, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILD_PRO_ENEMY, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_SKILL_BSKILL, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_SKILL_ZSKILL, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_SKILL_ZZSKILL, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_BULLET_ARROW, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BULLET_SHELL, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BULLET_SHELL_RED, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BULLET_FIRE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BULLET_LASER, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_CIRCLE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_CIRCLE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ArrowTip, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_BaseTower, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Raider, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_HeroHotel, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Camp, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ResearchLab, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_MineFactory, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_WoodFactory, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ArrowTower, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Cannon, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Laser, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_BaseTower_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Raider_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_HeroHotel_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Camp_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ResearchLab_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_MineFactory_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_WoodFactory_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ArrowTower_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Cannon_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Laser_Big, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_BaseTower_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Raider_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_HeroHotel_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Camp_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ResearchLab_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_MineFactory_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_WoodFactory_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_ArrowTower_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Cannon_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));
	cache->addImageAsync(IMG_BUILDING_Laser_Broken, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	cache->addImageAsync(IMG_TREE, CC_CALLBACK_0(HelloWorld::loadResourcesUpdate, this));

	//加载动画(7)
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_FIGHTER, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_BOWMAN, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_GUNNER, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_MEATSHIELD, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_HERO_ARAGORN, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_SKILL_1, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(ANIM_SKILL_2, this, schedule_selector(HelloWorld::loadResourcesUpdateAmr));

};		   

void HelloWorld::loadResourcesUpdateAmr(float dt) {
	//log("loadResourcesUpdateAmr");
	
	this->updateLoadingPrg();
};

void HelloWorld::loadResourcesUpdate() {
	//log("load");

	this->updateLoadingPrg();
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, png);
};

void HelloWorld::updateLoadingPrg() {

	resCount++;
	log("Loaded : %d", resCount);
	//更新进度条
	float percent = 100*resCount/72;	//一共需要加载72次
	_loadingBar->setPercent(percent);
	_text->setString(StringUtils::format("%d%c", (int)_loadingBar->getPercent(), '%'));

	//加载完成,场景跳转
	if((int)_loadingBar->getPercent()>=100) {

		auto changeSceneFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::changeScene, this));
		auto delaytime = DelayTime::create(0.5f);
		this->runAction(
			Sequence::create(
			delaytime,
			changeSceneFunc,
			nullptr
		)
		);
	}
};

//场景跳转
void HelloWorld::changeScene() {
	//log("changeScene");

	//GM()->enterHomeScene();
	GlobalManager::getInstance()->enterHomeScene();
};

Scene* HelloWorld::createScene() {

	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}