import redis
from __init__ import REDIS_HOSTS,REDIS_PORT

db = redis.Redis(host=REDIS_HOSTS,port=REDIS_PORT,db=0)

class CNovel:
    def __init__(self):
        self.name = ''
        self.author = ''
        self.novelUrl = ''
        self.serialStatus = ''
        self.serialNums = 0
        self.category = ''
        self.time = 0

    def copy(self,item):
        self.name = item['name']
        self.author = item['author']
        self.novelUrl = item['novelUrl']
        self.serialStatus = item['serialStatus']
        self.serialNums = item['serialNums']
        self.category = item['category']
        self.time = item['time']

    def Serialization(self):
        return ''+self.name+','+self.author+','+self.novelUrl+','+self.serialStatus+','+str(self.serialNums)+','+self.category+','+str(self.time)

    def getkey(self):
        return 'novel:%s' %self.name

    def getValue(self):
        return {'name':'%s' %self.name,
                'author':'%s' %self.author,
                  'novelUrl':'%s' %self.novelUrl,
                  'serialStatus':'%s' %self.serialStatus,
                  'serialNums':'%s' %self.serialNums,
                  'category':'%s' %self.category,
                  'time':'%s' %self.time}

    def insert(self):
        if db.hmset(self.getkey(),self.getValue()) is False:
            print "[debug-redis]: error"
        if db.hget('novel:%s' %self.name,'author'):
            print "[debug-output]:"+db.hget('novel:%s' %self.name,'author')



