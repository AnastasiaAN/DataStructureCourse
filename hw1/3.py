import urllib2
import re
import time
def visit(main_url,i):
    global entry_dict
    while i<=2:
        # print main_url,i
         i=i+1
         all_url=urllib2.urlopen(main_url)
         link_list=re.findall(r"(?<=href=\").+?(?=\")|(?<=href=\').+?(?=\')" ,all_url.read())
         for url in link_list:
             if '/wiki/' in url:
                if (':' in url) or ('//' in url)or('Main'in url):
                   continue          
                entry_dict[url[6:]]=0
                entry_dict[url[6:]]+=1
              #  print url[6:]
                main_url='https://en.wikipedia.org'+url
                visit(main_url,i)
        # print entry_dict
entry_dict={}
main_url="https://en.wikipedia.org/wiki/Shanghai_Jiao_Tong_University"
i=0
visit(main_url,i)
for lists in sorted(entry_dict.items(),key=lambda d:-d[1]):
    print lists


