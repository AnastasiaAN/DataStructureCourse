import urllib2
import re
import string
import timeit
def function():
    response = urllib2.urlopen('https://en.wikipedia.org/wiki/Shanghai_Jiao_Tong_University')
    html = response.read()
    link_list =re.findall(r"(?<=href=\").+?(?=\")|(?<=href=\').+?(?=\')" ,html)
    for url in link_list:
        print url
function()
#link_list_convert=''.join(link_list)
#print link_list_convert
#link_list2=re.findall('\\http+',link_list_convert)
#print link_list2
#html2=html.replace(" ","")
#link_list3=re.findall(r"<a.*?href=.*?<\/a>",html2,re.I)
#print "\n\n\n"
#for urls in link_list3:
    #print urls
