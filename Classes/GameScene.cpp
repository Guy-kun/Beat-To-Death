#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	String simfileDirectory = String("simfiles/[Tweety3187] Necrofantasia/");
	String simfileToLoad = String("simfiles/[Tweety3187] Necrofantasia/Trance.sm");
	currentSimfile = new Simfile(simfileToLoad);
	//Play music

	std::stringstream ss;
	ss << simfileDirectory.getCString() << currentSimfile->getMusicFileName().getCString();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ss.str().c_str());


	//Generate points for level 0
	generateLevelPoints(0);

	boxLayer = BoxLayer::create();
	addChild(boxLayer);
    return true;
}

void GameScene::generateLevelPoints(int level){
	if (level == 1){
		levelPoints.push_back(ccp(200,100));
		levelPoints.push_back(ccp(400,100));
	}
}


void GameScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
