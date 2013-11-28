#coding:utf8
'''
Created on 2013-10-25
角色的阵法设置信息
@author: lan (www.9miao.com)
'''

from app.game.component.Component import Component
from app.share.mem.memmode import tb_matrix_amin

class CharacterMatrixComponent(Component):
    '''角色邮件列表组件'''
    
    def __init__(self,owner):
        '''初始化
        '''
        Component.__init__(self, owner)
        #已设置的阵法相关的信息
        self._matrixSetting = {}
        self.initMatrixInfo()
        
    def initMatrixInfo(self):
        '''初始化阵法设置信息'''
        characterId = self._owner.cid
        matrixMmode = tb_matrix_amin.getObj(characterId)
        if not matrixMmode:
            characterId = self._owner.cid
            self._matrixSetting = {'eyes_1':-1,
                                   'eyes_2':-1,'eyes_3':-1,'eyes_4':-1,'eyes_5':0,
                                   'eyes_6':-1,'eyes_7':-1,'eyes_8':-1,'eyes_9':-1,
                                   'characterId':characterId,'matrixId':0}
            tb_matrix_amin.new(self._matrixSetting)
        else:
            self._matrixSetting = matrixMmode.get("data")
        
    def getMatrixMaxEyesCnt(self):
        '''获取阵法最大阵眼数
        '''
        return 9
    
    def checkMatrixSetting(self,setting):
        '''检测阵法设置
        '''
        if not setting:
            return False
        if not set([pos['pos'] for pos in setting]).issubset(set(range(1,10))):
            return False#针眼位置不正确的情况
        characterId = self._owner.baseInfo.id
        memlist = [minfo['roleid'] for minfo in setting]
        if len(set(memlist))<len(memlist):#有重复上阵的情况
            return False
        memlist.remove(characterId)
        if not set(memlist).issubset(self._owner.pet._pets.keys()):
            return False
        return True
        
    def updateMatrix(self,setting):
        '''更新阵法位置信息
        @param setting: 设置结果
        '''
        characterId = self._owner.baseInfo.id
        newsetting = {'eyes_1':-1,'eyes_2':-1,'eyes_3':-1,'eyes_4':-1,'eyes_5':-1,
                                   'eyes_6':-1,'eyes_7':-1,'eyes_8':-1,'eyes_9':-1}
        if not self.checkMatrixSetting(setting):
            return {'result':False,'message':u'不合法的阵法设置'}
        for minfo in setting:
            pos = minfo['pos']
            roleid = minfo['roleid']
            newsetting['eyes_%d'%pos] = 0 if roleid==characterId else roleid
        self._matrixSetting = newsetting
        return {'result':True,'message':u''}
    
    def FormatMatrixInfo(self):
        '''格式化角色的阵法设置信息
        '''
        matrix = []
        for index in range(1,10):
            info = {}
            info['pos'] = index
            petId = self._matrixSetting.get('eyes_%d'%index)
            if not petId:
                continue
            else:
                info['chatype'] = 3
                info['chaid'] = petId
                pet  = self._owner.pet.getPets().get(petId)
                info['tempid'] = pet.templateId
            matrix.append(info)
        return {'matrix':matrix}
        
    def WriteMatrixInDB(self):
        self.cleanMatrixSetting()
        characterId = self._owner.cid
        newsetting = self._matrixSetting
        matrixMmode = tb_matrix_amin.getObj(characterId)
        matrixMmode.update_multi(newsetting)
        
    def IsInMatrix(self,petId):
        '''判断宠物是否在阵法中
        '''
        if petId in self._matrixSetting.values():
            return True
        return False
        
        