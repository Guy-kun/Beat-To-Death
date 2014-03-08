/****************************************************************************
B2DebugDrawLayer.cpp

Created by Stefan Nguyen on Oct 8, 2012.

Copyright (c) 2013 Stefan Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "B2DebugDrawLayer.h"

using namespace cocos2d;

B2DebugDrawLayer* B2DebugDrawLayer::create(b2World* pB2World, float pPtmRatio)
{
  B2DebugDrawLayer *pRet = new B2DebugDrawLayer(pB2World, pPtmRatio);
  if (pRet && pRet->init())
  {
    pRet->autorelease();
    return pRet;
  }
  else
  {
    delete pRet;
    pRet = NULL;
    return NULL;
  }
}
B2DebugDrawLayer::B2DebugDrawLayer(b2World* pB2World, float pPtmRatio)
: mB2World(pB2World), mPtmRatio(pPtmRatio)
{
}

bool B2DebugDrawLayer::init()
{
  //////////////////////////////
  // 1. super init first

  if(!CCLayer::init())
  {
    return false;
  }
  
  mB2DebugDraw = new GLESDebugDraw( mPtmRatio );
  mB2World->SetDebugDraw(mB2DebugDraw);
  
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
  flags += b2Draw::e_aabbBit;
  flags += b2Draw::e_pairBit;
  flags += b2Draw::e_centerOfMassBit;
  mB2DebugDraw->SetFlags(flags);
  
  return true;
}


void B2DebugDrawLayer::draw()
{
  ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
  
  kmGLPushMatrix();
  
  mB2World->DrawDebugData();
  
  kmGLPopMatrix();
}
