#ifndef __SIMFILE_H__
#define __SIMFILE_H__

#include "cocos2d.h"
#include "FileReader.h"

USING_NS_CC;

class Simfile 
{
public:
	Simfile(String pathToFile);
	~Simfile();

	float getOffset(){ return offset; };
	String getFullTitle(){ return "blah"; };
	String getMusicFileName(){ return musicFilename; };
	std::vector<std::pair<long, float>> getBPMs(){ return BPMs; };

private:
	float offset;
	String title;
	String artist;
	String musicFilename;
	std::vector<std::pair<long, float>> BPMs;
};

#endif 
