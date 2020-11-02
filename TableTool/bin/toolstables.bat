#!/bin/bash

##################################################
# ��ӡ����MBEAN��Ϣ��

#���Ӳ�����ʽ��鿴 tools.jar �İ�����������Դ�롣^_^ ��
#    �磺zg.gs.Main�������ڵ�������ʵ����
CONNECTION=$1

#���Կ��ǰ� grep ��������ֻ��ӡĳ�ű���ĳЩ��
TABLES=`java -jar tools.jar mbeans -c ${CONNECTION} | grep "xdb:type=Tables,name="`

for BEANNAME in ${TABLES}
do
	java -jar tools.jar attrs -c ${CONNECTION} -b ${BEANNAME}
done
