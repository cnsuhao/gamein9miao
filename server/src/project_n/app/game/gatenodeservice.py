#coding:utf8
'''
Created on 2013-10-25

@author: lan (www.9miao.com)
'''
from firefly.server.globalobject import GlobalObject
from firefly.utils.services import CommandService


remoteservice = CommandService("gateremote")
GlobalObject().remote['gate']._reference.addService(remoteservice)


def remoteserviceHandle(target):
    """
    """
    remoteservice.mapTarget(target)


