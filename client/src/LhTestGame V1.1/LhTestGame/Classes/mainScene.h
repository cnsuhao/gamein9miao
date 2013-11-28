//
//  mainScene.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__mainScene__
#define __LhTestGame__mainScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MyRole.h"
#include "SocketClient.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;

class mainScene:public CCLayer{
public:
    SocketClient * socket;
    bool myroleflag;
    const char * m_name[20];
    int listsize;
    void sendList();
    void sendBz();
    void sendPersonMsg(int personId);
    void receivePersonMsg();
    void receiveBz();
    void getList();
    void setList();
    void setName();
    void sendPet();
    void getPet();
    void sendBagMsg();
    void receiveBagMsg();
    void sendShopMsg();
    void receiveShopMsg();
    virtual bool init();
    void receive(CCObject * object);
    MyRole * role0;
    CCArray * arr;
    CCPoint oldpoint;
    static CCScene * scene();
    void BattleEnter();
    void closeShop();
    void sendBattleMsg(CCObject * sender);
    void touchlisten();
    void openShop();
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    CREATE_FUNC(mainScene);
    
};
#endif /* defined(__LhTestGame__mainScene__) */
