#include "AppDelegate.h"
#include "UI/HelloScene/HelloWorldScene.h"

USING_NS_CC;

//use
//#include "Utils\DBManager.h"
//#include "Utils\DataManager.h"
//#include "Utils\Config.h"
//#include "cocostudio\CocoStudio.h"
//using namespace cocostudio;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Ring", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
	//TIMTIdirector->setContentScaleFactor(1440.0f/480.0f);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

	//this->loadResources();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::loadResources() {

	//创建数据库
	//DBM()->createTable();
	//将相关数据加载到内存中
	//DM();

	//加载搜索路径
	//FileUtils::getInstance()->addSearchPath("images");

	//加载动画
/*	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_FIGHTER);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_BOWMAN);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_GUNNER);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_MEATSHIELD);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_HERO_ARAGORN);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_SKILL_1);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_SKILL_2);	*/
	//auto scene = HelloWorld::createScene();
	//Director::getInstance()->runWithScene(scene);

};
