//
//  MyRole.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__MyRole__
#define __LhTestGame__MyRole__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class MyRole:public CCSprite{
    
public:
    virtual bool init();
    CCPoint oldpoint;
    int pos;
    int petId;
    bool isInsprite(CCTouch  * touch);
    CREATE_FUNC(MyRole);
};

#endif /* defined(__LhTestGame__MyRole__) */
