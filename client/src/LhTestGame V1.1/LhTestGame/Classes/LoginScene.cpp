//
//  LoginScene.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "LoginScene.h"
#include "message.h"
#include "GameData.h"
#include "mainScene.h"
#define ip "172.16.103.6"
#define port 11009
CCScene * LoginScene::scene(){
    CCScene * m_scene=CCScene::create();
    CCLayer * m_layer=LoginScene::create();
    m_scene->addChild(m_layer);
    return m_scene;
}

bool LoginScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
 //   CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoginScene::receive_LoginData), "101", NULL);
 
//    CCNode * pNode=cocos2d::extension:: CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("GameScene.json");
//    
//    
//    this->addChild(pNode);
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCSprite * bg= CCSprite::create("login_bg.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg);
    socket= new SocketClient(ip,port,1,1,NULL);
    socket->start();
    GameData::shareGameData()->socket=socket;

  //  this->send_LoginData();
    CCMenuItemImage * item1=CCMenuItemImage::create("login_up.png", "login_down.png", this, menu_selector(LoginScene::send_LoginData));
    item1->setPosition(ccp(240, -80));
    CCMenuItemImage * item2=CCMenuItemImage::create("register_up.png", "register_down.png",this,menu_selector(LoginScene::registers));
    item2->setPosition(ccp(240, -160));
    CCMenu * meu=CCMenu::create(item1,item2,NULL);
    this->addChild(meu,1);
    CCScale9Sprite *bg1 = CCScale9Sprite::create("login_kong.png");
    editBoxUsername = CCEditBox::create(CCSizeMake(204,60),bg1);
    editBoxUsername->setFontSize(15);
    editBoxUsername->setPosition(ccp(size.width/2-100,size.height/2-70));
    editBoxUsername->setFontColor(ccc3(255, 255, 255));
    this->addChild(editBoxUsername,2);
    editBoxUsername->setReturnType(kKeyboardReturnTypeDone);
    CCScale9Sprite *bg2 = CCScale9Sprite::create("login_kong.png");
    editBoxPassword = CCEditBox::create(CCSizeMake(204, 60),bg2);
    editBoxPassword->setInputFlag(kEditBoxInputFlagPassword);
    
    editBoxPassword->setFontSize(15);
    
    editBoxPassword->setFontColor(ccc3(255, 255, 255));
    editBoxPassword->setPosition(ccp(size.width/2-100,size.height/2-160));
    editBoxPassword->setReturnType(kKeyboardReturnTypeDone);
    
    
    
    this->addChild(editBoxPassword,2);

   
    return true;
    
}
void LoginScene::registers(){
    registerView *re=registerView::create();
    this->addChild(re,999);
}
void LoginScene::send_LoginData(){
    
    CSJson::Value root;
    CSJson::FastWriter writer;
    root["username"]=editBoxUsername->getText();
    root["password"]=editBoxPassword->getText();
    std::string json_str= writer.write(root);
    Message * msg= socket->constructMessage(json_str.c_str(), 101);
    socket->sendMessage_(msg, true);
    this->schedule(schedule_selector(LoginScene::receive_LoginData));
}
void LoginScene::receive_LoginData(CCObject *sender){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(101);
    //sender;
    if(msg){
        this->unschedule(schedule_selector(LoginScene::receive_LoginData));
        GameData::shareGameData()->dic->removeObjectForKey(101);
        CSJson::Reader reader;
        CSJson::Value root;
        if (reader.parse(msg->data, root)) {
            CCLog("%s",msg->data);
            if (root["result"].asBool()) {
                CSJson::Value da=root["data"];
                int userId=da["userId"].asInt();
                int chaId=da["characterId"].asInt();
                GameData::shareGameData()->userID=userId;
                GameData::shareGameData()->charId=chaId;
                CSJson::FastWriter  write;
                
                CSJson::Value person1;
                
                person1["userId"]=userId;
                person1["characterId"]=chaId;
                
                
                
                std::string  json_file1=write.write(person1);
                
                Message * personMsg= socket->constructMessage(json_file1.c_str(), 103);
                CCLog("%s",json_file1.c_str());
                socket->sendMessage_(personMsg, false);
                this->schedule(schedule_selector(LoginScene::replaceScene));

            }
        }
    }
}

void LoginScene::replaceScene(){
    Message * msg= (Message *)GameData::shareGameData()->dic->objectForKey(103);
    if(msg){
        this->unschedule(schedule_selector(LoginScene::replaceScene));
        GameData::shareGameData()->dic->removeObjectForKey(103);
        CCLog("%s",msg->data);
        CSJson::Reader reader;
        CSJson::Value root;
        if (reader.parse(msg->data, root)) {
            CSJson::Value data;
            data= root["data"];
            GameData::shareGameData()->roleName=data["name"].asString();
        }
        GameData::shareGameData()->scoredata=msg->data;
        CCScene * scene= mainScene::scene();
        //  this->addChild(scene,10);
        CCDirector::sharedDirector()->replaceScene(scene);
    }
}
