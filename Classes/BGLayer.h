#ifndef __BG_LAYER_H__
#define __BG_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BGLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BGLayer);
	virtual bool init();
	~BGLayer(){};
	void update(float delta);
	static cocos2d::Layer* layer();

private:
	CCSprite* bgImage;
	CCSprite* goMarker;

	int timeToCompleteMovement;
	float timeElapsed;
};

#endif 
