#ifndef __ABOX_H__
#define __ABOX_H__

#include "cocos2d.h"

USING_NS_CC;

enum BoxType{
	Player,Dead,Static
};

class ABox : public cocos2d::Node
{
public:
	ABox(BoxType t);
	~ABox();

	void visit();
	
private:
	BoxType type;
	Sprite* sprite;
	//TODO Body
};

#endif 
