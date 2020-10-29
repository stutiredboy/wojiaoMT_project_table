
REM ==========================================================
REM rpcgenmerge
REM
REM rpcgen 生成inl文件时，即使文件内容完全一样，也会重新生成，
REM 造成文件的修改时间发生变化，影响编译速度。
REM
REM 这个脚本通过备份和恢复文件的修改时间，提高编译速度。
REM 使用例子如下

set SNAIL_BIN=../snail/bin

REM ==========================================================
REM 备份文件
if exist gzg\rpcgen xcopy /e /i gzg\rpcgen gzg\rpcgen1
if exist gzg\rpcgen.hpp copy gzg\rpcgen.hpp gzg\rpcgen1.hpp
if exist gzg\rpcgen.cpp copy gzg\rpcgen.cpp gzg\rpcgen1.cpp
if exist gzg\protocols.hpp copy gzg\protocols.hpp gzg\protocols1.hpp

REM ==========================================================
REM 正常生成
java -jar %SNAIL_BIN%/rpcgen.jar -aio your.xml

REM ==========================================================
REM 恢复文件，如果内容完全一样（修改时间）
if exist gzg\rpcgen1 rpcgenmerge.exe gzg\rpcgen gzg\rpcgen1
if exist gzg\rpcgen1.hpp rpcgenmerge.exe restore file to gzg\rpcgen.hpp gzg\rpcgen1.hpp
if exist gzg\rpcgen1.cpp rpcgenmerge.exe restore file to gzg\rpcgen.cpp gzg\rpcgen1.cpp
if exist gzg\protocols1.cpp rpcgenmerge.exe restore file to gzg\protocols.hpp gzg\protocols1.hpp

REM ==========================================================
REM 删除备份
if exist gzg\rpcgen1 rd /s /q gzg\rpcgen1
if exist gzg\rpcgen1.hpp del gzg\rpcgen1.hpp
if exist gzg\rpcgen1.cpp del gzg\rpcgen1.cpp
if exist gzg\protocols1.hpp del gzg\protocols1.hpp
