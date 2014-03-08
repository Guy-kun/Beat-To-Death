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

	static cocos2d::Layer* layer();

private:
	CCSprite* bgImage;
};

#endif 
