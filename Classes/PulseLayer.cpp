#include "PulseLayer.h"

bool PulseLayer::init(){
	whiteLayer = CCLayerColor::create();
	whiteLayer->initWithColor(ccc4(255, 255, 255, 255));
	whiteLayer->setOpacity(0);
	addChild(whiteLayer);
	return true;
}

void PulseLayer::flashWhite(float timeToFadeAway){
	whiteLayer->stopAllActions();

	//whiteLayer->setOpacity(255);
	//CCFadeOut* fadeOutAction = CCFadeOut::create(timeToFadeAway);
	//whiteLayer->runAction(fadeOutAction);
}