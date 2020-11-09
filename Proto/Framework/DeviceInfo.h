#ifndef FireClient_DeviceInfo_h
#define FireClient_DeviceInfo_h

#include "utils/StringUtil.h"
#include "utils/StringCover.h"
#include "GameApplication.h"

class DeviceInfo
{
public:
    
    static int sGetDeviceType(); // 0:DEBUG, 1:ios, 2:android, 3:wp8
	static const char* sGetCurDeviceName();

	static void sInitDeviceInfo();

	static int sGetCpuFrequency();
	static int sGetMaxCpuFreq();
	static int sGetCpuCount();
	static const char* sGetCpuName();

    static int sGetTotalMemSize();
    static int sGetFreeMemSize();
    
	static float sGetAppCpuRate();				// ANDROID��ϷCPUռ����
    static const char* sGetOSVersion();			// ANDROID�ֻ�ϵͳ�汾��
	static int		   sGetOSVersionCode();		// ANDROID�ֻ�ϵͳ�汾��(��������)
	static const char* sGetProductModel();		// ANDROID�ֻ��ͺ�
	static const char* sGetNetEnvir();			// ANDROID�ֻ���������
	static const char* sGetMacAddress();		// ANDROID�ֻ�MAC��ַ
	static const char* sGetNoColonMacAddress();	// ȥ��ð�ŵ�MAC��ַ
	static const char* sGetIPAddress();			// PC��IP��ַ
	static const char* sGetScreenWidthInfo();	// ANDROID��Ļ��ȣ����أ�
    static const char* sGetScreenHeightInfo();	// ANDROID��Ļ�߶ȣ����أ�
    static const char* sGetVersionName();		// ANDROID��Ϸ�汾��
    static const char* sGetPhoneNumber();		// ANDROID�û��ֻ���
	static const char* sGetDeviceID();			// ANDROID�豸Ψһ��ʶ��IMEI
	static const char* sGetProvider();			// ANDROID�û�������Ӫ��

private:
	static void byte2Hex(unsigned char bData, unsigned char hex[]);

public:
	static std::string s_strDevDesc;

    static int s_nCpuFrequency;
	static int s_nMaxCpuFreq;
	static int s_nCpuCount;
	static std::string s_strCpuName;

    static int s_nTotalMemSize; //unit: MByte
    static int s_nFreeMemSize; //unit: MByte

	static float s_fAppCpuRate;
    static std::string s_strAppSrc;
    static std::string s_strOSVersion;
	static int		   s_iOSVersionCode;
	static std::string s_strProductModel;
	static std::string s_strNetEnvir;
    static std::string s_strMacAddress;
	static std::string s_strNoColonMacAddress;
	static std::string s_strIPAddress;
    static std::string s_strScreenWidthInfo;
    static std::string s_strScreenHeightInfo;
    static std::string s_strVersionName;
    static std::string s_strPhoneNumber;
	static std::string s_strDeviceID;
	static std::string s_strProvider;
};

#endif // FireClient_DeviceInfo_h
