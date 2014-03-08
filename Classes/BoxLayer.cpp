#include "BoxLayer.h"

USING_NS_CC;

#define PTM_RATIO 1

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

	ABox* sampleBox = new ABox(Player,_world);
	sampleBox->setPosition(ccp(100, 100));
	boxes.push_back(sampleBox);
	addChild(sampleBox);

	ABox* sampleBox2 = new ABox(Player, _world);
	sampleBox2->setPosition(ccp(200, 500));
	boxes.push_back(sampleBox2);
	addChild(sampleBox2);
	
	scheduleUpdate();

	return true;
}

void BoxLayer::initFixedBoxes(std::vector<Point> points){
	for (int i = 0; i < points.size(); i++) {
		ABox* box = new ABox(Static, _world);
		box->setPosition(points[i]);

		boxes.push_back(box);
		addChild(box);
	}
}
void BoxLayer::update(float delta){
	_world->Step(delta, 8, 1);
}
void BoxLayer::movePlayer(InputDirection direction){

}

BoxLayer::~BoxLayer(){
	//TODO: remove all boxes
}