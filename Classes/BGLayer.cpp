#include "BGLayer.h"

bool BGLayer::init(){
	bgImage = CCSprite::create();
	bgImage->initWithFile("bg.png");
	bgImage->setAnchorPoint(ccp(0, 0));
	addChild(bgImage);
	return true;
}
