#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BoxLayer.h"
#include "Simfile.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	//Box stuff
	BoxLayer* boxLayer;
	std::vector<Point> levelPoints;

	//Simfile stuff
	Simfile* currentSimfile;

	void generateLevelPoints(int level);
};

#endif // __HELLOWORLD_SCENE_H__
