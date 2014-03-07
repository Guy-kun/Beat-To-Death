#ifndef __TILE_LAYER_H__
#define __TILE_LAYER_H__

#include "cocos2d.h"
#include "ABox.h"

USING_NS_CC;

class BoxLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BoxLayer);
	virtual bool init();
	~BoxLayer();

	static cocos2d::Layer* layer();

private:
	std::vector<ABox*> boxes;
};

#endif 
