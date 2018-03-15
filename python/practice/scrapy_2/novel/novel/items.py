# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class NovelItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    #名字
    name = scrapy.Field()
    #作者
    author = scrapy.Field()
    #地址
    novelUrl = scrapy.Field()
    #状态
    serialStatus = scrapy.Field()
    #字数
    serialNums = scrapy.Field()
    #分类
    category = scrapy.Field()
    #编号
    time =scrapy.Field()
