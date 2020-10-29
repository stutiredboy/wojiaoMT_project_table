#!/usr/bin/python

import os
import sys
import re

def execute(cmd):
    print cmd
    return os.system(cmd)

def yesorno(q):
    a = raw_input(q + '[y(default)/n] : ')
    return a == '' or a == 'y'

def ask(q):
    return raw_input(q + ' : ')


user = ask("1, make user, input username")
if user == '':
    sys.exit(1)

if execute("mysqladmin create %s"%user):
    print user + ' already exist in mysql'
    sys.exit(1)

pw = ask('2, make passwd, input password, if empty, mkpasswd will generate for you')
if pw == '':
    pw = os.popen('mkpasswd -l 10').read()[:-1]
    while None != re.search("<|>|'|&|\"", pw) :
        pw = os.popen('mkpasswd -l 10').read()[:-1]

if execute( "mysql -e \"grant all on %s.* to %s@localhost identified by '%s'\""%(user, user, pw) ):
    sys.exit(1);

execute('cat jmonitor/mbeandb.xml.sample | sed s/{{username}}/%s/g | sed s/{{password}}/%s/g > jmonitor/mbeandb.xml'%(user, pw))
execute('cp jmonitor/lastfetch.xml.sample jmonitor/lastfetch.xml');
execute('cp jmonitor/access.xml.sample jmonitor/access.xml');

