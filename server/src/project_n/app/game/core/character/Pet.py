#coding:utf8
'''
Created on 2013-10-25
宠物（伙伴）类
@author: Administrator
'''
from app.share.mem.memmode import tbpetadmin
from app.game.component.attribute.AttributeComponent import AttributeComponent
from app.share.dbopear import dbSkill

MAXPOWER = 100


class Pet:
    '''宠物类'''
    
    def __init__(self,petId = 0,name = u'小伙伴',templateId = 0,owner = 0,level =1):
        '''初始化宠物的信息'''
        #角色类型
        self._pid = petId
        self.name = name
        self.templateId = templateId
        self._owner = owner#宠物的拥有者的ID
        self.skill_1 = 0#宠物的主动技能
        self.skill_2 = 0#宠物的被动技能
        self.skill_3 = 0#宠物的被动技能
        self.attribute = AttributeComponent(self)
        if self._pid:
            self.initData()
        
    def initData(self):
        '''不存在实例时的初始化方式'''
        pass
        
    def initItemInstance(self,pet_data):
        '''存在数据库实例时的初始化方式'''
        self._owner = pet_data['owner']
        self.skill_1 = pet_data['skill_1']
        self.skill_2 = pet_data['skill_2']
        self.skill_3 = pet_data['skill_3']
        
    def InsertIntoDB(self):
        '''将不存在的实例写入数据库，生成数据库中的实例'''
        characterId = self._owner
        data = {'owner':characterId,
                'name':u'',
                'templateID':self.templateId,
                'skill_1':0,
                'skill_2':0,
                'skill_3':0}
        petmmode = tbpetadmin.new(data)
        petId = int(petmmode._name.split(':')[1])
        if petId:
            self.baseInfo.setId(petId)
            return True
        return False
    
    def getActiveSkillList(self):
        """
        """
        if not self.skill_1:
            skill_list = [610101]
        else:
            skillid = dbSkill.ALL_SKILL_TEMPLATE.get(self.skill_1)['skillid']
            skill_list = [skillid]
        return skill_list
        
        
    def getFightData(self):
        '''获取怪物战斗数据'''
        attr_info = self.attribute.getAtrribute()
        fightdata = {}
        fightdata['chaId'] = self._pid          #角色的ID
        fightdata['chaName'] = self.name  #角色的昵称
        fightdata['difficulty'] = 1
        fightdata['chaLevel'] = 1#角色的等级
        fightdata['chaBattleId'] = 0                        #角色在战场中的id
        fightdata['chaCurrentHp'] = attr_info['MaxHp']#角色当前血量
        fightdata['chaCurrentPower'] = attr_info['power']#角色的当前能量
        fightdata['chaTotalHp'] = attr_info['MaxHp']#角色的最大血量s
        fightdata['chaTotalPower'] = MAXPOWER#角色的最大能量
        fightdata['physicalAttack'] = attr_info['PhyAtt']
        fightdata['physicalDefense'] = attr_info['PhyDef']
        fightdata['speed'] = attr_info['Speed']
        fightdata['hitRate'] = attr_info['HitRate']
        fightdata['critRate'] = attr_info['CriRate']
        fightdata['block'] = attr_info['Block']
        fightdata['dodgeRate'] = attr_info['Dodge']
        fightdata['ActiveSkillList'] = self.getActiveSkillList()#self.skill#角色的主动攻击技能
        fightdata['ordSkill'] = 610101#角色的普通攻击技能
        fightdata['canDoMagicSkill'] = 1#可否释放魔法技能
        fightdata['canDoPhysicalSkill'] = 1#可否释放物理技能
        fightdata['canDoOrdSkill'] = 1#可否进行普通攻击
        fightdata['canBeTreat'] = 1#可否被治疗
        fightdata['canBeAttacked'] = 1#可否被攻击
        fightdata['canDied'] = 1#是否可死亡
        fightdata['skillIDByAttack'] = 0#被攻击的技能的ID 普通攻击为 0
        return fightdata
        
    def formatInfo(self):
        '''格式化角色信息
        '''
        info = {}
        return info    
    
    