'''
import re
x=raw_input('Enter string')
#m=re.search('.*= (.*)/(.*)/(.*)/(.*) ms',x)
#print m.group(2)


x=raw_input('Enter string')
m=re.search('(.*),(.*), (.*)% packet loss',x)
print m.group(3)
'''

import re
import requests
from requests.auth import HTTPProxyAuth

URL = "http://www.spfld.com/cgi-bin/ping"
ip = input("ip")
onvar = "on"
ct = 10
sz = 64
PARAMS = {'remote_host':ip,'dns':onvar,'count':ct,'size':sz}

proxyDict = { 'http' : '172.16.115.24:3128', 'https' : '172.16.115.24:3128' } 
auth = HTTPProxyAuth('mitansh', 'pass')

f = open(ip+'.txt','w')

avg=0
f.write("Attempt")
for run in range(0, 20):
	r = requests.get(url = URL, params = PARAMS, proxies=proxyDict, auth=auth)
	inp = r.text
	lis = inp.splitlines()
	m=re.search('.*= (.*)/(.*)/(.*)/(.*) ms',lis[4])
	m.group(2)
	k=re.search('(.*),(.*), (.*)% packet loss',lis[3])
	f.write(m.group(2)+"\n"+k.group(3)+"\n")
	avg+=float(m.group(2))

f.write("avg="+str(avg)+"\n")

f.close()