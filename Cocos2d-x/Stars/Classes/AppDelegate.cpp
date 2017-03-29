
#include "Data.h"
#include "Audio.h"
#include "MenuScene.h"
#include "AppDelegate.h"

USING_NS_CC;

extern bool isMusic;
extern bool isSound;

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





//glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);

/********图片480*800**********
 *****设计分辨率和窗口缩放*******
 进入glview的create函数中修改窗口缩放
 
 **原为
 GLViewImpl* GLViewImpl::create(const std::string& viewName){
 auto ret = new (std::nothrow) GLViewImpl;
 if(ret && ret->initWithFullScreen(viewName)) {
 ret->autorelease();
 return ret;
 }
 return nullptr;
 }
 
 **修改为
 GLViewImpl* GLViewImpl::create(const std::string& viewName)
 {
 auto ret = new (std::nothrow) GLViewImpl;
 if(ret && ret->initWithRect(viewName, Rect(0, 0, 480, 800), 0.8f)) {
 ret->autorelease();
 return ret;
 }
 return nullptr;
 }
 
 *原来initWithRect中的第四个参数默认是1, 现修改为0.8,让电脑能够显示整个窗口.
 
 */

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
        glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);
    
    if(!glview) {
        glview = GLViewImpl::create("My Game");
                director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuScene::scene();

    // run
    director->runWithScene(scene);
    
//加载音乐
    Audio::getInstance()->prepare();
    
    if (isMusic) {
        Audio::getInstance()->playBGM();
    }
    else{
        Audio::getInstance()->pauseMusic();
    }
    
    if (!isSound) {
        Audio::getInstance()->pauseSound();
    }
    
    return true;
}

//进入后台
// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    printf("applicationDidEnterBackground\n");
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    //CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();

//进入后台暂停音乐
    Audio::getInstance()->pauseMusic();
    Audio::getInstance()->pauseSound();
}

//进入前台
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    printf("applicationWillEnterForeground\n");

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
//进入前台,启动音乐
    if (isMusic) {
        Audio::getInstance()->resumeMusic();
    }
    if (isSound) {
        Audio::getInstance()->resumeSound();
    }
}







