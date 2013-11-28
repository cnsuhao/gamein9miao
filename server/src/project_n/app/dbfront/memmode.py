#-*-coding:utf8-*-
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from firefly.dbentrust.mmode import MAdmin

tbitemadmin = MAdmin('tb_item','id',fk ='characterId',incrkey='id')
tbitemadmin.insert()
tb_character_admin = MAdmin('tb_character','id',incrkey='id')
tb_character_admin.insert()
tb_matrix_amin = MAdmin('tb_character_matrix','characterId',incrkey='id')
tb_matrix_amin.insert()
tbpetadmin = MAdmin('tb_pet','id',fk ='ownerID',incrkey='id')
tbpetadmin.insert()

