//
//  role.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-25.
//
//

#include "role.h"

bool role::init(){
    if(!CCArmature::init()){
        return false;
    }
    changeHp=0;
    resName="";
    chaId=0;
    skillId=0;
    pos=0;
    resNum=0;
    curHP=0;
    totalHp=0;
    dir=0;
    return true;
}
void role::whetherDead(){
    
}
bool role::isDead(){
    if(changeHp+curHP<0){
        return true;
    }
    return false;
}
void role::initArm(const char *armName){
    this->cocos2d::extension::CCArmature::init(armName);
}
void role::playArm(const char *playName){
    this->getAnimation()->play(playName);
}
void role::addBlood(){
    CCSprite * blood= CCSprite::create();
    CCSprite * blood_bg=CCSprite::create();
    blood_bg->addChild(blood);
    
    
    
    
}
void role::setBloodChange(float changeBlood){
    curHP=curHP+changeBlood;
}