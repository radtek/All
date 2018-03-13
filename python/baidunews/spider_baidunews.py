# -*- coding: utf-8 -*-
import urllib2
import urllib
import re
import xlrd
import xlwt
from xlutils.copy import copy
import threading
import random

class Result:
    def __init__(self):
        self.stkId = ''
        self.comp = ''
        self.num = []


class IOExcl:
    def __init__(self):
        self.filename = ''
        self.list = []

    def readExcl(self,filename):
        data = xlrd.open_workbook(filename)
        sheet = data.sheets()[0]
        list = []

        for i in range(sheet.nrows):
            if i == 0:
                continue
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
            for j in range(len(self.list[i].num)):
                ws.write(i+1,j+2,unicode(str(self.list[i].num[j]),'utf-8'))

        wb.save(filename)


class SPiDerBaiDuNews:
    def __init__(self):
        self.excl = IOExcl()
        self.list = []
        self.url_list = []
        self.user_agent = ['Mozilla/5.0 (X11; U; Linux x86_64; zh-CN; rv:1.9.2.10) Gecko/20100922 Ubuntu/10.10 (maverick) Firefox/3.6.10',
                           'Mozilla/5.0 (Windows NT 5.1) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.84 Safari/535.11 SE 2.X MetaSr 1.0 ',
                           'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; QQDownload 732; .NET4.0C; .NET4.0E) ',
                           'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/10.0.648.133 Safari/534.16',
                           'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Win64; x64; Trident/5.0)']
        self.index = 0
        self.threadLock = threading.Lock()

    def getUrl(self,comp):
        self.url_list = []
        url = 'http://news.baidu.com/ns?from=news&cl=2&bt=1388505600&y0=2014&m0=1&d0=1&y1=2014&m1=12&d1=31&et=1420041599&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2014-1-1&end_date=2014-12-31&tn=newstitledy&ct=0&rn=1&q6='
        self.url_list.append(url)
        url = 'http://news.baidu.com/ns?from=news&cl=2&bt=1451577600&y0=2016&m0=1&d0=1&y1=2016&m1=12&d1=31&et=1483199999&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2016-1-1&end_date=2016-12-31&tn=newstitledy&ct=0&rn=1&q6='
        self.url_list.append(url)
        url = 'http://news.baidu.com/ns?from=news&cl=2&bt=1483200000&y0=2017&m0=1&d0=1&y1=2017&m1=12&d1=31&et=1514735999&q1='\
                    +comp+'&submit=百度一下&q3=&q4=&mt=0&lm=&s=2&begin_date=2017-1-1&end_date=2017-12-31&tn=newstitledy&ct=0&rn=1&q6='
        self.url_list.append(url)

    def analysis(self,content):
        #print content
        pattern = re.compile(r'<span class="nums">找到相关新闻(.*?)篇</span>',re.S)
        items = re.findall(pattern,content)
        if items:
            return items[0]
        else:
            return 0

    def load(self,url,agent,tryCount,comp,year):
        try:
            req = urllib2.Request(url,headers={'User-Agent' : agent})
            response = urllib2.urlopen(req)
            content = response.read()#.decode('utf-8')
            return content
        except Exception as e:
            tryCount += 1
            print '[%s][%d]错误发生，重试中[第%d次]' %(comp,year,tryCount)
            if tryCount < 3:
                return self.load(url,agent,tryCount,comp,year)
            else:
                print '[%s][%d]重试多次,获取该条失败' %(comp,year)
                return ''

    def getContent(self,threadName):
        while True:
            self.threadLock.acquire()
            index = self.index
            self.index += 1
            if self.index > len(self.list):
                self.threadLock.release()
                break
            self.threadLock.release()

            #print index
            self.getUrl(self.list[index])
            user_agent = self.user_agent[random.randint(0,4)]
            for i in range(len(self.url_list)):
                content = self.load(self.url_list[i],user_agent,0,self.list[index],2014+i)
                self.excl.list[index].num.append(self.analysis(content))
            print '[%d---%s][%s]获取完毕' %(index,self.list[index],threadName)


    def run(self):
        self.list = self.excl.readExcl(u'爬数据.xlsx')
        threads = []
        thread_1 = threading.Thread(target=self.getContent,args=('thread_1',))
        thread_2 = threading.Thread(target=self.getContent,args=('thread_2',))
        thread_3 = threading.Thread(target=self.getContent,args=('thread_3',))
        thread_4 = threading.Thread(target=self.getContent,args=('thread_4',))
        thread_5 = threading.Thread(target=self.getContent,args=('thread_5',))
        thread_6 = threading.Thread(target=self.getContent,args=('thread_6',))
        thread_7 = threading.Thread(target=self.getContent,args=('thread_7',))
        thread_8 = threading.Thread(target=self.getContent,args=('thread_8',))
        threads.append(thread_1)
        threads.append(thread_2)
        threads.append(thread_3)
        threads.append(thread_4)
        threads.append(thread_5)
        threads.append(thread_6)
        threads.append(thread_7)
        threads.append(thread_8)

        for i in threads:
            i.start()

        for i in threads:
            i.join()

        self.excl.writeExcl(u'爬数据.xlsx')

ojbk = SPiDerBaiDuNews()
ojbk.run()







