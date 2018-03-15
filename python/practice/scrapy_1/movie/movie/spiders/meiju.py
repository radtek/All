# -*- coding: utf-8 -*-
import scrapy
from ..items import MovieItem

class MeijuSpider(scrapy.Spider):
    name = "meiju"
    allowed_domains = ["meijutt.com"]
    start_urls = ['http://www.meijutt.com/new100.html']

    def parse(self, response):
        movies = response.xpath('//ul[@class="top-list  fn-clear"]/li')
        for each_mov in movies:
            item = MovieItem()
            #item['name'] = each_mov.xpath('./h5/a/@title').extract()[0]
            item['name'] = each_mov.xpath('./h5/a/text()').extract()[0]
            #item['name'] = each_mov.xpath('./h5/a/string()').extract()[0] #无输出
            #item['name'] = each_mov.xpath('./h5/a/data()').extract()[0] #无输出
            print item['name']
            yield item
