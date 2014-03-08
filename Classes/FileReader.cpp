// FileReader.cpp
#include "FileReader.h"
#include <fstream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

vector< string > FileReader::ReadFile(string pFileName, char pMode) {
	vector< string > mFileContents;
	// Initialize variables needed
	long fileSize = 0;
	unsigned char * fileContents = NULL;
	string thisLine, result, fullPath, contents;

    
	// Get absolute path of file
	fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName.c_str());

	// Get data of file
	fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize);
	contents.append((char *) fileContents);

	// Create a string stream so that we can use getline( ) on it
	istringstream fileStringStream(contents);

	// Get file contents line by line
	while (getline(fileStringStream, thisLine)) {
		// Put all lines in vector
		mFileContents.push_back(thisLine);
	}

	// After this, mFileContents will have an extra entry and will have the value '\x04'.
	// We should remove this by popping it out the vector.
	mFileContents.pop_back();

	// Delete buffer created by fileContents. This part is required.
	if (fileContents) {
		delete [] fileContents;
		fileContents = NULL;
	}

	return mFileContents;
}