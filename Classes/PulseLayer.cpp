#include "PulseLayer.h"

bool PulseLayer::init(){
	bgOverlay = CCSprite::create();
	bgOverlay->initWithFile("bgOverlay.png");
	bgOverlay->setAnchorPoint(ccp(0, 0));
	bgOverlay->setOpacity(0);
	addChild(bgOverlay);

	redLayer = CCLayerColor::create();
	redLayer->initWithColor(ccc4(227, 55, 55, 255));
	redLayer->setOpacity(0);
	addChild(redLayer);
	return true;
}

void PulseLayer::flashWhite(float timeToFadeAway){
	bgOverlay->stopAllActions();

	bgOverlay->setOpacity(255);
	CCFadeOut* fadeOutAction = CCFadeOut::create(timeToFadeAway);
	bgOverlay->runAction(fadeOutAction);
}

void PulseLayer::flashRed(float timeToFadeAway){
	redLayer->stopAllActions();

	redLayer->setOpacity(255);
	CCFadeOut* fadeOutAction = CCFadeOut::create(timeToFadeAway);
	redLayer->runAction(fadeOutAction);
}