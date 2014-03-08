#include "ABox.h"

USING_NS_CC;
#define PTM_RATIO 30


ABox::ABox(BoxType t, b2World* world){
	myWorld = world;
	type = t;

	//TODO vary based on type
	sprite = Sprite::create();
	if (type == Static) {
		sprite->initWithFile("inactive.png");
		boxBodyDef.type = b2_staticBody;
	}
	else if (type == Player) {
		sprite->initWithFile("player.png");
		boxBodyDef.type = b2_dynamicBody;
	}
	else if (type == Dead) {
		sprite->initWithFile("dead.png");
		boxBodyDef.type = b2_staticBody;
	}
	addChild(sprite);

	
	boxBodyDef.userData = this;

	boxBody = world->CreateBody(&boxBodyDef);
	
	boxShape.SetAsBox(getSprite()->getContentSize().width / PTM_RATIO / 2,
					  getSprite()->getContentSize().height / PTM_RATIO / 2); // need to divide by 2 for some reason

	boxShapeDef.shape = &boxShape;
	boxShapeDef.density = 10.0f;
	boxShapeDef.friction = 1.0f;
	boxShapeDef.restitution = 0.0f;
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

void ABox::kill() {
	removeChild(sprite);
	sprite = Sprite::create();
	sprite->initWithFile("inactive.png");
	addChild(sprite);

	boxBody->SetType(b2_staticBody);
}

ABox::~ABox(){
	myWorld->DestroyBody(boxBody);
	removeChild(sprite);
}