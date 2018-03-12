# -*- coding: utf-8 -*-
import urllib2
import urllib
import re
import xlrd
import xlwt
from xlutils.copy import copy

class Result:
    def __init__(self):
        self.stkId = ''
        self.comp = ''
        self.num1 = 0
        self.num2 = 0
        self.num3 = 0


class IOExcl:
    def __init__(self):
        self.filename = ''
        self.list = []

    def readExcl(self,filename):
        data = xlrd.open_workbook(filename)
        sheet = data.sheets()[0]
        list = []

        for i in range(sheet.nrows):
            arr = sheet.row_values(i)
            list.append(arr[1].encode('utf-8'))
            obj = Result()
            obj.comp = arr[1].encode('utf-8')
            self.list.append(obj)

        return list

    def writeExcl(self,filename):
        rb = xlrd.open_workbook(filename)
        rs = rb.sheet_by_index(0)
        wb = copy(rb)
        ws = wb.get_sheet(0)

        for i in range(len(self.list)):
            for j in range(len(self.list[i])):
                ws.write(i+1,j+2,unicode(self.list[i][j],'utf-8'))

        wb.save(filename)


class SPiDerBaiDuNews:
    def __init__(self):
        self.list = []
        self.url1 = ''
        self.url2 = ''
        self.url3 = ''
        self.time = 0
        self.page = 1
        self.user_agent = ['Mozilla/5.0 (X11; U; Linux x86_64; zh-CN; rv:1.9.2.10) Gecko/20100922 Ubuntu/10.10 (maverick) Firefox/3.6.10',
                           'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.84 Safari/535.11 SE 2.X MetaSr 1.0 ',
                           'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; QQDownload 732; .NET4.0C; .NET4.0E) ',
                           'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/10.0.648.133 Safari/534.16',
                           'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Win64; x64; Trident/5.0)']

    def getUrl(self,comp):
        self.url1 = 'http://news.baidu.com/ns?from=news&cl=2&bt=1388505600&y0=2014&m0=1&d0=1&y1=2014&m1=12&d1=31&et=1420041599&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2014-1-1&end_date=2014-12-31&tn=newstitledy&ct=0&rn=1&q6='

        self.url2 = 'http://news.baidu.com/ns?from=news&cl=2&bt=1451577600&y0=2016&m0=1&d0=1&y1=2016&m1=12&d1=31&et=1483199999&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2016-1-1&end_date=2016-12-31&tn=newstitledy&ct=0&rn=1&q6='

        self.url3 = 'http://news.baidu.com/ns?from=news&cl=2&bt=1483200000&y0=2017&m0=1&d0=1&y1=2017&m1=12&d1=31&et=1514735999&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2017-1-1&end_date=2017-12-31&tn=newstitledy&ct=0&rn=1&q6='

    def get

