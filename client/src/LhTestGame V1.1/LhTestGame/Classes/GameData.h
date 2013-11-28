//
//  GameData.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__GameData__
#define __LhTestGame__GameData__

#include <iostream>
#include "cocos2d.h"
#include "SocketClient.h"
using namespace cocos2d;
class GameData{
public:
    GameData();
    ~GameData();
    SocketClient * socket;
    CCDictionary * dic;
    std::string enemName;
    std::string roleName;
    std::string scoredata;
    std::string bagData;
    std::string shopData;
    std::string szData;
    int personId;
    int userID;
    int charId;
    std::string  str;
    static GameData * shareGameData();
    CCDictionary * roleDic;
};
#endif /* defined(__LhTestGame__GameData__) */
