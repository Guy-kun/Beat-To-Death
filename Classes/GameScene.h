#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "BoxLayer.h"
#include "Simfile.h"
#include "SimpleAudioEngine.h"  
#include "PulseLayer.h"
#include "BGLayer.h"
#include <CCEventKeyboard.h>


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void update(float delta);
	void visit();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

private:
	int survivalMultiplier;
	int hueVal;
	GLuint hueUniformLocation;
	RenderTexture* rTex;

	//Box stuff
	BoxLayer* boxLayer;
	BGLayer* bgLayer;
	std::vector<std::pair<Point,BoxType>> levelPoints;

	//Simfile stuff
	Simfile* currentSimfile;

	void generateLevelPoints();

	bool isInLeadIn;
	float elapsedTime;
	float currentBPM;

	double currentBeatNoRaw;

	double lastBeatFlashedOn;
	double lastBeatDiedOn;

	//FX
	PulseLayer* pulseLayer;
	float FLASH_BEATCOUNT;
	float DEATH_BEATCOUNT;
};

#endif
