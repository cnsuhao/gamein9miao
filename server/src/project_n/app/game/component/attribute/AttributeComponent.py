#coding:utf8
'''
Created on 2013-10-25
宠物(伙伴)的属性
@author: Administrator
'''
from app.share.dbopear import dbSkill
from app.game.component.Component import Component
from app.game.util import addDict

INIT_HP = 150#初始的血量
INIT_PHYATT = 30#初始的物理攻击


class AttributeComponent(Component):
    '''宠物属性相关
    '''
    
    def __init__(self,owner):
        '''
        Constructor
        @param hp: int 宠物的当前血量
        @param StrGrowth: int 宠物的力量成长
        @param WisGrowth: int 宠物的智力成长
        @param VitGrowth: int 宠物的耐力（体力）成长
        @param DexGrowth: int 宠物的敏捷成长
        '''
        Component.__init__(self, owner)
        self.hp = INIT_HP
        self.PhyAtt = INIT_PHYATT
        
    def getSkillAttr(self):
        """获取技能的属性加成
        """
        skill_list = [self._owner.skill_1,self._owner.skill_2,self._owner.skill_3]
        attr_info = {}
        for _skill_id in skill_list:
            skill_info = dbSkill.ALL_SKILL_TEMPLATE.get(_skill_id)
            if not skill_info:
                continue
            else:
                _info = eval(skill_info.get("effect",{}))
            attr_info = addDict(attr_info,_info)
        return attr_info
                
        
    def getAtrribute(self):
        '''获取宠物的属性
        '''
        skill_attr = self.getSkillAttr()
        info = {}
        info['hp'] = self.hp#当前血量
        info['MaxHp'] = self.hp#最大血量
        info['PhyAtt'] = self.PhyAtt#物攻
        info['PhyDef'] = 0#物防
        info['Speed'] = 0
        info['HitRate'] = 100
        info['Dodge'] = 0
        info['CriRate'] = 0
        info['power'] = 0
        info['Block'] = 0
        
        return addDict(skill_attr,info)
        
        
    
    