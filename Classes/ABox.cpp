#include "ABox.h"

USING_NS_CC;

ABox::ABox(BoxType t){
	type = t;

	//TODO vary based on type
	sprite = Sprite::create();
	sprite->initWithFile("CloseNormal.png");
	addChild(sprite);
}


void ABox::visit(){
	sprite->setPosition(getPosition());
	sprite->setAnchorPoint(getAnchorPoint());
	sprite->setZOrder(getZOrder());
	sprite->visit();
}

ABox::~ABox(){
	//TODO: clear up body etc
}