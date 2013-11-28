#coding:utf8
'''
Created on 2013-10-25

@author: sean_lan
'''



from app.share.mem.memmode import tb_character_admin
from app.game.component.pet.CharacterPetComponent import CharacterPetComponent
from app.game.component.matrix.CharacterMatrixComponent import CharacterMatrixComponent
from app.game.component.arena.CharacterArenaComponent import CharacterArenaComponent
from twisted.python import log

class PlayerCharacter:
    '''玩家角色类'''
    def __init__(self , cid ,dynamicId = -1):
        '''构造方法
        @dynamicId （int） 角色登陆的动态ID socket连接产生的id
        '''
        self.cid = cid
        self.nickname = ""
        self.score = 0
        self.coin = 0
        self.dynamicId = dynamicId    #角色登陆服务器时的动态id
        #--------角色的各个组件类------------
        self.pet = CharacterPetComponent(self)#角色的伙伴组件
        self.matrix = CharacterMatrixComponent(self)#角色的阵法设置信息
        self.arena = CharacterArenaComponent(self)#角色竞技场信息
        self.initPlayerInfo() #初始化角色
        
    def initPlayerInfo(self):
        '''初始化角色信息'''
        pid = self.cid
        pmmode = tb_character_admin.getObj(pid)
        data = pmmode.get("data")
        if not data:
            log.err( "Inint_player _"+str(self.baseInfo.id))
        self.nickname = data['nickname'] #角色昵称
        self.score = data['score'] #角色积分
        self.coin = data['coin'] #角色的金币
            
    def getDynamicId(self):
        '''获取角色的动态Id'''
        return self.dynamicId
    
    def formatInfo(self):
        '''格式化角色基本信息'''
        characterInfo = {}
        characterInfo['id'] = self.cid#角色的ID
        characterInfo['nickname'] = self.nickname#角色的昵称
        characterInfo['score'] = 0
        return characterInfo
         
    def CheckClient(self,dynamicId):
        '''检测客户端id是否匹配'''
        if self.dynamicId ==dynamicId:
            return True
        return False
        
    def updatePlayerDBInfo(self):
        '''更新角色在数据库中的数据'''
        pass
        pid = self.cid
        pmmode = tb_character_admin.getObj(pid)
        mapping = {'score':self.score,"coin":self.coin}
        pmmode.update_multi(mapping)
        
        
