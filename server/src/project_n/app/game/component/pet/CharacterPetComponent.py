#coding:utf8
'''
Created on 2013-10-25
角色的宠物信息
@author: lan (www.9miao.com)
'''
from app.game.component.Component import Component
from app.game.core.character.Pet import Pet
from app.share.mem.memmode import tbpetadmin 

class CharacterPetComponent(Component):
    '''角色的宠物信息类'''
    
    def __init__(self,owner):
        '''init Object'''
        Component.__init__(self, owner)
        #角色的宠物列表
        self._pets = {}
        self.initCharacterPetInfo()
        
    def initCharacterPetInfo(self):
        '''初始化角色宠物信息'''
        pid = self._owner.cid
        petlist = tbpetadmin.getAllPkByFk(pid)
        petobjlist = tbpetadmin.getObjList(petlist)
        for petmmode in petobjlist:
            petId = int(petmmode._name.split(':')[1])
            pet = Pet(petId)
            petinfo = petmmode.get('data')
            pet.initItemInstance(petinfo)
            self._pets[petId] = pet
        
    def getPets(self):
        '''获取角色的宠物列表'''
        return self._pets
    
    def getPet(self,pet_id):
        """获取伙伴实例
        """
        return self._pets.get(pet_id)
        
    def IsInMatrix(self,petId):
        '''判断宠物是否在阵法中
        '''
        return self._owner.matrix.IsInMatrix(petId)
    
    def getCharacterPetListInfo(self):
        '''获取角色宠物列表'''
        pets = self.getPets()
        PetListInfo = {}
        PetListInfo['curPetNum'] = len(pets)
        PetListInfo['maxPetNum'] = 20
        PetListInfo['petInfo'] = []
        for pet in pets.values():
            info = {}
            petId = pet.baseInfo.getId()
            info['petId'] = pet._pid
            info['resPetId'] = 0
            info['icon'] = 0
            info['petName'] = pet.name
            info['petLevel'] = 1
            info['sz'] = self.IsInMatrix(petId)
            info['pinzhi'] = 1
            PetListInfo['petInfo'].append(info)
        return PetListInfo
        
        