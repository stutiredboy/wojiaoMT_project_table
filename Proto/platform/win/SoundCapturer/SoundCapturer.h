/*
	Function:
		һ���򵥵�������׽����
		��Ҫʵ�ֵĹ������£�
			1��֧��ö�ٳ�������Ƶ�����豸��
			2���ṩʹ��ָ����Ƶ�����豸¼�����ܡ�
			3���ṩ��¼�����ݱ��浽ָ���ļ����ܡ�
	
	History:
		2013.07.03		��һ�δ���

	Author:
		Colin 
*/

#pragma once
//#include <Guiddef.h>
#include <windows.h>
#include <MMSystem.h>
#include <initguid.h>
#include <dsound.h>
#pragma comment(lib,"winmm.lib")

#include <string>
using std::wstring;

// ��Ƶ�����豸ö�ٺ�������// �μ�DirectSoundCaptureEnumerate����1
typedef BOOL (CALLBACK *PSCENUMCALLBACK)(LPGUID lpGUID, LPCTSTR lpszDesc,LPCTSTR lpszDrvName, LPVOID lpContext);


#define CB_WAVE_FORM_BUFFER	 16384		// ÿ���洢��Ƶ������ֽ�����С
class CSoundCapturer
{
public:
	CSoundCapturer(IN PWAVEFORMATEX npdWaveFormatEx = NULL);
	~CSoundCapturer(void);

	// ������Ƶ�����豸ö�ٺ���
	MMRESULT SetEnumCallBackProc(
		IN PSCENUMCALLBACK npFunAddress,		// �ص�������ַ
		IN LPVOID npContext						// �����ص�������������
		);

	// ��ȡ��ǰʹ�õ���Ƶ�豸��Ϣ
	

	// ����¼��
	MMRESULT StartRecord(
		IN LPGUID npDevGUID = NULL						// �豸GUID�����Ϊ�գ���ʹ��Ĭ�ϵ��豸
		);

	// ֹͣ¼��
	MMRESULT StopRecord();

	// ����¼�����ݵ��ļ�
	MMRESULT SaveRecordToFile(
		IN wchar_t* nswFileName
		);

	// ��ȡ��������
	void GetErrorDescribe(
		IN MMRESULT nhMMResult,
		OUT wstring& noWStrDescrib);

	// ͨ��DirectSound���ص��豸GUID����ȡ�豸�����Ϣ
	static BOOL GetInfoFromDSoundGUID( GUID i_sGUID, DWORD &dwWaveID, wstring &Description, wstring &Module, wstring &Interface);


protected:

	// ���ڴ�GUID��ȡID�ĺ���
	static MMRESULT DirectSoundPrivateCreate (OUT LPKSPROPERTYSET * ppKsPropertySet);
	
	
	// ����waveIn��Ϣ�Ļص�����
	static void CALLBACK WaveInMsgProc(HWAVEIN hwi,UINT uMsg,DWORD_PTR dwInstance,DWORD_PTR dwParam1,DWORD_PTR dwParam2);

private:
	WAVEFORMATEX mdWaveFormatEx;			// PCM��ʽ

	HWAVEIN	mhWaveIn;						// ��ʶ¼���豸�ľ��
	WAVEHDR	mdWaveHdr1,mdWaveHdr2;			// ��ʶ����¼����������ͷ�ṹ

	BYTE* mpDataBuffer;						// �洢���ݵ�Buffer		// ���bufferҪ��free�ͷ�	
	LONG mlCbBuffer;						// Buffer�Ĵ�С

	wstring moWstrError;					// ������Ϣ����

	bool mbIsStop;							// ����Ƿ�ֹͣ¼��
};

