# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
from mypipelines.sql import CNovel

class NovelPipeline(object):
    def process_item(self, item, spider):
        obj = CNovel()
        obj.copy(item)
        print "[debug]"+obj.Serialization()
        obj.insert()

