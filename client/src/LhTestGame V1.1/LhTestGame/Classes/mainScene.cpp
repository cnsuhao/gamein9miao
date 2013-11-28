//
//  mainScene.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "mainScene.h"
#include "GameData.h"
#include "message.h"
#include "BattleScene.h"
#include "shop.h"
static int m_id[7]={0};

CCScene * mainScene::scene(){
    CCScene * m_scene= CCScene::create();
    CCLayer * m_layer=mainScene::create();
    m_scene->addChild(m_layer);
    return m_scene;
}
bool mainScene::init(){
    
    if(!CCLayer::init()){
        return false;
    }
    socket=GameData::shareGameData()->socket;
    myroleflag=false;
    setTouchEnabled(true);
    arr=CCArray::create();
    arr->retain();
    
    UILayer * ul=UILayer::create();
    ul->setTag(200);
    this->addChild(ul);
    ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("mainLayer_1.json"));
    UIButton * btn= dynamic_cast<UIButton *>(ul->getWidgetByTag(800));
    sendList();
    btn->addReleaseEvent(this, coco_releaseselector(mainScene::touchlisten));
    for (int i=0; i<7; i++) {
        UIButton * btn= dynamic_cast<UIButton *>(ul->getWidgetByTag(100+i));
        btn->addReleaseEvent(this, coco_releaseselector(mainScene::sendBattleMsg));
    }
    for (int i=0; i<9; i++) {
        UIButton * btn= dynamic_cast<UIButton *>(ul->getWidgetByTag(400+i));
        btn->addReleaseEvent(this, coco_releaseselector(mainScene::touchlisten));
        
        MyRole * sp=MyRole::create();
        sp->setVisible(false);
        if(i%2==1){
            sp->initWithFile("icon_02.png");
        }else{
            sp->initWithFile("icon_01.png");
        }
        sp->setPosition(btn->getPosition());
        sp->setTag(1000+i+1);
        this->addChild(sp);
        sp->oldpoint=btn->getPosition();
        btn->removeFromParent();
        
        
    }
    setName();
    sendList();
    sendPet();
    return true;
}
void mainScene::setName(){
    std::string str= GameData::shareGameData()->scoredata;
    CSJson::Reader reader;
    CSJson::Value root;
    if (reader.parse(str.c_str(), root)) {
        CSJson::Value data;
        data=root["data"];
        UILayer *ul=(UILayer *)this->getChildByTag(200);
        UILabel * btn= dynamic_cast<UILabel *>(ul->getWidgetByTag(300));
        btn->setText(data["name"].asString().c_str());
    }
}
void mainScene::sendList(){
    CSJson::FastWriter writer;
    CSJson::Value root;
    
    root["characterId"]=GameData::shareGameData()->charId;
    root["userId"]=GameData::shareGameData()->userID;
    
    
    std::string str= writer.write(root);
    Message * personMsg= socket->constructMessage(str.c_str(), 3700);
    socket->sendMessage_(personMsg, false);
    this->schedule(schedule_selector(mainScene::getList));
}
void mainScene::getList(){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(3700);
    if(msg){
        this->unschedule(schedule_selector(mainScene::getList));
        GameData::shareGameData()->dic->removeObjectForKey(3700);
        
        UILayer *ul=(UILayer *)this->getChildByTag(200);
        CSJson::Reader reader;
        CSJson::Value root;
        CSJson::Value datas;
        CSJson::Value list;
        if(reader.parse(msg->data,root)){
            datas=root["data"];
            list=datas["data"];
            listsize=list.size();
            CCLog("%d",list.size());
            CCLog("%s",msg->data);
            for (int i=0; i<list.size(); i++) {
                
                CSJson::Value das=list[i];
                
                UILabel * btn= dynamic_cast<UILabel *>(ul->getWidgetByTag(200+i));
                btn->setText(das["nickname"].asString().c_str());
                std::string str=das["nickname"].asString();
                if(i>2){
                    m_id[i-3]=das["id"].asInt();
                    m_name[i-3]=str.c_str();

                    CCLog("%s",m_name[1]);
                    CCLog("%d   %d",i,i-3);
                }
            }
        }
    }
}
void mainScene::sendPet(){
    CSJson::FastWriter writer;
    CSJson::Value sendMessage;
    sendMessage["characterId"]=GameData::shareGameData()->charId;
    
    string json_file_jianghu=writer.write(sendMessage);
    Message *jianghuMsg=socket->constructMessage(json_file_jianghu.c_str(), 2306);
    socket->sendMessage_(jianghuMsg, false);
    this->schedule(schedule_selector(mainScene::getPet));
}
void mainScene::getPet(){
    Message *revMsg=(Message *)GameData::shareGameData()->dic->objectForKey(2306);
    if(revMsg){
        
        this->unschedule(schedule_selector(mainScene::getPet));
        
        GameData::shareGameData()->dic->removeObjectForKey(2306);
        const char * data=revMsg->data;
        CCLog("%s",data);
        CSJson::Reader reader;
        CSJson::Value root;
        CSJson::Value jsonData;
        CSJson::Value matrix;
        if (reader.parse(data, root)) {
            jsonData=root["data"];
            matrix=jsonData["matrix"];
            //            nowcount=matrix.size()-1;
            for(int i=0;i<matrix.size();i++)
            {
                
                int tmpchatid =matrix[i]["chaid"].asInt();
                
                if (1) {
                    int pos =matrix[i]["pos"].asInt();
                    MyRole * role= (MyRole *)this->getChildByTag(1000+pos);
                    role->petId=tmpchatid;
                    role->setVisible(true);

                    
                    
                }
                
                
                
            }

        }
    }
}
void mainScene::receive(cocos2d::CCObject *object){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(3704);
    if(msg){
        this->unschedule(schedule_selector(mainScene::receive));
        GameData::shareGameData()->dic->removeObjectForKey(3704);
        CSJson::Reader reader;
        CSJson::Value root;
        if (reader.parse(msg->data, root)) {
            GameData::shareGameData()->str=msg->data;
            CCScene * scene=BattleScene::scene();
            CCDirector::sharedDirector()->replaceScene(scene);
        }
    }
    
}
void mainScene::touchlisten(){
    
}
void  mainScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-99900, true);
    CCLayer::registerWithTouchDispatcher();
}
bool mainScene::ccTouchBegan(CCTouch* touch, CCEvent* event){
    
    for (int i=0; i<listsize; i++) {
        MyRole * sp=(MyRole *)this->getChildByTag(i+1000+1);
       // if(sp->isVisible()){
        myroleflag=sp->isInsprite(touch);
        
        if (myroleflag) {
            arr->removeAllObjects();
            role0=sp;
            oldpoint=sp->getPosition();
            break;
        }
       // }
        
    }
    CCPoint touchPoint=touch->getLocation();
    CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
    if (reallyPoint.x>286&&reallyPoint.x<700&&reallyPoint.y>117&&reallyPoint.y<535) {
        return true;
    }else{
        return false;
    }
    
    return true;
}
void mainScene::ccTouchMoved(CCTouch* touch, CCEvent* event){
    if(myroleflag){
        
        CCPoint touchPoint=touch->getLocation();
        CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
        role0->setPosition(reallyPoint);
        
    }
}
void mainScene::ccTouchEnded(CCTouch* touch, CCEvent* event){
 
    if(myroleflag){
        myroleflag=false;
        arr->removeAllObjects();
        for (int i=0; i<listsize; i++) {
            
            MyRole * sp=(MyRole *)this->getChildByTag(i+1000+1);
           // if(sp->isVisible()){
            myroleflag=sp->isInsprite(touch);
            
            if (myroleflag) {
                CCLog("%d",sp->getTag());
                arr->addObject(sp);
               
            }
           // }
        }
        CCLog("%d",arr->count());
        if (arr->count()==2) {
            int a=0;
            int b1=0;
            MyRole *fr=(MyRole *)arr->objectAtIndex(0);
            MyRole *sr=(MyRole *)arr->objectAtIndex(1);
            CCPoint fp=fr->oldpoint;
            CCPoint sp=sr->oldpoint;
            a=fr->pos;
            b1=sr->pos;
            fr->pos=b1;
            sr->pos=a;
            fr->oldpoint=sp;
            sr->oldpoint=fp;
            fr->setPosition(sp);
            sr->setPosition(fp);
        }else{
            if (ccpDistance(role0->getPosition(), oldpoint)==0) {
                CCLog("equal");
                for (int i=0; i<listsize; i++) {
                    MyRole * sp=(MyRole *)this->getChildByTag(i+1000+1);
             
                    myroleflag=sp->isInsprite(touch);
                
                    if (myroleflag) {
                            
                        sendPersonMsg(sp->petId);
                    }
                }
               
                
            }
            role0->setPosition(oldpoint);
        }
    }
}
void mainScene::sendBagMsg(){
    CSJson::FastWriter writer;
    CSJson::Value root;
    root["characterId"]=GameData::shareGameData()->charId;
    std::string str= writer.write(root);
    Message * msg= (Message *)socket->constructMessage(str.c_str(), 803);
    socket->sendMessage_(msg, false);
    this->schedule(schedule_selector(mainScene::receiveBagMsg));
    
}
void mainScene::receiveBagMsg(){
    Message * msg= (Message * )GameData::shareGameData()->dic->objectForKey(803);
    if(msg){
        this->unschedule(schedule_selector(mainScene::receiveBagMsg));
        GameData::shareGameData()->dic->removeObjectForKey(804);
        CSJson::Reader reader;
        CSJson::Value root;
        if (reader.parse(msg->data, root)) {
            CCLog("%s",msg->data);
            GameData::shareGameData()->bagData=msg->data;
            
            sendShopMsg();
        }
    }
}
void mainScene::sendShopMsg(){
    CSJson::FastWriter writer;
    CSJson::Value value;
    value["characterId"]=GameData::shareGameData()->charId;
    std::string str= writer.write(value);
    Message * msg= (Message *)socket->constructMessage(str.c_str(), 801);
    socket->sendMessage_(msg, false);
    this->schedule(schedule_selector(mainScene::receiveShopMsg));
    
}
void mainScene::sendPersonMsg(int personId){
    CSJson::FastWriter writer;
    CSJson::Value root;
    root["characterId"]=GameData::shareGameData()->charId;
    root["pet_id"]=personId;
    GameData::shareGameData()->personId=personId;
    std::string str=writer.write(root);
    CCLog("%s",str.c_str());
    Message * msg=(Message *)socket->constructMessage(str.c_str(), 804);
    socket->sendMessage_(msg, false);
    this->schedule(schedule_selector(mainScene::receivePersonMsg));
    
}
void mainScene::receivePersonMsg(){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(804);
    if (msg) {
        this->schedule(schedule_selector(mainScene::receivePersonMsg));
        GameData::shareGameData()->dic->removeObjectForKey(804);
        CSJson::Reader reader;
        CSJson::Value root;
        if (reader.parse(msg->data, root)) {
            GameData::shareGameData()->szData=msg->data;
            CCLog("%s",msg->data);
            sendBagMsg();
        }
    }
}
void mainScene::receiveShopMsg(){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(801);
    if(msg){
        this->unschedule(schedule_selector(mainScene::receiveShopMsg));
        GameData::shareGameData()->dic->removeObjectForKey(801);
        CSJson::Reader read;
        CSJson::Value root;
        if (read.parse(msg->data, root)) {
            CCLog("%s",msg->data);
            GameData::shareGameData()->shopData=msg->data;
            openShop();
        }
    }
    
}
void mainScene::sendBz(){
    int characterId=GameData::shareGameData()->charId;
    
    CSJson::FastWriter writer;
    CSJson::Value sendMessage;
    CSJson::Value item;
    CSJson::Value arrayObj;
    sendMessage["characterId"]=characterId;
    for (int i=1; i<10; i++) {
        MyRole * dz=(MyRole *)this->getChildByTag(1000+i);
        if(dz->isVisible()){
            if(dz->pos<=9||dz->pos>=1){
                item["roleid"]=dz->petId;
                item["pos"]=dz->pos;
                arrayObj.append(item);
            }
        }
    }
    sendMessage["setting"]=arrayObj;
    string json_file_jianghu=writer.write(sendMessage);
    
    
    
    CCLog("%s",json_file_jianghu.c_str());
    Message *jianghuMsg=socket->constructMessage(json_file_jianghu.c_str(), 2307);
    socket->sendMessage_(jianghuMsg, false);
    
    //SocketManager::getInstance()->sendMessage(json_file_jianghu.c_str(), 3505);
    this->schedule(schedule_selector(mainScene::receiveBz),0.01);
}
void mainScene::receiveBz(){
    Message* revMsg = (Message*)GameData::shareGameData()->dic->objectForKey(2307);
    
    //    CCLOG("势力revMsg==%s",revMsg);
    if(revMsg)
    {
        this->unschedule(schedule_selector(mainScene::receiveBz));
        GameData::shareGameData()->dic->removeObjectForKey(2307);
        char * ditu=revMsg->data;
        //解析数据
        
        CCLog("%s\n",ditu);
        
        CSJson::Reader read;
        CSJson::Value value;
        if(read.parse(ditu, value))
        {
            
            sendBattleMsg(NULL);
            
        }
    }
}
void mainScene::openShop(){
    shop * sp=shop::create();
    this->addChild(sp,20);
    this->setTouchEnabled(false);

}
void mainScene::sendBattleMsg(CCObject *sender){
    UIWidget * s=(UIWidget *)sender;
    CCLog("%d",s->getTag());
    
    CSJson::FastWriter writer;
    CSJson::Value root;
    
    CCLog("%s",m_name[0]);
    GameData::shareGameData()->enemName=m_name[s->getTag()-100];
    root["tid"]=m_id[s->getTag()-100];
    root["characterId"]=GameData::shareGameData()->charId;
    std::string str= writer.write(root);
    CCLog("%s",str.c_str());
    Message *jianghuMsg=socket->constructMessage(str.c_str(), 3704);
    socket->sendMessage_(jianghuMsg, false);
    this->schedule(schedule_selector(mainScene::receive));
}
void mainScene::closeShop(){
//    this->removeChildByTag(300);
//    this->setTouchEnabled(true);
}

void mainScene::BattleEnter(){
    
}