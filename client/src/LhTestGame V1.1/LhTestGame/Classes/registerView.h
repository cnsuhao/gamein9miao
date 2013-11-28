//
//  registerView.h
//  fengyanqi
//
//  Created by lh on 13-10-9.
//
//

#ifndef __fengyanqi__registerView__
#define __fengyanqi__registerView__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;
class registerView:public CCLayerColor{
public:
    CCSize size;
    virtual bool init();
    void menuCallBackClose();
    void menuCallBackRegister();
    virtual void  registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
     static   size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p);
    void registerSuccess();
    CCMenu * menu;
    bool menuflag;
    CCEditBox * registerusername;
    CCEditBox * firPassword;
    bool firFlag;
    bool secFlag;
    CCEditBox * secPassword;
    bool registerBool;
    CREATE_FUNC(registerView);
};
#endif /* defined(__fengyanqi__registerView__) */
