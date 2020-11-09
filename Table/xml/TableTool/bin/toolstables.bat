#!/bin/bash

##################################################
# 打印表格的MBEAN信息。

#连接参数格式请查看 tools.jar 的帮助或者它的源码。^_^ 。
#    如：zg.gs.Main，适用于单个进程实例。
CONNECTION=$1

#可以考虑把 grep 参数化，只打印某张表，或某些表。
TABLES=`java -jar tools.jar mbeans -c ${CONNECTION} | grep "xdb:type=Tables,name="`

for BEANNAME in ${TABLES}
do
	java -jar tools.jar attrs -c ${CONNECTION} -b ${BEANNAME}
done
