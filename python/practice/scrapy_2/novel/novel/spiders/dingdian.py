# -*- coding: utf-8 -*-
import scrapy
from scrapy.http import Request
from ..items import NovelItem

print "debug999"

def n1e(temp):
    if temp:
        return temp[0].encode('utf-8')

class DingdianSpider(scrapy.Spider):
    name = 'dingdian'
    allowed_domains = ['23us.so']
    bash_url = 'http://www.23us.so/list/'
    bash_html = '.html'


    def start_requests(self):
        for i in range( 1, 9):
            url = self.bash_url + str(i) + '_1' + self.bash_html
            yield Request(url, self.parse)
        yield Request('http://www.23us.so/full.html',self.parse)


    def parse(self, response):
        #novels = response.xpath('//dl[@id="content"]/dd/table/tbody/tr[@bgcolor="#FFFFFF"]') no tbody,create by chrome
        novels = response.xpath('//dl[@id="content"]/dd[1]/table/tr[@bgcolor="#FFFFFF"]')
        category = n1e(response.xpath(r'//dl[@id="content"]/dt/text()').extract())
        for i in novels:
            item = NovelItem()
            item['name'] = n1e(i.xpath('.//td[1]/a/text()').extract())
            item['novelUrl'] = n1e(i.xpath('.//td[1]/a/@href').extract())
            item['author'] = n1e(i.xpath('.//td[3]/text()').extract())
            item['time'] = n1e(i.xpath('.//td[5]/text()').extract())
            item['serialStatus'] = n1e(i.xpath('.//td[6]/text()').extract())
            item['serialNums'] = n1e(i.xpath('.//td[4]/text()').extract())
            item['category'] = category
            yield item