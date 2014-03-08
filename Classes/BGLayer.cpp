#include "BGLayer.h"
#include <CCTexture2D.h>


bool BGLayer::init(){
	timeToCompleteMovement = 3;
	timeElapsed = 0.0f;

	bgImage = CCSprite::create();
	bgImage->initWithFile("bg.png");
	bgImage->setAnchorPoint(ccp(0, 0));
	addChild(bgImage);

	goMarker = CCSprite::create();
	goMarker->initWithFile("goMarker.png");
	goMarker->setAnchorPoint(ccp(0, 0));
	goMarker->setPosition(ccp(151, 0));
	addChild(goMarker);

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
