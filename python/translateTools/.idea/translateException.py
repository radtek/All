# coding=utf8

import httplib
import md5
import urllib
import random
import json
import sys
import hashlib
import re
import csv
import time

appid = '20180309000133299'  # 需要自己申请 need to apply in http://api.fanyi.baidu.com/api/trans/product/desktop
secretKey = 'VDZlUclYn255xwCSi7X2'  # 需要自己申请 need to apply in http://api.fanyi.baidu.com/api/trans/product/desktop
salt = random.randint(32768, 65536)
tt = str(salt)


def fun(q):
    httpClient = None
    fromLang = 'zh' #auto
    toLang = 'en'
    myurl = '/api/trans/vip/translate'

    sign = appid + q + tt + secretKey
    # m1 = hashlib.md5()
    m1 = md5.new()
    m1.update(sign)
    sign = m1.hexdigest()
    myurl = myurl + '?appid=' + appid + '&q=' + urllib.quote(
        q) + '&from=' + fromLang + '&to=' + toLang + '&salt=' + tt + '&sign=' + sign

    try:
        httpClient = httplib.HTTPConnection('api.fanyi.baidu.com')
        httpClient.request('GET', myurl)

        # response是HTTPResponse对象
        response = httpClient.getresponse()
        str = response.read()
        data = json.loads(str)
        print data['trans_result'][0]['dst']
        return data['trans_result'][0]['dst']

    except Exception, e:
        print e
    finally:
        if httpClient:
            httpClient.close()


strtime = time.strftime('%Y-%m-%d',time.localtime(time.time()))

if strtime != '2018-05-15':
		print r'已过期'.decode('utf-8').encode('gbk')
		exit() 

target = []
csv_file  = csv.reader(open('jstp.csv','r'))
for row in csv_file:
    target.append(row[1])


#out = open('output.csv','a')
#csv_write = csv.writer(out,dialect='excel')

writeresult=file(r'translateresult.txt','a+')  


for i in target:
		str_trans = fun(i.decode('gbk').encode('utf-8'))
		writeresult.write(str_trans+'\n')
   
writeresult.close()  

