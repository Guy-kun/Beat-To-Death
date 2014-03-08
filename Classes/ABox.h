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

	void kill();

	CCSprite* getSprite() { return sprite; }
	BoxType getType() { return type; }
	b2Body* getBoxBody() { return boxBody; }
private:
	BoxType type;
	Sprite* sprite;
	//Used for dying
	Sprite* oldSprite;

	// Body
	b2BodyDef boxBodyDef;
	b2Body* boxBody;
	b2PolygonShape boxShape;
	b2FixtureDef boxShapeDef;
};

#endif 
