//
//  role.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__role__
#define __LhTestGame__role__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace extension;
class role:public CCArmature{
public:
    int battleId;
    std::string resName;
    int chaId;
    int skillId;
    int pos;
    int resNum;
    int curHP;
    int changeHp;
    int totalHp;
    int dir;
    CCPoint oldpos;
    virtual bool init();
    bool isDead();
    void whetherDead();
    void initArm(const char * armName);
    void playArm(const char * playName);
    void addBlood();
    void setBloodChange(float changeBlood);
    CREATE_FUNC(role);
};
#endif /* defined(__LhTestGame__role__) */
