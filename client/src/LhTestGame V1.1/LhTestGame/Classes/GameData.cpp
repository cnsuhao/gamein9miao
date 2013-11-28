//
//  GameData.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "GameData.h"
static GameData * game=NULL;

GameData::GameData(){
    roleDic=CCDictionary::create();
    roleDic->retain();
    dic=CCDictionary::create();
    dic->retain();
    
}
GameData::~GameData(){
    
}
GameData * GameData::shareGameData(){
    if(!game){
        game=new GameData();
    }
    return game;
}