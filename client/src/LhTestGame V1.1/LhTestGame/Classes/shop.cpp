//
//  shop.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-25.
//
//

#include "shop.h"
#include "GameData.h"
#include "message.h"
static int skillId[12]={0};
static int buySkill[12]={0};
bool shop::init(){
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    layer=UILayer::create();
    this->addChild(layer);
    layer->addWidget(CCUIHELPER->createWidgetFromJsonFile("shopLayer_1.json"));
    socket=GameData::shareGameData()->socket;
    UIButton * btn= dynamic_cast<UIButton *>(layer->getWidgetByTag(3));
    btn->addReleaseEvent(this, coco_releaseselector(shop::menuCallBack));
    initLoadSkill();
    initShop();
    initBag();
    return true;
}
void shop::initLoadSkill(){
    CSJson::Reader reader;
    CSJson::Value root;
    if (reader.parse(GameData::shareGameData()->szData, root)) {
        CSJson::Value data;
        
        data=root["data"];
        int skill1=data["skill_1"].asInt();
        int skill2=data["skill_2"].asInt();
        if (skill1!=0) {
            UIButton * btn= dynamic_cast<UIButton *>(layer->getWidgetByTag(33));
            btn->loadTextures("skill-01.png", "skill-01.png", "skill-01.png");
            btn->setVisible(true);
            
        }else if(skill2!=0){
            UIButton * btn= dynamic_cast<UIButton *>(layer->getWidgetByTag(34));
            btn->loadTextures("skill-02.png", "skill-02.png", "skill-02.png");
        }
        
       // CCLog()
    }
}
void shop::initShop(){
    CSJson::Reader reader;
    CSJson::Value root;
    if (reader.parse(GameData::shareGameData()->shopData, root)) {
        CSJson::Value data;
        data=root["data"];
        for (int i=0; i<data.size(); i++) {
            CCLog("%d",data[i].asInt());
            
            if (i<12) {
                skillId[i]=data[i].asInt();
                UIButton * btn= dynamic_cast<UIButton *>(layer->getWidgetByTag(109+i));
                char name[20]="";
                btn->addPushDownEvent(this, coco_pushselector(shop::touchBeganEvent));
                btn->addMoveEvent(this, coco_moveselector(shop::touchMoveEvent));
                btn->addReleaseEvent(this, coco_releaseselector(shop
                                                        ::touchEndedEvent));
                sprintf(name, "skill-%02d.png",i+1);
                btn->loadTextures(name, name, name);
                btn->setVisible(true);
            }
        }
    }
}
void shop::initBag(){
    CSJson::Reader reader;
    CSJson::Value root;
    if (reader.parse(GameData::shareGameData()->bagData, root)) {
        bool result=root["result"].asBool();
        if (result) {
            CSJson::Value data;
            data=root["data"];
            for (int i=0; i<data.size(); i++) {
                CCLog("%d",data[i].asInt());
                if (i<12) {
                    buySkill[i]=data[i].asInt();
                    arrTag=i;
                    UIButton * btn= dynamic_cast<UIButton *>(layer->getWidgetByTag(9+i));
                    btn->addPushDownEvent(this, coco_pushselector(shop::touchBeganEvent0));
                    btn->addMoveEvent(this, coco_moveselector(shop::touchMovedEvent0));
                    btn->addReleaseEvent(this, coco_moveselector(shop::touchEndedEvent0));
                    
                    char name[20]="";
                    sprintf(name, "skill-%02d.png",i+1);
                    btn->loadTextures(name, name, name);
                    btn->setVisible(true);
                }
            }
        }
    }
}
void shop::touchBeganEvent(CCObject *obj){
    oldpos=((UIButton *)obj)->getPosition();
    touchBtn= (UIButton *)obj;
}
void shop::touchMoveEvent(CCObject * obj){
    
    
   // touchBtn->setPosition(layer)
    CCLog("%f",oldpos.x);
}
void shop::sendBuySkillMsg(int skillId){
    CSJson::FastWriter writer;
    CSJson::Value root;
    root["characterId"]=GameData::shareGameData()->charId;
    root["skill_id"]=skillId;
    std::string str=writer.write(root);
    Message * msg= (Message *)socket->constructMessage(str.c_str(), 802);

    socket->sendMessage_(msg, false);
    this->schedule(schedule_selector(shop::receiveBuySkillMsg));

}
void shop::receiveBuySkillMsg(){
    Message * msg=(Message *)GameData::shareGameData()->dic->objectForKey(802);
    if (msg) {
        this->unschedule(schedule_selector(shop::receiveBuySkillMsg));
        GameData::shareGameData()->dic->removeObjectForKey(802);
        CCLog("%s",msg->data);
    }
}
void shop::touchEndedEvent(CCObject * obj){
    UIButton * btn= (UIButton *)obj;
    for (int i=0; i<12; i++) {
        UIButton * btn0= (UIButton *)layer->getWidgetByTag(9+i);
        if (ccpDistance(btn0->getPosition(), btn->getPosition())<30) {
            btn->setVisible(false);
           int tag= btn->getTag();
            char name[20]="";
            sendBuySkillMsg(skillId[tag-109]);
            sprintf(name, "skill-%02d.png",tag-109+1);
            btn0->loadTextures(name, name, name);
            btn0->setVisible(true);
            
        }else{
            btn->setPosition(oldpos);
        }
    }
    
}
void shop::touchEndedEvent0(cocos2d::CCObject *obj){
    UIButton * btn=(UIButton *)obj;
    if (btn->getTag()<=1005) {
        UIButton * btn0=(UIButton *)layer->getWidgetByTag(33);
        if (ccpDistance(btn0->getPosition(), btn->getPosition())<30) {
            btn0->setVisible(true);
            char name[20]="";
            int tag= btn->getTag();
            if (arrTag<11) {
                
            }
            sendloadSkill(buySkill[tag-9+1], 1, 0);
            sprintf(name, "skill-%02d.png",tag-9+1);
            btn0->loadTextures(name, name, name);
            
            btn->setVisible(false);
        }else{
            btn->setPosition(oldpos);
        }

    }else{
        UIButton * btn0=(UIButton *)layer->getWidgetByTag(34);
        if (ccpDistance(btn0->getPosition(), btn->getPosition())<30) {
            btn0->setVisible(true);
            char name[20]="";
            int tag= btn->getTag();
            sprintf(name, "skill-%02d.png",tag-9+1);
            btn0->loadTextures(name, name, name);
            btn->setVisible(false);
            sendloadSkill(buySkill[tag-9+1], 2, 0);
        }else{
            btn->setPosition(oldpos);
        }
    }
}
void shop::touchBeganEvent0(cocos2d::CCObject *obj){
    touchBtn=(UIButton *)obj;
    oldpos=touchBtn->getPosition();
    
}
void shop::touchMovedEvent0(cocos2d::CCObject *obj){
    
}
void shop::menuCallBack(){
    CCLayer * l=(CCLayer *)this->getParent();
    l->setTouchEnabled(true);
    this->removeFromParent();
}
void  shop::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-99900, true);
    CCLayer::registerWithTouchDispatcher();
}
bool shop::ccTouchBegan(CCTouch* touch, CCEvent* event){
    CCLog("1132344444");
    touchFlag=layer->ccTouchBegan(touch, event);
    return true;
}
void shop::ccTouchMoved(CCTouch* touch, CCEvent* event){
    //touchBtn->setPosition(touch->getLocation());
    if (touchFlag) {
        if (touchBtn) {
            touchBtn->setPosition(touch->getLocation());
        }
        
        layer->ccTouchMoved(touch, event);
    }
}
void shop::ccTouchEnded(CCTouch* touch, CCEvent* event){
    if (touchFlag) {
        layer->ccTouchEnded(touch, event);
        touchFlag=false;
    }
}
void shop::sendloadSkill(int skillId,int space,int petId){
    CSJson::FastWriter writer;
    CSJson::Value root;
    root["characterId"]=GameData::shareGameData()->charId;
    root["skill_id"]=skillId;
    root["pet_id"]=GameData::shareGameData()->personId;
    root["space"]=space;
    std::string str=writer.write(root);
    Message * msg= (Message *)socket->constructMessage(str.c_str(), 805);
    CCLog("%s",str.c_str());
    socket->sendMessage_(msg, false);
    this->schedule(schedule_selector(shop::receiveloadSkill));
    
    
}
void shop::receiveloadSkill(){
    Message * msg=(Message *)GameData::shareGameData()->dic->objectForKey(805);
    if (msg) {
        this->unschedule(schedule_selector(shop::receiveloadSkill));
        GameData::shareGameData()->dic->removeObjectForKey(805);
        CCLog("%s",msg->data);
    }
}

