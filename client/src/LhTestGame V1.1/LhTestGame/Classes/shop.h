//
//  shop.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__shop__
#define __LhTestGame__shop__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SocketClient.h"
using namespace cocos2d;
using namespace extension;
class shop:public CCLayer{
  
public:
    SocketClient * socket;
    virtual bool init();
    void menuCallBack();
    UILayer * layer;
    UIButton *touchBtn;
    bool touchFlag;
    void initBag();
    void initShop();
    void touchMoveEvent(CCObject * obj);
    CCPoint oldpos;
    int arrTag;
    void sendloadSkill(int skillId,int space,int petId);
    void receiveloadSkill();
    void initLoadSkill();
    void touchBeganEvent(CCObject *obj);
    void sendBuySkillMsg(int skillId);
    void receiveBuySkillMsg();
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void touchEndedEvent(CCObject * obj);
    void touchBeganEvent0(CCObject * obj);
    void touchMovedEvent0(CCObject * obj);
    void touchEndedEvent0(CCObject * obj);
    
    CREATE_FUNC(shop);

};
#endif /* defined(__LhTestGame__shop__) */
