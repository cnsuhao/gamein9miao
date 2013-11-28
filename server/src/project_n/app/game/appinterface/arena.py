#coding:utf8
'''
Created on 2013-10-25
竞技场操作
@author: Administrator
'''
from app.game.core.PlayersManager import PlayersManager
from app.game.core.character.PlayerCharacter import PlayerCharacter
from app.game.core.fight import battleSide,fight

def GetJingJiInfo3700(dynamicId,characterId):
    '''获取竞技场信息
    '''
    player = PlayersManager().getPlayerByID(characterId)
    if not player or not player.CheckClient(dynamicId):
        return {'result':False,'message':u""}
    data = player.arena.getRivalInfoList()
    return {'result':True,'data':data}

def ArenaBattle_3704(dynamicId,characterId,tocharacterId):
    '''竞技场战斗
    '''
    player = PlayersManager().getPlayerByID(characterId)
    if not player or not player.CheckClient(dynamicId):
        return {'result':False,'message':""}
    toplayer = PlayerCharacter(tocharacterId)
    nbatt = battleSide.BattleSide(player)
    tbatt = battleSide.BattleSide(toplayer)
    fit = fight.Fight(nbatt, tbatt)
    fit.DoFight()
    player.arena.arenaClearing(fit.battleResult)#战后结算
    setData = {'coin':0,'exp':0,'star':fit.battlestar,'item':[],'huoli':0}
    return {'result':True,'data':{'fight':fit,'setData':setData}}
    
