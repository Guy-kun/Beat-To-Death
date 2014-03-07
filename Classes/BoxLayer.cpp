#include "BoxLayer.h"

USING_NS_CC;

Layer* BoxLayer::layer()
{
	Layer *layer = Layer::create();
	return layer;
}

bool BoxLayer::init()
{
	ABox* sampleBox = new ABox(Static);
	sampleBox->setPosition(ccp(100, 100));

	boxes.push_back(sampleBox);
	addChild(sampleBox);

	return true;
}

BoxLayer::~BoxLayer(){
	//TODO: remove all boxes
}