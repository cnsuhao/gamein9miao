#coding:utf8
'''
Created on 2013-10-25

@author: sean_lan
'''
from firefly.dbentrust.dbpool import dbpool
from MySQLdb.cursors import DictCursor
import datetime


def getUserInfo(uid):
    '''获取用户角色关系表所有信息
    @param id: int 用户的id
    '''
    sql = "select * from tb_user_character where id = %d"%(uid)
    conn = dbpool.connection()
    cursor = conn.cursor(cursorclass=DictCursor)
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    return result

def checkUserPassword(username,password):
    '''检测用户名户密码
    @param username: str 用户的用户名
    @param password: str 用户密码
    '''
    sql = "select id from `tb_register` where username = '%s' and password = '%s'" %( username, password)
    conn = dbpool.connection()
    cursor = conn.cursor()
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    pid = 0
    if result:
        pid = result[0]
    return pid

def getUserInfoByUsername(username,password):
    '''检测用户名户密码
    @param username: str 用户的用户名
    @param password: str 用户密码
    '''
    sql = "select * from `tb_register` where username = '%s'\
     and password = '%s'" %( username, password)
    conn = dbpool.connection()
    cursor = conn.cursor(cursorclass=DictCursor)
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    return result

    
def InsertUserCharacter(userId,characterId):
    '''加入角色用户关系'''
    sql = "update tb_register set characterId = %d where `id` = %d"%( characterId ,userId)
    conn = dbpool.connection()
    cursor = conn.cursor()
    count = cursor.execute(sql)
    conn.commit()
    cursor.close()
    conn.close()
    if count >= 1:
        return True
    else:
        return False

def checkCharacterName(nickname):
    '''检测角色名是否可用
    @param nickname: str 角色的名称
    '''
    sql = "SELECT `id` from tb_character where nickname = '%s'"%nickname
    conn = dbpool.connection()
    cursor = conn.cursor()
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    if result:
        return False
    return True

def creatNewCharacter(nickname ,userId):
    '''创建新的角色
    @param nickname: str 角色的昵称
    @param profession: int 角色的职业编号
    @param userId: int 用户的id
    @param fieldname: str 用户角色关系表中的字段名，表示用户的第几个角色
    '''
    nowdatetime = str(datetime.datetime.today())
    sql = "insert into `tb_character`(nickName,createtime) \
    values('%s','%s')"%(nickname,nowdatetime)
    sql2 = "SELECT @@IDENTITY"
    conn = dbpool.connection()
    cursor = conn.cursor()
    count = cursor.execute(sql)
    conn.commit()
    cursor.execute(sql2)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    if result and count:
        characterId = result[0]
        InsertUserCharacter(userId,characterId)
        createCharacterPets(characterId)
        createInfoMatix(characterId)
        return characterId
    else:
        return 0
    
    
def getUserCharacterInfo(characterId):
    '''获取用户角色列表的所需信息
    @param id: int 用户的id
    '''
    sql = "select town from tb_character where id = %d"%(characterId)
    conn = dbpool.connection()
    cursor = conn.cursor(cursorclass=DictCursor)
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    return result

def CheckUserInfo(Uid):
    '''检测用户信息'''
    sql = "SELECT * from tb_register where username = '%s'"%Uid
    conn = dbpool.connection()
    cursor = conn.cursor(cursorclass=DictCursor)
    cursor.execute(sql)
    result = cursor.fetchone()
    cursor.close()
    conn.close()
    return result

def creatUserInfo(username,password):
    '''创建
    '''
    sql = "insert into tb_register(username,`password`) values ('%s','%s')"%(username,password)
    conn = dbpool.connection()
    cursor = conn.cursor()
    count = cursor.execute(sql)
    conn.commit()
    cursor.close()
    conn.close()
    if(count >= 1):
        return True
    return False

def createCharacterPets(character_id):
    """初始化创建的角色的小伙伴们
    """
    sql = "INSERT INTO `tb_pet`(`owner`) VALUES (%d),(%d),(%d);"%(character_id,
                                                    character_id,character_id)
    conn = dbpool.connection()
    cursor = conn.cursor()
    count = cursor.execute(sql)
    conn.commit()
    cursor.close()
    conn.close()
    if(count >= 1):
        return True
    return False

def getCharacterPetList(character_id):
    """获取角色的宠物列表
    """
    sql = "SELECT `id` FROM  `tb_pet` WHERE `owner` = %d;"%character_id
    conn = dbpool.connection()
    cursor = conn.cursor()
    cursor.execute(sql)
    result = cursor.fetchall()
    cursor.close()
    conn.close()
    return [_pinfo[0] for _pinfo in result]

def createInfoMatix(character_id):
    """初始化创建的角色的阵法
    """
    petlist = getCharacterPetList(character_id)
    sql = "INSERT INTO `tb_character_matrix`(`characterId`,`eyes_4`,`eyes_5`,`eyes_6`) \
     VALUES(%d,%d,%d,%d);"%(character_id,petlist[0],petlist[1],petlist[2])
    conn = dbpool.connection()
    cursor = conn.cursor()
    count = cursor.execute(sql)
    conn.commit()
    cursor.close()
    conn.close()
    if(count >= 1):
        return True
    return False
    
def getAllCharacterIdList():
    """获取所有角色的id列表
    """
    sql = "SELECT `id` FROM  `tb_character`;"
    conn = dbpool.connection()
    cursor = conn.cursor()
    cursor.execute(sql)
    result = cursor.fetchall()
    cursor.close()
    conn.close()
    return [_cinfo[0] for _cinfo in result]




