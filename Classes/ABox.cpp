#include "ABox.h"

USING_NS_CC;
#define PTM_RATIO 32


ABox::ABox(BoxType t, b2World* world){
	type = t;

	//TODO vary based on type
	sprite = Sprite::create();
	sprite->initWithFile("CloseNormal.png");
	addChild(sprite);

	sampleBoxBodyDef.type = b2_dynamicBody;
	sampleBoxBodyDef.userData = this;

	sampleBoxBody = world->CreateBody(&sampleBoxBodyDef);
	
	sampleBoxShape.SetAsBox(getSprite()->getContentSize().width / PTM_RATIO,
		getSprite()->getContentSize().height / PTM_RATIO);

	
	sampleBoxShapeDef.shape = &sampleBoxShape;
	sampleBoxShapeDef.density = 10.0f;
	sampleBoxShapeDef.friction = 0.4f;
	sampleBoxShapeDef.restitution = 0.1f;
	sampleBoxBody->CreateFixture(&sampleBoxShapeDef);

}

void ABox::setPosition(const Point &point){
	Node::setPosition(point);
	sampleBoxBody->SetTransform(b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO),0);
}


void ABox::visit(){
	Node::setPosition(ccp(sampleBoxBody->GetPosition().x*PTM_RATIO, sampleBoxBody->GetPosition().y*PTM_RATIO));

	sprite->setPosition(getPosition());
	sprite->setAnchorPoint(getAnchorPoint());
	sprite->setZOrder(getZOrder());
	sprite->visit();
}

ABox::~ABox(){
	//TODO: clear up body etc
}