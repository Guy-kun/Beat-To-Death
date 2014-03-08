#ifndef __ABOX_H__
#define __ABOX_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

enum BoxType{
	Player,Dead,Static
};

class ABox : public cocos2d::Node
{
public:
	ABox(BoxType t, b2World* world);
	~ABox();

	void visit();
	void setPosition(const Point &point) override;

	CCSprite* getSprite(){ return sprite; };
private:
	BoxType type;
	Sprite* sprite;
	// Body
	b2BodyDef sampleBoxBodyDef;
	b2Body* sampleBoxBody;
	b2PolygonShape sampleBoxShape;
	b2FixtureDef sampleBoxShapeDef;
};

#endif 
