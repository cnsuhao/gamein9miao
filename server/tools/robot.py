#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from socket import AF_INET,SOCK_STREAM,socket
import random
import time,struct,json

HOST='localhost'
PORT=11009
BUFSIZE=1024
ADDR=(HOST , PORT)

def produceData(sendstr,commandId):
    """78,37,38,48,9,0"""
    HEAD_0 = chr(78)
    HEAD_1 = chr(37)
    HEAD_2 = chr(38)
    HEAD_3 = chr(48)
    ProtoVersion = chr(9)
    ServerVersion = 0
    sendstr = sendstr
    data = struct.pack('!sssss3I',HEAD_0,HEAD_1,HEAD_2,\
                       HEAD_3,ProtoVersion,ServerVersion,\
                       len(sendstr)+4,commandId)
    senddata = data+sendstr
    return senddata

class Roboter:
    
    def __init__(self,username,password):
        """
        """
        self.username = username
        self.password = password
        self.client = socket(AF_INET,SOCK_STREAM)
        self.userId = 0
        self.characterId = 0
        self.load()
        
    def load(self):
        """
        """
        info = {'id':1915,'characterId':1000060}
        self.userId = info.get('id')
        self.characterId = info.get('characterId')
        
    def connect(self):
        """建立连接
        """
        self.client.connect(ADDR)
        
    def login(self):
        """登陆
        """
        self.client.sendall(produceData(json.dumps({"username":self.username,
                                                    "password":self.password}),101))
        
    def rolelogin(self):
        """进入游戏
        """
        self.client.sendall(produceData(json.dumps({"userId":self.userId,
                                                    "characterId":self.characterId}),103))
    
    def fight(self):
        """战斗
        """
        self.client.sendall(produceData(json.dumps({"tid":1000060,
                                                    "characterId":self.characterId}),3704))
        
    def getPackage(self):
        """获取包裹信息
        """
        self.client.sendall(produceData(json.dumps({"characterId":self.characterId}),203))
        
    def action(self):
        """机器人行动
        """
        rate = random.choice([1])
        if rate==1:
            self.fight()
        else:
            self.fight()
            
    def _run(self):
        self.connect()
        self.login()
        self.rolelogin()
        while True:
            self.action()
            
            
rob = Roboter("test555","111111")
rob.connect()
rob.login()
rob.rolelogin()
rob.fight()

