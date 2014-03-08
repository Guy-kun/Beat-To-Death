#include "BGLayer.h"
#include <CCTexture2D.h>


bool BGLayer::init(){
	timeToCompleteMovement = 3;
	timeElapsed = 0.0f;

	bgImage = CCSprite::create();
	bgImage->initWithFile("bg.png");
	bgImage->setAnchorPoint(ccp(0, 0));
	addChild(bgImage);

	bgOverlay = CCSprite::create();
	bgOverlay->initWithFile("bgOverlay.png");
	bgOverlay->setAnchorPoint(ccp(0, 0));
	bgOverlay->setOpacity(125);
	addChild(bgOverlay);

	scheduleUpdate();
	return true;
}

void BGLayer::update(float delta){
	timeElapsed += delta;
	if (timeElapsed >= timeToCompleteMovement)
	{
		timeElapsed = 0.0f;
		bgImage->setPosition(ccp(0, 0));
	}
	else
	{
		bgImage->setPosition(
			ccp(-500 * (timeElapsed / timeToCompleteMovement), -500 * (timeElapsed / timeToCompleteMovement))
			);
	}
}
