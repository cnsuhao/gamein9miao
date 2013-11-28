#coding:utf8
'''
Created on 2013-8-14

@author: lan (www.9miao.com)
'''
from firefly.dbentrust.dbpool import dbpool
from MySQLdb.cursors import DictCursor
    
def getALlCharacterBaseInfo():
    """获取所有的角色的基础信息
    """
    sql = "SELECT `id`,`nickname`,`score` FROM tb_character;";
    conn = dbpool.connection()
    cursor = conn.cursor(cursorclass=DictCursor)
    cursor.execute(sql)
    result=cursor.fetchall()
    cursor.close()
    conn.close()
    return result


    
    