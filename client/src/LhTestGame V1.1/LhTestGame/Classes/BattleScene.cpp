//
//  BattleScene.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "BattleScene.h"
#include "GameData.h"
#include "GameOver.h"
CCScene * BattleScene::scene(){
    CCScene * m_scene=CCScene::create();
    CCLayer * m_layer= BattleScene::create();
    m_scene->addChild(m_layer);
    return m_scene;
}
bool BattleScene::init(){
    if (!CCLayer::init()) {
        
        return false;
    }
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF * label1=CCLabelTTF::create(GameData::shareGameData()->roleName.c_str(), "黑体", 40);
    label1->setPosition(ccp(size.width/2-100, size.height-70));

    CCLabelTTF * label2=CCLabelTTF::create(GameData::shareGameData()->enemName.c_str(), "黑体", 40);
    label2->setPosition(ccp(size.width/2+100, size.height-70));
    this->addChild(label1,10);
    this->addChild(label2,10);
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0010.png", "man0010.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0011.png", "man0011.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0012.png", "man0012.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0013.png", "man0013.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0014.png", "man0014.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0015.png", "man0015.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0016.png", "man0016.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0017.png", "man0017.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0018.png", "man0018.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man0019.png", "man0019.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man00110.png", "man00110.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("man00111.png", "man00111.plist", "man001.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx010.png", "tx010.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx011.png", "tx011.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx012.png", "tx012.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx013.png", "tx013.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx014.png", "tx014.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx015.png", "tx015.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx016.png", "tx016.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx017.png", "tx017.plist", "tx01.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("tx018.png", "tx018.plist", "tx01.ExportJson");
    ene_Arr=CCArray::create();
    ene_Arr->retain();
    deadArr=CCArray::create();
    deadArr->retain();
    rounds=0;
    getJsonData(GameData::shareGameData()->str.c_str());
    CCSprite * sp= CCSprite::create("battle_bg.png");
    sp->setPosition(ccp(480, 320));
    this->addChild(sp);
//    pNode=cocos2d::extension:: CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("GameScene.json");
//    this->addChild(pNode);
    return true;
}
void BattleScene::getJsonData(const char *data){
    CSJson::Reader reader;
    CSJson::Value root;
    CSJson::Value datas;
    if(reader.parse(data, root)){
        datas=root["data"];
        alluseValue=datas;
        initRole(datas);
        initAttackData(alluseValue);
    }
}
void BattleScene::initAttackData(CSJson::Value value){
    
    
    CSJson::Value stepData=alluseValue["stepData"];
    CSJson::Value eneArr;
    if(rounds==stepData.size()){
        GameOver * gover=GameOver::create();
        //gover->setData(GameData::shareGameData()->str.c_str());
        this->addChild(gover,99);
        return;
    }
    chaBattleId=stepData[rounds]["chaBattleId"].asInt();
    my_role=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    my_role->skillId=stepData[rounds]["skill"].asInt();
    my_role->chaId=stepData[rounds]["chaId"].asInt();
    eneArr=stepData[rounds]["enemyChaArr"];
    int a=0;
    
    if(eneArr.size()==1){
        eneBattleId=eneArr[a]["enemyBattleId"].asInt();
        ene_role=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
        ene_role->curHP=eneArr[a]["enemyCurrentHp"].asInt();
        ene_role->totalHp=eneArr[a]["enemyTotalHp"].asInt();
        ene_role->changeHp=eneArr[a]["enemyChangeHp"].asInt();
        runAttack();
    }else if(eneArr.size()>1){
        
        for (int i=0; i<eneArr.size(); i++) {
            eneBattleId=eneArr[i]["enemyBattleId"].asInt();
            role *ro=(role * )GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
            ro->battleId=eneBattleId;
            ro->chaId=eneArr[i]["enemyChaId"].asInt();
            ro->curHP=eneArr[i]["enemyCurrentHp"].asInt();
            ro->totalHp=eneArr[i]["enemyTotalHp"].asInt();
            ro->changeHp=eneArr[i]["enemyChangeHp"].asInt();
            ene_Arr->addObject(ro);
        }
    }
    rounds++;
}
void BattleScene::moreAttack(){
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    //my_r->getAnimation()->stop();
    char attack[50]="";
    sprintf(attack, "%sattack",my_r->resName.c_str());
    my_r->playArm(attack);
    my_r->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BattleScene::eneHurt));
}
void BattleScene::moreEneHurt(){
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
  // my_r->getAnimation()->stop();
    char attack[50]="";
    sprintf(attack, "%sstand",my_r->resName.c_str());
    my_r->playArm(attack);
    for (int i=0; i<ene_Arr->count(); i++) {
        role * ene_r=(role *)ene_Arr->objectAtIndex(i);
     //   ene_r->getAnimation()->stop();
        char attacked[50]="";
        sprintf(attacked, "%swound",ene_r->resName.c_str());
      //  ene_r->getAnimation()->stop();
        ene_r->playArm(attacked);
        
        if(i==ene_Arr->count()-1){
            ene_r->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BattleScene::moreWhetherDead));
        }
        
    }

}
void BattleScene::moreWhetherDead(){
    int deadNum[9]={0};
    int j=0;
    char attacked[50]="";
    
    for (int i=0; i<ene_Arr->count(); i++) {
        role * ene_r=(role *)ene_Arr->objectAtIndex(i);
        if (ene_r->isDead()) {
            if(i==ene_Arr->count()-1){
                ene_r->playArm(attacked);
            }
            ene_r->removeFromParent();
            deadNum[j]=i;
            j++;
            
        }else{
          //  ene_r->getAnimation()->stop();
            sprintf(attacked, "%sstand",ene_r->resName.c_str());
            if(i==ene_Arr->count()-1){
                ene_r->playArm(attacked);
            }
        }
        
    
    
    }
    for (int i=0; i<9; i++) {
        if(deadNum[i]!=0){
            
            ene_Arr->removeObjectAtIndex(deadNum[i]);
        }
    }
    
}


void BattleScene::runAttack(){
    
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    CCLog("%d",my_r->skillId);
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    if(my_r->skillId==610101){
        if (ene_r->dir==2) {
            my_r->setPosition(ccp(ene_r->getPosition().x-120, ene_r->getPosition().y));

        }else{
            my_r->setPosition(ccp(ene_r->getPosition().x+120, ene_r->getPosition().y));
        }
                my_r->setZOrder(my_r->getZOrder()+1);
       // my_r->getAnimation()->stop();
        char attack[50]="";
        sprintf(attack, "%sattack",my_r->resName.c_str());
        my_r->playArm(attack);
        my_r->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BattleScene::eneHurt));
    }else {
       // my_r->getAnimation()->stop();
        CCArmature * arm=CCArmature::create("tx01");
        arm->setTag(20000);
        arm->setPosition(ccp(480, 320));
        this->addChild(arm,10);
        arm->getAnimation()->play("tx02");
        
        char attack[50]="";
        sprintf(attack, "%sattack",my_r->resName.c_str());
        my_r->playArm(attack);
        my_r->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BattleScene::eneHurt));
        
    }
    
}

void BattleScene::eneHurt(CCArmature * arm,MovementEventType type,const char * name){
    if (type == COMPLETE)
    {
        this->removeChildByTag(20000);
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    char attacked[50]="";
    char my_setNor[50]="";
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    if(my_r->skillId==610101){
        
        //ene_r->getAnimation()->stop();
        my_r->setPosition(my_r->oldpos);
        sprintf(attacked, "%swound",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        ene_r->setBloodChange(1000.0f);

    }else {
       // ene_r->getAnimation()->stop();
        my_r->setPosition(my_r->oldpos);
        sprintf(attacked, "%swound",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        ene_r->setBloodChange(1000.0f);
    }
   // my_r->getAnimation()->stop();
    sprintf(my_setNor, "%sstand",my_r->resName.c_str());
    my_r->playArm(my_setNor);
        //getAnimation()->play(attacked);
    
    ene_r->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BattleScene::whetherDead));
    }
    
    
}
void BattleScene::whetherDead(CCArmature * arm,MovementEventType type,const char * name){
    if (type == COMPLETE)
    {
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    char attacked[50]="";
    if(ene_r->isDead()){
        //ene_r->getAnimation()->stop();
        sprintf(attacked, "%sdeath",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        
        
        GameData::shareGameData()->roleDic->removeObjectForKey(eneBattleId);
        initAttackData(alluseValue);
    }else{
       // ene_r->getAnimation()->stop();
        sprintf(attacked, "%sstand",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        initAttackData(alluseValue);
    }
    
    
    }
    
    
}


//startData
void BattleScene::initRole(CSJson::Value value){
    //setData
    CSJson::Value data=value["setData"];
    CSJson::Value startValue=value["startData"];
    CSJson::Value array;
    CCLog("%d",startValue.size());
    for (int i=0; i<startValue.size(); i++) {
        role * ro=role::create();
        ro->pos=startValue[i]["chaPos"].asInt();
        ro->dir=startValue[i]["chaDirection"].asInt();
        ro->resNum=1;
        ro->curHP=startValue[i]["chaCurrentHp"].asInt();
        ro->totalHp=startValue[i]["chaTotalHp"].asInt();
        
        std::string resName;
        if (ro->resNum==1) {
            resName="man001";
            
        }else if(ro->resNum==2){
            resName="man002";
            
        }else{
            resName="woman001";
        }
        char res[50]="";
        sprintf(res, "%sstand",resName.c_str());
        ro->resName=resName;
        ro->initArm(resName.c_str());
        ro->playArm(res);
        this->addChild(ro);
        if(ro->dir==1){
        switch (ro->pos) {
            case 1:
                ro->setPosition(ccp(50+50, 360+80));
                ro->setZOrder(1);
                break;
            case 2:
                ro->setPosition(ccp(50+50, 220+80));
                ro->setZOrder(3);
                break;
            case 3:
                ro->setPosition(ccp(50+50, 80+80));
                ro->setZOrder(5);
                break;
            case 4:
                ro->setPosition(ccp(210+50, 360+80));
                ro->setZOrder(1);
                break;
            case 5:
                ro->setPosition(ccp(210+50, 220+80));
                ro->setZOrder(3);
                break;
            case 6:
                ro->setPosition(ccp(210+50, 80+80));
                ro->setZOrder(5);
                
                break;
            case 7:
                ro->setPosition(ccp(370+50, 360+80));
                ro->setZOrder(1);
                
                break;
            case 8:
                ro->setPosition(ccp(370+50, 80+80));
                ro->setZOrder(3);
                
                break;
            case 9:
                ro->setPosition(ccp(370+50, 360+80));
                ro->setZOrder(5);
                break;
            default:
                break;
        }
        }else{
            switch (ro->pos) {
                case 1:
                    ro->setRotationY(180);
                    ro->setPosition(ccp(590+50, 360+80));
                    ro->setZOrder(1);
                    break;
                case 2:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(590+50, 220+80));
                    ro->setZOrder(3);
                    break;
                case 3:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(590+50, 80+80));
                    ro->setZOrder(5);
                    break;
                case 4:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(750+50, 360+80));
                    ro->setZOrder(1);
                    break;
                case 5:
                 ro->setRotationY(180);
                    ro->setPosition(ccp(750+50, 220+80));
                    ro->setZOrder(3);
                    break;
                case 6:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(750+50, 80+80));
                    ro->setZOrder(5);
                    break;
                case 7:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(910+50, 360+80));
                    ro->setZOrder(1);
                    break;
                case 8:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(910+50, 80+80));
                    ro->setZOrder(3);
                    break;
                case 9:
                     ro->setRotationY(180);
                    ro->setPosition(ccp(910+50, 360+80));
                    ro->setZOrder(5);
                    break;
                default:
                    break;
            }
        }
    
        ro->oldpos=ro->getPosition();
        GameData::shareGameData()->roleDic->setObject(ro, ro->pos+ro->dir*10);
        
    }
    


}
