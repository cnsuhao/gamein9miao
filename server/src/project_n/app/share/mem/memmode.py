#-*-coding:utf8-*-
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from firefly.dbentrust.mmode import MAdmin

tb_character_admin = MAdmin('tb_character','id',incrkey='id')
tb_character_admin.insert()
tb_matrix_amin = MAdmin('tb_character_matrix','characterId',incrkey='id')
tb_matrix_amin.insert()
tbpetadmin = MAdmin('tb_pet','id',fk ='owner',incrkey='id')
tbpetadmin.insert()
tbcharacter_skill = MAdmin('tb_character_skill','id',fk ='character_id',incrkey='id')
tbcharacter_skill.insert()

