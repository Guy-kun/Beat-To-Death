#include "ABox.h"

USING_NS_CC;
#define PTM_RATIO 32


ABox::ABox(BoxType t, b2World* world){
	type = t;

	//TODO vary based on type
	sprite = Sprite::create();
	sprite->initWithFile("CloseNormal.png");
	addChild(sprite);

	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.userData = this;

	boxBody = world->CreateBody(&boxBodyDef);
	
	boxShape.SetAsBox(getSprite()->getContentSize().width / PTM_RATIO,
		getSprite()->getContentSize().height / PTM_RATIO);

	
	boxShapeDef.shape = &boxShape;
	boxShapeDef.density = 10.0f;
	boxShapeDef.friction = 0.4f;
	boxShapeDef.restitution = 0.1f;
	boxBody->CreateFixture(&boxShapeDef);

}

void ABox::setPosition(const Point &point){
	Node::setPosition(point);
	boxBody->SetTransform(b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO),0);
}


void ABox::visit(){
	Node::setPosition(ccp(boxBody->GetPosition().x*PTM_RATIO, boxBody->GetPosition().y*PTM_RATIO));

	sprite->setPosition(getPosition());
	sprite->setAnchorPoint(getAnchorPoint());
	sprite->setZOrder(getZOrder());
	sprite->visit();
}

ABox::~ABox(){
	//TODO: clear up body etc
}