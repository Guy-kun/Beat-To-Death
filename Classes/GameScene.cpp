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
	isInLeadIn = true;
	elapsedTime = 0.0f;
	currentBeatNoRaw = 0.0f;
	lastBeatFlashedOn = 0;

	String simfileDirectory = String("simfiles/[Tweety3187] Necrofantasia/");
	String simfileToLoad = String("simfiles/[Tweety3187] Necrofantasia/Trance.sm");
	currentSimfile = new Simfile(simfileToLoad);

	currentBPM = currentSimfile->getBPMs()[0].second;
	//Play music
	std::stringstream ss;
	ss << simfileDirectory.getCString() << currentSimfile->getMusicFileName().getCString();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ss.str().c_str());


	//Generate points for level 0
	generateLevelPoints(1);

	
	pulseLayer = PulseLayer::create();
	addChild(pulseLayer);
	boxLayer = BoxLayer::create();
	addChild(boxLayer);


	scheduleUpdate();

	boxLayer->initFixedBoxes(levelPoints);
    return true;
}

void GameScene::update(float delta){
	elapsedTime += delta;
	if (isInLeadIn)
	{
		if (elapsedTime > currentSimfile->getOffset())
			isInLeadIn = false;
	}
	else
	{
		currentBeatNoRaw += 60000.0f / currentBPM * delta;

		//Beat number
		double beatNo = floor(currentBeatNoRaw);
		//Update BPM
		for (int i = currentSimfile->getBPMs().size() - 1; i >= 0; i--)
		{
			std::pair<double, float> p = currentSimfile->getBPMs()[i];
			if (beatNo > p.first)
			{
				currentBPM = p.second;
				break;
			}
		}
		//Flash
		if (beatNo - lastBeatFlashedOn > FLASH_BEATCOUNT)
		{
			lastBeatFlashedOn += FLASH_BEATCOUNT;
			pulseLayer->flashWhite(0.5f);
		}
	}
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
