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
	Size winSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	rTex = RenderTexture::create(winSize.width, winSize.height);
	rTex->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	rTex->retain();

	timeBar = CCLayerColor::create(ccc4(227, 55, 55, 200), 1000, 20);
	timeBar->setAnchorPoint(ccp(0, 1));
	timeBar->setPosition(ccp(-500, 495));
	addChild(timeBar);

	survivalMultiplier = 2;
	isInLeadIn = true;
	elapsedTime = 0.0f;
	currentBeatNoRaw = 0.0f;
	lastBeatFlashedOn = 0;
	lastBeatDiedOn = 0;
	hueVal = 0;

	String simfileDirectory = String("simfiles/[Tweety3187] Necrofantasia/");
	String simfileToLoad = String("simfiles/[Tweety3187] Necrofantasia/Trance.sm");
	currentSimfile = new Simfile(simfileToLoad);

	currentBPM = currentSimfile->getBPMs()[0].second;
	FLASH_BEATCOUNT = 2.0f /(currentBPM/180);
	DEATH_BEATCOUNT = FLASH_BEATCOUNT * 6 *survivalMultiplier;
	//Play music
	std::stringstream ss;
	ss << simfileDirectory.getCString() << currentSimfile->getMusicFileName().getCString();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(ss.str().c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3f);


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

	//Load shader
	GLProgram* prog = new GLProgram();
	prog->initWithVertexShaderFilename("default.vert", "default.frag");
	//Cocos2dx attribs
	prog->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	prog->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	prog->link();
	prog->updateUniforms();

	hueUniformLocation = glGetUniformLocation(prog->getProgram(), "hueAdjust");

	CCShaderCache::sharedShaderCache()->addProgram(prog, "defaultProgram");
	rTex->getSprite()->setShaderProgram(prog);
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
		//Beat number
		double beatNo = floor(currentBeatNoRaw);

		int b = (int)beatNo % 100;
		if (b > 50)
			hueVal += 1;
		else
			hueVal -= 1;
		CCLOG("Hueval %d", hueVal);


		//Update BPM
		for (int i = currentSimfile->getBPMs().size() - 1; i >= 0; i--)
		{
			std::pair<double, float> p = currentSimfile->getBPMs()[i];
			if (beatNo > p.first)
			{
				currentBPM = p.second;
				FLASH_BEATCOUNT = 1.0f / (currentBPM / 180);
				DEATH_BEATCOUNT = FLASH_BEATCOUNT * 6 * survivalMultiplier;
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
			if (boxLayer->canPlayerBeKilled())
			{
				boxLayer->killPlayer(true);
				pulseLayer->flashRed(0.5f);
			}
		}
		timeBar->setPosition(ccp(-1000 + (1000 * ((currentBeatNoRaw - lastBeatDiedOn)/DEATH_BEATCOUNT)), timeBar->getPositionY()));
		
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

	for (int i = 0; i < rand() % 8; i++){
		int a = rand() % 3;

		levelPoints.push_back(std::pair<Point, BoxType>(ccp(200+ (rand()%700), rand()%450), (a==0?Kill:Static)));
	}

	levelPoints.push_back(std::pair<Point, BoxType>(ccp(100, 100),Static));
	levelPoints.push_back(std::pair<Point, BoxType>(ccp(900, rand() % 350),Goal));
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
	case EventKeyboard::KeyCode::KEY_SPACE:
		boxLayer->resetBodies();
		break;
	}
}
void GameScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		boxLayer->stopHorizontalMovement();
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		boxLayer->stopHorizontalMovement();
		break;
	}
}
void GameScene::visit(){
	rTex->beginWithClear(0.0f, 0.0f, 0.0f, 1.0f);
	bgLayer->visit();
	pulseLayer->visit();
	timeBar->visit();
	rTex->end();
	rTex->visit();
	glUniform1f(hueUniformLocation, (float)hueVal/100);

	boxLayer->visit();

}

void GameScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
