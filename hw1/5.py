import urllib2
import re
import copy
import threading
import Queue
class work(threading.Thread):
      def __init__(self,main_url,i,entry_dict):
          self.main_url=main_url
          self.i=i
          self.entry_dict=entry_dict
          self.queue_urls=Queue.Queue(maxsize=-1)
      def many_thread(self):        
          t1=threading.Thread(target=self.get_url)
          self.threads.append(t1)
          t2=threading.Thread(target=self.get_url)
          self.threads.append(t2)
          t3=threading.Thread(target=self.get_url)
          self.threads.append(t3)
          t4=threading.Thread(target=self.get_url)
          self.threads.append(t4)
      def get_url(self):
        if lock.acquire(): 
          try:
            main_url=self.queue_urls.get()
          finally:
            lock.release()
        self.all_url=urllib2.urlopen(main_url)
        self.link_list=re.findall(r"(?<=href=\").+?(?=\")|(?<=href=\').+?(?=\')" ,self.all_url.read())
        for url in self.link_list:
            if '/wiki/' in url:
               if (':' in url) or ('//' in url)or('Main'in url):
                  continue          
               entry_dict[url[6:]]=[0,i]
               entry_dict[url[6:]][0]+=1
               #print url[6:]
               #print self.entry_dict
               main_url='https://en.wikipedia.org'+url
               self.queue_urls.put(main_url)
               #print self.queue_urls.get()
      def line_work(self):
          for t in self.threads:
              print t.getName()
              t.start()
              time.sleep(1)
main_url="https://en.wikipedia.org/wiki/Shanghai_Jiao_Tong_University"
i=0
entry_dict={}
test=work(main_url,i,entry_dict)
test.get_url(main_url,i)
