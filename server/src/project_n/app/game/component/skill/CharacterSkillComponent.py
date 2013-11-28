#coding:utf8
'''
Created on 2013-10-25
角色的所学的技能信息
@author: lan (www.9miao.com)
'''
from app.game.component.Component import Component
from app.share.mem.memmode import tbcharacter_skill

class CharacterPetComponent(Component):
    '''角色的所学的技能信息'''
    
    def __init__(self,owner):
        '''init Object'''
        Component.__init__(self, owner)
        #角色的宠物列表
        self._skills = []
        
    def initCharacterSkillInfo(self):
        '''初始化角色所学技能信息'''
        pid = self._owner.cid
        skilllist = tbcharacter_skill.getAllPkByFk(pid)
        petobjlist = tbcharacter_skill.getObjList(skilllist)
        for petmmode in petobjlist:
            skillinfo = petmmode.get('data')
            self._skills.append(skillinfo['skillId'])
        
    def getSkills(self):
        '''获取角色的宠物列表'''
        return self._skills
        
        
        