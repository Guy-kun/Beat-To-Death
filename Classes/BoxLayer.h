#ifndef __BOX_LAYER_H__
#define __BOX_LAYER_H__

#include "cocos2d.h"
#include "ABox.h"
#include "Box2D\Box2D.h"
#include "SimpleAudioEngine.h"  


USING_NS_CC;

enum InputDirection{
	UP, DOWN, LEFT, RIGHT, NONE
};

class BoxLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BoxLayer);
	virtual bool init();
	~BoxLayer();

	void initFixedBoxes(std::vector<std::pair<Point, BoxType>> boxInput);
	void update(float delta);
	ABox* getPlayer();
	ABox* getGoal();
	void movePlayer(InputDirection direction);
	void stopHorizontalMovement();
	void spawnPlayer();
	void killPlayer(bool newBody);
	void resetBodies();

	bool canPlayerBeKilled();


	static cocos2d::Layer* layer();

private:
	std::vector<ABox*> boxes;
	b2World* _world;
	b2Body* _groundBody;
	std::vector<ABox*> toDelete;
};

#endif 
