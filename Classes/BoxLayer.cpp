#include "BoxLayer.h"

USING_NS_CC;

#define PTM_RATIO 30

bool BoxLayer::init()
{
	Size screenSize = Director::getInstance()->getWinSize();

	// box2d shit
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	boolean doSleep = true;
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);

	/*
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	_groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundShape;
	groundShape.Set(b2Vec2(0, 0), b2Vec2(screenSize.width / PTM_RATIO, 0));
	_groundBody->CreateFixture(&groundShape, 0);
	*/

	spawnPlayer();
	
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

	if (getPlayer()->getPosition().y < 0) {
		killPlayer(false);
	}

	if (!toDelete.empty()) {
		for (int i = toDelete.size() - 1; i >= 0; i--) {
			removeChild(toDelete[i]);
			toDelete[i]->release();
		}
		toDelete.clear();
	}
}

ABox* BoxLayer::getPlayer() {
	for (int i = boxes.size()-1; i >= 0; i--) {
		if (boxes[i]->getType() == Player) {
			return boxes[i];
		}
	}
}

void BoxLayer::spawnPlayer() {
	ABox* player = new ABox(Player, _world);
	player->setPosition(ccp(100, 150));
	boxes.push_back(player);
	addChild(player);
}

void BoxLayer::killPlayer(bool newBody) {
	for (int i = boxes.size() - 1; i >= 0; i--) {
		ABox* player = boxes[i];
		if (player->getType() == Player) {
			if (newBody) {
				player->kill();
			} else {
				toDelete.push_back(player);
				boxes.erase(boxes.begin() + i);
			}
		}
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"boom.wav");
	spawnPlayer();
}
bool BoxLayer::canPlayerBeKilled(){
	for (int i = boxes.size() - 1; i >= 0; i--) {
		ABox* player = boxes[i];
		if (player->getType() == Player) {
			return player->getBoxBody()->GetPosition().x * PTM_RATIO> 151;
		}
	}
}

void BoxLayer::resetBodies(){

}

void BoxLayer::movePlayer(InputDirection direction){
	ABox* player = getPlayer();
	b2Vec2 vel = player->getBoxBody()->GetLinearVelocity();
	if (direction == UP) {
		if (abs(vel.y) < 0.2) {
			vel.y = 10;//upwards - don't change x velocity
			player->getBoxBody()->SetLinearVelocity(vel);
		}
	}
	else if (direction == LEFT) {
		vel.x = -5;
		player->getBoxBody()->SetLinearVelocity(vel);
	}
	else if (direction == RIGHT) {
		vel.x = 5;
		player->getBoxBody()->SetLinearVelocity(vel);
	}
	else if (direction == DOWN) {
		killPlayer(true);
	}
}

BoxLayer::~BoxLayer(){
	//TODO: remove all boxes
}