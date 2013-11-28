#coding:utf8
'''
Created on 2012-7-1
角色的竞技场信息
@author: Administrator
'''
from app.game.component.Component import Component
from firefly.dbentrust.memclient import mclient
from app.share.mem.mcharacter import Mcharacter
from app.share.dbopear import dbuser

MEM_CNT = 10 #最多对手

class CharacterArenaComponent(Component):
    '''角色竞技场信息    
    @param score: int 竞技场积分
    '''
    CD = 600
    
    def __init__(self,owner):
        '''初始化
        '''
        Component.__init__(self, owner)
    
    def getRivalList(self):
        '''获取对手列表
        '''
        all_character_list = dbuser.getAllCharacterIdList()
        all_character_info_list = [Mcharacter(_cid,'character%d'%_cid,mclient).mcharacterinfo for \
                                    _cid in all_character_list]
        all_character_info_list = sorted(all_character_info_list,reverse=True,\
                            key = lambda d:d['score'])
        rival_list = []
        if len(all_character_info_list)<=MEM_CNT:
            for rival in all_character_info_list:
                info = rival
                info['ranking']= all_character_info_list.index(rival)
                rival_list.append(info)
        else:
            for i in range(3):
                info = all_character_info_list[i]
                info['ranking']= i+1
                rival_list.append(info)
            index =1
            for rival in all_character_info_list:
                if self._owner.cid == rival['id']:
                    index = all_character_info_list.index(rival)+1
                    continue
            if index<=MEM_CNT:
                for i in range(3,MEM_CNT):
                    info = all_character_info_list[i]
                    info['ranking']= i+1
                    rival_list.append(info)
            else:
                for i in range(index-(MEM_CNT-3),index):
                    info = all_character_info_list[i]
                    info['ranking']= i+1
                    rival_list.append(info)

        return rival_list
        
        
    def getRivalInfoList(self):
        """获取竞技场中的前3名和排名最近的对手信息
        """
        return {"result":True,"data":self.getRivalList()}
    
    def arenaClearing(self,battle_result):
        """战斗结束
        """
        if battle_result==1:
            self._owner.coin+=10
            self._owner.score+=10
        else:
            self._owner.coin+=10
            self._owner.score+=10
        characterId = self._owner.cid
        mcha = Mcharacter(characterId,'character%d'%characterId,mclient)
        mcha.update("score", self._owner.score)
        
        
        
        
    
