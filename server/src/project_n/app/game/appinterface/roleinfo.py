#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from app.game.core.PlayersManager import PlayersManager

def roleInfo(dynamicId,characterId):
    '''获取角色的状态栏信息
    @param userId: int 用户id
    @param characterId: 角色的id 
    '''
    player = PlayersManager().getPlayerBydynamicId(dynamicId)
    if dynamicId != player.getDynamicId():
        return {'result':False,'message':""}
    playerinfo = player.formatInfo()
    responsedata = {'result':True,'message':'',
                    'data':{'characterId':playerinfo['id'],
                            'rolename':playerinfo['nickname'],
                            'score':player.score}}
    return responsedata

