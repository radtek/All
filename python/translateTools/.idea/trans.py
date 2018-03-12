#coding=utf8
 
import httplib
import md5
import urllib
import random
import json
import sys
import hashlib
import re

appid = '20180309000133299'   #需要自己申请 need to apply in http://api.fanyi.baidu.com/api/trans/product/desktop
secretKey = 'xxxxxxxxxxxxxxx' #需要自己申请 need to apply in http://api.fanyi.baidu.com/api/trans/product/desktop
salt = random.randint(32768, 65536)
tt = str(salt)

def fun(q):
    httpClient = None
    fromLang = 'auto'
    toLang = 'auto'
    myurl = '/api/trans/vip/translate'

    sign = appid+q+tt+secretKey
    #m1 = hashlib.md5()
    m1 = md5.new()
    m1.update(sign)
    sign = m1.hexdigest()
    myurl = myurl+'?appid='+appid+'&q='+urllib.quote(q)+'&from='+fromLang+'&to='+toLang+'&salt='+tt+'&sign='+sign

    try:
        httpClient = httplib.HTTPConnection('api.fanyi.baidu.com')
        httpClient.request('GET', myurl)

        #response是HTTPResponse对象
        response = httpClient.getresponse()
        str = response.read()
        data = json.loads(str)
        print data['trans_result'][0]['dst']

    except Exception, e:
        print e
    finally:
        if httpClient:
            httpClient.close()

q = 'apple'

list_1 = []


if len(sys.argv) == 1:
    z = '聂平真帅'
    fun(z)
else:
    list_1 = sys.argv[1:]
    for i in list_1:
        z = ''
        print u'嘟噜噜:',
        print i
        z = i.decode('gbk').encode('utf-8')
        fun(z)


