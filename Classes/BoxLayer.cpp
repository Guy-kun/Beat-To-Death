#include "BoxLayer.h"

USING_NS_CC;

#define PTM_RATIO 32

bool BoxLayer::init()
{
	Size screenSize = Director::getInstance()->getWinSize();

	// box2d shit
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	boolean doSleep = true;
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	_groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundShape;
	groundShape.Set(b2Vec2(0, 0), b2Vec2(screenSize.width / PTM_RATIO, 0));
	_groundBody->CreateFixture(&groundShape, 0);

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
}

void BoxLayer::spawnPlayer() {
	ABox* player = new ABox(Player, _world);
	player->setPosition(ccp(200, 400));
	boxes.push_back(player);
	addChild(player);
}

void BoxLayer::killPlayer() {
	for (ABox* box : boxes) {
		if (box->getType() == Player) {
			box->kill();
		}
	}
}

void BoxLayer::movePlayer(InputDirection direction){
	for (ABox* player : boxes) {
		if (player->getType() == Player) {
			b2Vec2 vel = player->getBoxBody()->GetLinearVelocity();
			if (direction == UP) {
				if (abs(vel.y) < 0.1) {
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
				killPlayer();
			}
		}
	}
}

BoxLayer::~BoxLayer(){
	//TODO: remove all boxes
}