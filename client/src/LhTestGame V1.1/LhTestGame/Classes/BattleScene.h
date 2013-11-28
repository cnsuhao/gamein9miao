//
//  BattleScene.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__BattleScene__
#define __LhTestGame__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "role.h"
using namespace cocos2d;
using namespace extension;
using namespace CSJson;

class BattleScene:public CCLayer{
public:
    virtual bool init();
    CCArray *deadArr;
    CCNode * pNode;
    role * ene_role;
    role * my_role;
    int chaBattleId;
    int eneBattleId;
    CCArray * ene_Arr;
    static CCScene * scene();
    void runAttack();
    void moreAttack();
    void moreEneHurt();
    void moreWhetherDead();
    CSJson::Value alluseValue;
    void eneHurt(CCArmature * arm,MovementEventType type,const char * name);
    void whetherDead(CCArmature * arm,MovementEventType type,const char * name);
    int rounds;
    void getJsonData(const char * data);
    void initAttackData(CSJson::Value value);
    void initRole(CSJson::Value value);
    CREATE_FUNC(BattleScene);
};
#endif /* defined(__LhTestGame__BattleScene__) */
