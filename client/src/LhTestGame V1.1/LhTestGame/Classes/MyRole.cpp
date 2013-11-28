//
//  MyRole.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-25.
//
//

#include "MyRole.h"

bool MyRole::init(){
    if(!CCSprite::init()){
        return false;
    }
    
    
    pos=0;
    return true;
}
bool MyRole::isInsprite(cocos2d::CCTouch *touch){
    CCPoint touchPoint=touch->getLocation();
    CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
    CCLog("%f %f %f %f",reallyPoint.x,reallyPoint.y,this->getPosition().x,this->getPosition().y);
    CCRect rect=CCRectMake(this->getPosition().x-50,this->getPosition().y-50, 95, 107);
    if(rect.containsPoint(reallyPoint)){
        
        return true;
    }
    return false;
}