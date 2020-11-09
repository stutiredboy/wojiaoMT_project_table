#!/bin/sh

# 检查运行环境

if [ "$1" == "" ]; then
	echo "-->Usage:   update.sh   <SNAIL_BIN_DIR>"
	exit
fi
if [ ! -d "$1" ]; then
	echo "-->{<SNAIL_BIN_DIR> == \"$1\"} not exist!"
	exit
fi
echo "--><SNAIL_BIN_DIR> == $1" 

echo "-->Check <SNAIL_BIN_DIR>'s integrity:"
if [ ! -f "$1/dbtool" ]; then
	echo "   False: $1/dbtool not exist!"
	exit
fi
if [ ! -f "$1/libdb_i386.so" ]; then
	echo "   False: $1/libdb_i386.so not exist!"
	exit
fi
if [ ! -f "$1/libdb_amd64.so" ]; then
	echo "   False: $1/libdb_amd64.so not exist!"
	exit
fi
if [ ! -f "$1/db_x86.dll" ]; then
	echo "   False: $1/db_x86.dll not exist!"
	exit
fi
if [ ! -f "$1/xdb.jar" ]; then
	echo "   False: $1/xdb.jar not exist!"
	exit
fi
echo "-->TRUE"

#备份旧的程序 && 备份旧的数据库
if [ ! -d "./old__lib" ] || [ ! -d "./old__xdb" ]; then
	mkdir ./old__lib	
	mkdir ./old__xdb
else
	echo "   Warning: old_lib or old_xdb exist!"		
	echo "      Please Make Sure First Update the Project And"
	echo "      Reuse update.sh After del DIR old_lib && DIR old_xdb"
	echo "   Program exit"
	exit
fi

echo "-->backup old lib_files to ./old__lib"
cp lib2/xdb.jar old__lib/
cp libdb_i386.so old__lib/
cp libdb_amd64.so old__lib/
cp db_x86.dll old__lib/

echo "-->Compress xdb/dbdata to xdb/dbdata_c Temp Dir"
$1/dbtool -c xdb/dbdata
echo "-->backup old xdb/dbdata to old__xdb/dbdata"
mv xdb/dbdata old__xdb/
mv xdb/dbdata_c xdb/dbdata
echo "-->del xdb/dbdata_c && move xdb/dbdata_c to xdb/dbdata"

#更新程序。
echo "-->cpy lib_files"
cp $1/xdb.jar ./lib2/
cp $1/libdb_i386.so ./
cp $1/libdb_amd64.so ./
cp $1/db_x86.dll ./

echo "-->======    Updata Success    ======"
