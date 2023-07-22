#include "AppDelegate.h"
#include "AndroidLaunchingScene.h"
#include "HomeScene.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
  GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = GLViewImpl::createWithRect("Combine Number", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
    glview = GLViewImpl::create("Combine Number");
#endif
    director->setOpenGLView(glview);
  }
  FileUtils::getInstance()->addSearchPath("images/");
  FileUtils::getInstance()->addSearchPath("fonts/");
  FileUtils::getInstance()->addSearchPath("soundeffects/");
  
  // turn on display FPS
  director->setDisplayStats(false);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);
  
  // Set the design resolution
  glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
  register_all_packages();
  
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
  auto scene = HomeScene::createScene();
  director->runWithScene(scene);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  auto scene = AndroidLaunchingScene::createScene();
  director->runWithScene(scene);
#endif
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();
}
