
REM ==========================================================
REM rpcgenmerge
REM
REM rpcgen ����inl�ļ�ʱ����ʹ�ļ�������ȫһ����Ҳ���������ɣ�
REM ����ļ����޸�ʱ�䷢���仯��Ӱ������ٶȡ�
REM
REM ����ű�ͨ�����ݺͻָ��ļ����޸�ʱ�䣬��߱����ٶȡ�
REM ʹ����������

set SNAIL_BIN=../snail/bin

REM ==========================================================
REM �����ļ�
if exist gzg\rpcgen xcopy /e /i gzg\rpcgen gzg\rpcgen1
if exist gzg\rpcgen.hpp copy gzg\rpcgen.hpp gzg\rpcgen1.hpp
if exist gzg\rpcgen.cpp copy gzg\rpcgen.cpp gzg\rpcgen1.cpp
if exist gzg\protocols.hpp copy gzg\protocols.hpp gzg\protocols1.hpp

REM ==========================================================
REM ��������
java -jar %SNAIL_BIN%/rpcgen.jar -aio your.xml

REM ==========================================================
REM �ָ��ļ������������ȫһ�����޸�ʱ�䣩
if exist gzg\rpcgen1 rpcgenmerge.exe gzg\rpcgen gzg\rpcgen1
if exist gzg\rpcgen1.hpp rpcgenmerge.exe restore file to gzg\rpcgen.hpp gzg\rpcgen1.hpp
if exist gzg\rpcgen1.cpp rpcgenmerge.exe restore file to gzg\rpcgen.cpp gzg\rpcgen1.cpp
if exist gzg\protocols1.cpp rpcgenmerge.exe restore file to gzg\protocols.hpp gzg\protocols1.hpp

REM ==========================================================
REM ɾ������
if exist gzg\rpcgen1 rd /s /q gzg\rpcgen1
if exist gzg\rpcgen1.hpp del gzg\rpcgen1.hpp
if exist gzg\rpcgen1.cpp del gzg\rpcgen1.cpp
if exist gzg\protocols1.hpp del gzg\protocols1.hpp
