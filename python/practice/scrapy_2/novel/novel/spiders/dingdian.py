# -*- coding: utf-8 -*-
import scrapy
from scrapy.http import Request
from ..items import NovelItem


class DingdianSpider(scrapy.Spider):
    name = 'dingdian'
    allowed_domains = ['23us.so']
    bash_url = 'http://www.23us.so/list/'
    bash_html = '.html'

    def start_requests(self):
        for i in range(1,9):
            url = self.bash_url + str(i) + '_1' + self.bash_html
            yield Request(url, self.parse)
        yield Request('http://www.23us.so/full.html',self.parse)

    def parse(self, response):
        #novels = response.xpath('//dl[@id="content"]/dd/table/tbody/tr[@bgcolor="#FFFFFF"]')
        novels = response.xpath('//*[@id="content"]/dd[1]/table/tbody/tr[2]')
        print novels.extract()
        links = response.xpath('//dl[@id="content"]/dd[@class="pages"]/div')
        category = response.xpath(r'//dl[@id="content"]/dt/text()')

        for i in novels:
            item = NovelItem()
            item['name'] = i.xpath('/td[1]')
            item['author'] = i.xpath('/td[3]')
            item['time'] = i.xpath('/td[5]')
            item['serialStatus'] = i.xpath('/td[6]')
            item['serialNums'] = i.xpath('/td[4]')
            item['category'] = category
            yield item
