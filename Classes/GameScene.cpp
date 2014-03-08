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
	lastBeatDiedOn = 0;

	String simfileDirectory = String("simfiles/[Tweety3187] Necrofantasia/");
	String simfileToLoad = String("simfiles/[Tweety3187] Necrofantasia/Trance.sm");
	currentSimfile = new Simfile(simfileToLoad);

	currentBPM = currentSimfile->getBPMs()[0].second;
	FLASH_BEATCOUNT = 2.0f /(currentBPM/180);
	DEATH_BEATCOUNT = FLASH_BEATCOUNT * 6;
	//Play music
	std::stringstream ss;
	ss << simfileDirectory.getCString() << currentSimfile->getMusicFileName().getCString();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ss.str().c_str());


	//Generate points for level 0
	generateLevelPoints();

	bgLayer = BGLayer::create();
	addChild(bgLayer);
	pulseLayer = PulseLayer::create();
	addChild(pulseLayer);
	boxLayer = BoxLayer::create();
	addChild(boxLayer);


	scheduleUpdate();

	boxLayer->initFixedBoxes(levelPoints);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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
		currentBeatNoRaw += currentBPM /60.0f  * delta;
		CCLOG("CurrBeatRaw %f", currentBeatNoRaw);
		//Beat number
		double beatNo = floor(currentBeatNoRaw);
		//Update BPM
		for (int i = currentSimfile->getBPMs().size() - 1; i >= 0; i--)
		{
			std::pair<double, float> p = currentSimfile->getBPMs()[i];
			if (beatNo > p.first)
			{
				currentBPM = p.second;
				FLASH_BEATCOUNT = 2.0f / (currentBPM / 180);
				DEATH_BEATCOUNT = FLASH_BEATCOUNT * 6;
				break;
			}
		}
		//Flash
		if (currentBeatNoRaw - lastBeatFlashedOn >= FLASH_BEATCOUNT)
		{
			lastBeatFlashedOn += FLASH_BEATCOUNT;
			pulseLayer->flashWhite(0.5f);
		}
		//Death
		if(currentBeatNoRaw - lastBeatDiedOn >= DEATH_BEATCOUNT)
		{
			lastBeatDiedOn += DEATH_BEATCOUNT;
			boxLayer->killPlayer();
			pulseLayer->flashRed(0.5f);

		}
	}
}


void GameScene::generateLevelPoints(){
	int hash = 0;
	int offset = 'a' - 1;
	std::string s = string(currentSimfile->getFullTitle().getCString());
	for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
		hash = hash << 1 | (*it - offset);
	}
	srand(hash);

	levelPoints.push_back(ccp(100,100));
	levelPoints.push_back(ccp(900,rand()%350));
}

void GameScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		CCDirector::getInstance()->end();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		boxLayer->movePlayer(RIGHT);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		boxLayer->movePlayer(LEFT);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		boxLayer->movePlayer(UP);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		boxLayer->movePlayer(DOWN);
		break;
	}
}
void GameScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

}


void GameScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
