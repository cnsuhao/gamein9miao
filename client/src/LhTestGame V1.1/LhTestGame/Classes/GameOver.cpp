//
//  GameOver.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-25.
//
//

#include "GameOver.h"
#include "mainScene.h"
bool GameOver::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))){
        return false;
    }
    setTouchEnabled(true);
   
    
   CCSize size= CCDirector::sharedDirector()->getWinSize();
    label1=CCLabelTTF::create("+10", "黑体", 35);
    label1->setPosition(ccp(size.width/2, size.height/2-25));
    this->addChild(label1,2);
    CCSprite *bg= CCSprite::create("over_bg.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg,0);
    CCMenuItemImage * item=CCMenuItemImage::create("back_up.png", "back_down.png", this, menu_selector(GameOver::goback));
    item->setPosition(ccp(0, -200));
    menu=CCMenu::create(item,NULL);
    this->addChild(menu,1);
    
    return true;
    
}
void GameOver::goback(){
    CCScene * scene=mainScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}
void GameOver::setData(const char *data){
    CCLog("%s",data);
    CSJson::Reader reader;
    CSJson::Value root;
    if(reader.parse(data, root)){
        CSJson::Value sData;
        sData=root["data"];
        CCLog("%d",sData["battleResult"].asInt());
        CSJson::Value setData;
        setData=sData["setData"];
        int star=setData["star"].asInt();
        char starnum[10]="";
        sprintf(starnum, "星级为：%d",star);
        //label1->setString(starnum);
    }
}
void  GameOver::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-99900, true);
    CCLayer::registerWithTouchDispatcher();
}
bool GameOver::ccTouchBegan(CCTouch* touch, CCEvent* event){
    menuflag=menu->ccTouchBegan(touch, event);
    return true;
}
void GameOver::ccTouchMoved(CCTouch* touch, CCEvent* event){
    if(menuflag){
        menu->ccTouchMoved(touch
                           , event);
    }
}
void GameOver::ccTouchEnded(CCTouch* touch, CCEvent* event){
    if(menuflag){
        menu->ccTouchEnded(touch, event);
        menuflag=false;
    }
}

