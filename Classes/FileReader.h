#ifndef __DS_FILEREADER__
#define __DS_FILEREADER__

// FileReader.h
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class FileReader {
private:

public:
	static vector<string> ReadFile(string pFileName, char pMode = 'r');
};

#endif