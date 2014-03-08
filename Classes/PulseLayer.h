#ifndef __PULSE_LAYER_H__
#define __PULSE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PulseLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(PulseLayer);
	virtual bool init();
	~PulseLayer(){};

	void flashWhite(float timeToFadeAway);
	static cocos2d::Layer* layer();

private:
	CCLayerColor* whiteLayer;
};

#endif 
