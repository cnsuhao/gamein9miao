//
//  GameOver.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__GameOver__
#define __LhTestGame__GameOver__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace extension;
using namespace CSJson;
class GameOver:public CCLayerColor{
public:
    virtual bool init();
    CCLabelTTF * label1;
    void setData(const char * data);
    CREATE_FUNC(GameOver);
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    CCMenu * menu;
    void goback();
    bool menuflag;
};
#endif /* defined(__LhTestGame__GameOver__) */
