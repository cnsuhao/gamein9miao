#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''

PLAYER_PLAYER =1
PLAYER_PET = 2
MONSTER_MONSTER =1
MATRIXLIST = [100001,100002,100003,100004,100005,100006,100007,100008,100009]

class BattleSide(object):
    '''战斗方类'''
    
    def __init__(self,character):
        '''初始化战斗方
        '''
        self.members = []
        self.matrixSetting = {}
        for eyeNo in range(1,10):
            memID = character.matrix._matrixSetting.get('eyes_%d'%eyeNo)
            if memID==0:
                continue
            else:
                pet = character.pet.getPet(memID)
                self.members.append(pet)
                self.matrixSetting[memID] = eyeNo
    
        
    def getCharacterEyeNo(self,characterId):
        '''获取角色在阵法中的位置'''
        eyeNo = self.matrixSetting.get(characterId)
        return eyeNo
    
    def getMembers(self):
        '''获取战斗方成员信息'''
        fighters = []
        for member in self.members:
            data = member.getFightData()
            fighters.append(data)
        return fighters
    
        
        