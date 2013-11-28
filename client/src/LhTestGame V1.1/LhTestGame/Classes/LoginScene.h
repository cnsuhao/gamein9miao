//
//  LoginScene.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__LoginScene__
#define __LhTestGame__LoginScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SocketClient.h"
#include "registerView.h"
using namespace cocos2d;
using namespace extension;
using namespace CSJson;
class LoginScene:public CCLayer{
public:
    virtual bool init();
    CCEditBox* editBoxUsername;
    CCEditBox* editBoxPassword;
    static CCScene * scene();
    void registers();
    void send_LoginData();
    void receive_LoginData(CCObject *sender);
    SocketClient * socket;
    void replaceScene();
    CREATE_FUNC(LoginScene);
};
#endif /* defined(__LhTestGame__LoginScene__) */
