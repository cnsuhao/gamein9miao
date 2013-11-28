#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from app.share.dbopear import dbSkill
from app.share.mem import memmode
from firefly.dbentrust.madminanager import MAdminManager

def load_config_data():
    """从数据库中读取配置信息
    """
    dbSkill.getALLSkillTemplate()
    dbSkill.getAllSkill()
    dbSkill.getBuffAddition()
    dbSkill.getBuffOffsetInfo()
    dbSkill.getAllBuffInfo()

    
def registe_madmin():
    """注册数据库与memcached对应
    """
    MAdminManager().registe(memmode.tbpetadmin)
    MAdminManager().registe( memmode.tb_character_admin)
    MAdminManager().registe(memmode.tb_matrix_amin)
    MAdminManager().registe(memmode.tbcharacter_skill)
    
    
    
    
    