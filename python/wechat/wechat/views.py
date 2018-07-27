# -*- coding: utf-8 -*-
import hashlib
import json
from django.utils.encoding import smart_str
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse

#@csrf_exempt
def weixin_main(request):
    if request.method == "GET":
        signature = request.GET.get('signature', None)
        timestamp = request.GET.get('timestamp', None)
        nonce = request.GET.get('nonce', None)
        echostr = request.GET.get('echostr', None)

        token = 'test'

        hashlist = [token, timestamp, nonce]
        hashlist.sort()
        hashstr = ''.join([s for s in hashlist])
        hashstr = hashlib.sha1(hashstr).hexdigets()

        if hashstr == signature:
            return HttpResponse(echostr)
        else:
            return HttpResponse("field")
    else:
        othercontent = auto_reply(request)
        return HttpResponse(othercontent)


import time
class TextMsg:
    def __init__(self, toUserName, fromUserName, content, img=''):
        self.__dict = dict()
        self.__dict['ToUserName'] = toUserName
        self.__dict['FromUserName'] = fromUserName
        self.__dict['CreateTime'] = int(time.time())
        self.__dict['Content'] = content
        self.__dict['image'] = img

    def send_text(self):
        XmlForm = """
        <xml>
        <ToUserName><![CDATA[{ToUserName}]]></ToUserName>
        <FromUserName><![CDATA[{FromUserName}]]></FromUserName>
        <CreateTime>{CreateTime}</CreateTime>
        <MsgType><![CDATA[text]]></MsgType>
        <Content><![CDATA[{Content}]]></Content>
        </xml>
        """
        return XmlForm.format(**self.__dict)

    def send_img(self):
        xmlForm = """
        <xml>
        <ToUserName>< ![CDATA[ToUserName] ]></ToUserName>
        <FromUserName>< ![CDATA[FromUserName] ]></FromUserName>
        <CreateTime>{CreateTime}</CreateTime>
        <MsgType>< ![CDATA[image] ]></MsgType>
        <Image><MediaId>< ![CDATA[media_id] ]></MediaId></Image>
        </xml>
        """
        return xmlForm.format(**self.__dict)


import xml.etree.ElementTree as ET
def auto_reply(request):
    try:
        webData = request.body
        xmlData = ET.fromstring(webData)

        msgType = xmlData.find('MsgType').text
        ToUserName = xmlData.find('ToUserName').text
        FromUserName = xmlData.find('FromUserName').text
        CreateTime = xmlData.find('CreateTime').text
        MsgType = xmlData.find('MsgType').text
        MsgId = xmlData.find('MsgId').text

        if msgType == 'text':
            content = "您好，自动回复功能开发中，敬请期待"
            replyMsg = TextMsg(ToUserName, FromUserName, content)
            return replyMsg.send_text()

        elif msgType == 'image':
            content = "图片已收到,谢谢"
            replyMsg = TextMsg(ToUserName, FromUserName, content)
            return replyMsg.send()

        else:
            content = "暂不支持"
            replyMsg = TextMsg(ToUserName, FromUserName, content)
            return replyMsg.send_text()

    except Exception, Argment:
        return Argment






