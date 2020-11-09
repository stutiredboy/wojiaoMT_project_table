#ifndef __FireClient__SystemInfo__
#define __FireClient__SystemInfo__

#include <map>
#include <vector>

class MT3SystemInfo
{
public:
	static float sGetIOSVersionFloatValue();
	static std::string sGetMacAddr();
	static void sSendSystemInfo();

public:
#if (defined ANDROID) || (defined WIN7_32) || (defined WINAPI_FAMILY && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
    #include "utils/StringCover.h"
	static std::wstring sIDFAValue(){ return StringCover::to_wstring(""); }
	static std::wstring sOpenUDIDValue(){ return StringCover::to_wstring(""); }
	static std::wstring sMacValue(){ return StringCover::to_wstring(""); }
#else
	static std::wstring sIDFAValue();
	static std::wstring sOpenUDIDValue();
	static std::wstring sMacValue();
#endif
private:
	static void sGetOSVersion();		// IOS�ֻ�ϵͳ�汾��
    static void sGetResolution();		// IOS�ֻ���Ļ�Ŀ�͸�
	static void sGetDeviceID();		// IOS�ֻ�MAC��ַ��ȡ������ȡIDFA��
   
	static void sGetPhoneNum();		// IOS�û��ֻ���
    
    static void sGetUDID();			// IOS�豸UDID
    static void sGetIOSDeviceType();	// IOS�ֻ��ͺţ�iPad��iPhone 5��
	static void sGetProvider();		// IOS�û�������Ӫ��
	static void sGetNetEnvir();		// IOS�ֻ���������
	static void sGetIMEI();			// IOS�ֻ�IMEI

private:
    static std::map<std::wstring, std::wstring> m_MapSystemInfo;
};

#endif
