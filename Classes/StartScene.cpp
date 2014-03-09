#include "StartScene.h"
#include <atlstr.h>
#include <atlconv.h>

USING_NS_CC;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

vector<wstring> get_all_files_within_folder()
{
	vector<wstring> names;
	wchar_t search_path[200];
	wchar_t curr_path[256];
	_wgetcwd(curr_path, 255);

	wsprintf(search_path, L"%s\\simfiles\\*", curr_path);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{

	image = CCSprite::create();
	image->initWithFile("titlescreen.png");
	image->setAnchorPoint(ccp(0, 0));
	addChild(image);


	vector<wstring> beatmapDirs = get_all_files_within_folder();
	for (int i = beatmapDirs.size()-1; i >=0; i--){
		int count = beatmapDirs.size() - i;
		wstring dir = beatmapDirs[i];
		string dirStr = CW2A(dir.c_str());

		stringstream ss;
		ss << std::to_string(count).c_str() << ". " << dirStr;
		//Ignore
		if (!(lstrcmpW(dir.c_str(), L".") == 0 || lstrcmpW(dir.c_str(), L"..") == 0))
		{
			dirs.push_back(dirStr);
			CCLabelTTF* ttf1 = CCLabelTTF::create(ss.str().c_str(), "Arial Bold", 24,
				CCSizeMake(1000, 40), kCCTextAlignmentCenter);
			//ttf1->setColor(ccc3(55, 175, 220));
			ttf1->setPosition(ccp(500, 50 + (100 * i)));
			ttf1->getTexture()->setAntiAliasTexParameters();
			addChild(ttf1);
		}
	}

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(StartScene::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(StartScene::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

void StartScene::startGameWithDir(string dir){
	Scene* game = GameScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5, game));
}

void StartScene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		CCDirector::getInstance()->end();
		break;
	case EventKeyboard::KeyCode::KEY_1:
		if (dirs.size() > 0)
			startGameWithDir(dirs[0]);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		if (dirs.size() > 1)
			startGameWithDir(dirs[1]);
		break;
	case EventKeyboard::KeyCode::KEY_3:
		if (dirs.size() > 2)
			startGameWithDir(dirs[2]);
		break;
	}
}

void StartScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

}


void StartScene::menuCloseCallback(Object* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
