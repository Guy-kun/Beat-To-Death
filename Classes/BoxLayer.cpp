#include "BoxLayer.h"

USING_NS_CC;

#define PTM_RATIO 32

bool BoxLayer::init()
{
	Size screenSize = Director::getInstance()->getWinSize();

	// box2d shit
	b2Vec2 gravity;
	gravity.Set(0.0f, -8.0f);
	boolean doSleep = true;
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	_groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundShape;
	groundShape.Set(b2Vec2(0, 0), b2Vec2(screenSize.width / PTM_RATIO, 0));
	_groundBody->CreateFixture(&groundShape, 0);

	ABox* sampleBox = new ABox(Static,_world);
	sampleBox->setPosition(ccp(100, 100));

	boxes.push_back(sampleBox);
	addChild(sampleBox);
	
	scheduleUpdate();

	return true;
}

void BoxLayer::initFixedBoxes(std::vector<Point> points){

}
void BoxLayer::update(float delta){
	_world->Step(delta, 8, 1);
}

BoxLayer::~BoxLayer(){
	//TODO: remove all boxes
}