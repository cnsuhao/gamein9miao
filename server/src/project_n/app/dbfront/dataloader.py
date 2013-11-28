#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from app.share.mem import  memmode
from firefly.dbentrust.madminanager import MAdminManager
from app.share.mem.McharacterManager import McharacterManager
from twisted.internet import reactor
reactor = reactor

def initData():
    """载入角色初始数据
    """
    McharacterManager().initData()
    
def registe_madmin():
    """注册数据库与memcached对应
    """
    MAdminManager().registe(memmode.tbpetadmin)
    MAdminManager().registe( memmode.tb_character_admin)
    MAdminManager().registe(memmode.tb_matrix_amin)
    MAdminManager().registe(memmode.tbcharacter_skill)
    
def CheckMemDB(delta):
    """同步内存数据到数据库
    """
    MAdminManager().checkAdmins()
    reactor.callLater(delta,CheckMemDB,delta)
    

    
    
    
    