#include "AppDelegate.h"
#include "GameScene.h"
#include "UseSqlite.hpp"
#include "Helper.hpp"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "PluginChartboost/PluginChartboost.h"

USING_NS_CC;

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
    
    sdkbox::PluginChartboost::init();
    
    sdkbox::PluginGoogleAnalytics::init();
    sdkbox::PluginGoogleAnalytics::startSession();
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("SyuraProject", Rect(0, 0, 640, 1136));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);

    FileUtils::getInstance()->addSearchPath("res");

    //ヘルパークラスを初期化
    Helper::getInstance()->getInstance();
    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();
//    auto scene = UseSqlite::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    sdkbox::PluginGoogleAnalytics::stopSession();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
