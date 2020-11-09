#include "SoundCapturer.h"

#include <windows.h>
#include <dsconf.h>
#pragma comment(lib, "dsound.lib")

#include <assert.h>

#include "WaveFile.h"

CSoundCapturer::CSoundCapturer(IN PWAVEFORMATEX npdWaveFormatEx)
{
	mhWaveIn = NULL;

	ZeroMemory(&mdWaveHdr1, sizeof(mdWaveHdr1));
	ZeroMemory(&mdWaveHdr2, sizeof(mdWaveHdr1));

	mdWaveHdr1.lpData = (LPSTR)new BYTE[CB_WAVE_FORM_BUFFER];
	ZeroMemory(mdWaveHdr1.lpData, CB_WAVE_FORM_BUFFER);
	mdWaveHdr1.dwBufferLength = CB_WAVE_FORM_BUFFER;
	
	mdWaveHdr2.lpData = (LPSTR)new BYTE[CB_WAVE_FORM_BUFFER];
	ZeroMemory(mdWaveHdr2.lpData, CB_WAVE_FORM_BUFFER);
	mdWaveHdr2.dwBufferLength = CB_WAVE_FORM_BUFFER;

	mpDataBuffer = NULL;
	mlCbBuffer = 0;

	// Ĭ��PCM��ʽ
	if(NULL == npdWaveFormatEx)
	{
		ZeroMemory( &mdWaveFormatEx, sizeof(mdWaveFormatEx));
		mdWaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;	// ͨ�����������������õ�ͨ����������ͨ����˫ͨ��
		mdWaveFormatEx.nSamplesPerSec = 8000;			// �����ʣ�HZ����ÿ���Ӳ�ȡ�����Ĵ���
		mdWaveFormatEx.wBitsPerSample =  16;			// ÿ��������λ����for WAVE_FORMAT_PCM��wBitsPerSample�������8����16
		mdWaveFormatEx.nChannels = 1;					// ͨ�����������������õ�ͨ����������ͨ����˫ͨ��
		mdWaveFormatEx.nBlockAlign = mdWaveFormatEx.nChannels * (mdWaveFormatEx.wBitsPerSample / 8);// ÿ���������ֽ�����for WAVE_FORMAT_PCM��nBlockAlign = (nChannels �� wBitsPerSample) / 8
		mdWaveFormatEx.nAvgBytesPerSec = mdWaveFormatEx.nBlockAlign * mdWaveFormatEx.nSamplesPerSec;	// ÿ��ת�����ݵ��ֽ�����for WAVE_FORMAT_PCM��nAvgBytesPerSec = nSamplesPerSec * nBlockAlign
	}
	else
		memcpy(&mdWaveFormatEx, npdWaveFormatEx, sizeof(WAVEFORMATEX));

	mbIsStop = true;
}


CSoundCapturer::~CSoundCapturer(void)
{
	StopRecord();

	if(NULL != mhWaveIn)
		waveInClose(mhWaveIn);

	if(NULL != mdWaveHdr1.lpData)
		delete [] mdWaveHdr1.lpData;

	if(NULL != mdWaveHdr2.lpData)
		delete [] mdWaveHdr2.lpData;

	if(NULL != mpDataBuffer)
	{
		delete [] mpDataBuffer;
	}
}


// ������Ƶ�����豸ö�ٺ���
MMRESULT CSoundCapturer::SetEnumCallBackProc(
	IN PSCENUMCALLBACK npFunAddress,		// �ص�������ַ
	IN LPVOID npContext						// �����ص�������������
	)
{
	MMRESULT lhMMResult = MMSYSERR_ERROR;
	do 
	{
		if(NULL == npFunAddress)
			lhMMResult = MMSYSERR_INVALPARAM;

		// ע��������׽�豸ö�ٻص�����
		lhMMResult = DirectSoundCaptureEnumerate((LPDSENUMCALLBACK)npFunAddress,npContext);

	} while (false);
	return lhMMResult;
}


//// ���õ�ǰ��Ƶ�����豸
//MMRESULT CSoundCapturer::SetSoundCaptureDev(
//	IN UINT nuiDevID						// �豸ID
//	)
//{
//	MMRESULT lhMMResult = MMSYSERR_ERROR;
//	do 
//	{
//		if(NULL != mhWaveIn)
//		{
//			waveInClose(mhWaveIn);
//		}
//
//		waveInOpen(mhWaveIn)
//
//	} while (false);
//	return lhMMResult;
//}


// ����¼��
MMRESULT CSoundCapturer::StartRecord(
	IN LPGUID npDevGUID								// �豸GUID�����Ϊ�գ���ʹ��Ĭ�ϵ��豸
	)
{
	MMRESULT lhMMResult = MMSYSERR_ERROR;
	do 
	{
		// ��ȡ�豸ID
		UINT luiDevID = WAVE_MAPPER;
		if(NULL != npDevGUID)
		{
			// ͨ��GUID��ȡ�豸ID�Լ�������Ϣ
			DWORD ldwDevID;
			wstring loWstrDescrib;
			wstring loWstrModule;
			wstring loWstrInterface;
			if(FALSE == GetInfoFromDSoundGUID(*npDevGUID, ldwDevID, loWstrDescrib, loWstrModule, loWstrInterface))
			{
				lhMMResult = MMSYSERR_INVALPARAM;
				break;
			}
			luiDevID = (UINT)ldwDevID;
		}

		// ȷ��֮ǰ��¼���������
		if(NULL != mhWaveIn)
		{
			lhMMResult = StopRecord();
			if(MMSYSERR_NOERROR != lhMMResult)
				break;
		}

		// ���豸
		lhMMResult = waveInOpen(&mhWaveIn, luiDevID, &mdWaveFormatEx, (DWORD)CSoundCapturer::WaveInMsgProc, (DWORD)this, CALLBACK_FUNCTION);
		if(MMSYSERR_NOERROR != lhMMResult)
			break;

		// ׼�����ݻ�����
		lhMMResult = waveInPrepareHeader(mhWaveIn, &mdWaveHdr1, sizeof(mdWaveHdr1));
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}
		lhMMResult = waveInAddBuffer(mhWaveIn, &mdWaveHdr1, sizeof (mdWaveHdr1));
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}

		lhMMResult = waveInPrepareHeader(mhWaveIn, &mdWaveHdr2, sizeof(mdWaveHdr2));
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}
		lhMMResult = waveInAddBuffer(mhWaveIn, &mdWaveHdr2, sizeof (mdWaveHdr2));
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}

		// ��ʼ¼��
		mbIsStop = false;
		lhMMResult = waveInStart(mhWaveIn);
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}

	} while (false);
	return lhMMResult;
}

void CALLBACK CSoundCapturer::WaveInMsgProc(HWAVEIN hwi,UINT uMsg,DWORD_PTR dwInstance,DWORD_PTR dwParam1,DWORD_PTR dwParam2)
{
	CSoundCapturer* lpoThis = (CSoundCapturer*)dwInstance;
	assert(NULL != lpoThis);

	MMRESULT lhMMResult = MMSYSERR_ERROR;
	switch(uMsg)
	{
	case WIM_OPEN:			// ����Ϣ��waveInOpen�����ڲ��͵����ˣ���ʱHWAVEIN������Ч״̬�����Բ���������׼��������
		{
			// ɾ���洢��¼������
			if(NULL != lpoThis->mpDataBuffer)
			{
				free(lpoThis->mpDataBuffer);
				lpoThis->mpDataBuffer = NULL;
			}

			lpoThis->mlCbBuffer = 0;
		}
		break;
	case WIM_DATA:
		{
			PWAVEHDR lpoWaveHdr = (PWAVEHDR)dwParam1;
			if((WHDR_DONE & lpoWaveHdr->dwFlags) != 1)
				break;

			// ���·����ڴ�洢����
			lpoThis->mpDataBuffer = (BYTE*)realloc(lpoThis->mpDataBuffer, lpoThis->mlCbBuffer + lpoWaveHdr->dwBytesRecorded);
			if(NULL == lpoThis->mpDataBuffer)
			{
				break;
			}

			if(0 != memcpy_s(lpoThis->mpDataBuffer + lpoThis->mlCbBuffer,
				lpoWaveHdr->dwBytesRecorded, lpoWaveHdr->lpData, lpoWaveHdr->dwBytesRecorded))
				break;

			lpoThis->mlCbBuffer += lpoWaveHdr->dwBytesRecorded;

			// ����Ѿ�û��ֹͣ¼������ѭ���������������
			if(false == lpoThis->mbIsStop)
			{
				// ѭ�����û�����
				lhMMResult = waveInAddBuffer(lpoThis->mhWaveIn, lpoWaveHdr, sizeof(WAVEHDR));
				if(MMSYSERR_NOERROR != lhMMResult)
				{
					break;
				}
			}


		}
		break;
	case WIM_CLOSE:
		{
			// ж��֮ǰ׼���Ļ���ͷ
			lhMMResult = waveInUnprepareHeader(lpoThis->mhWaveIn, &lpoThis->mdWaveHdr1, sizeof(lpoThis->mdWaveHdr1));
			if(MMSYSERR_NOERROR != lhMMResult)
			{
				break;
			}

			lhMMResult = waveInUnprepareHeader(lpoThis->mhWaveIn, &lpoThis->mdWaveHdr2, sizeof(lpoThis->mdWaveHdr2));
			if(MMSYSERR_NOERROR != lhMMResult)
			{
				break;
			}
		}
		break;

	default:
		break;
	}
}

// ֹͣ¼��
MMRESULT CSoundCapturer::StopRecord()
{
	mbIsStop = true;
	if(NULL != mhWaveIn)
	{
		MMRESULT lhMMRestult = waveInStop(mhWaveIn);
		if(MMSYSERR_NOERROR != lhMMRestult)
			return lhMMRestult;

		// ע��reset������ʹ�����е�buffer������done״̬����������Ҫ���ϱ�ǣ������ݴ���ĵط����ټ��뻺����
		lhMMRestult = waveInReset(mhWaveIn);
		if(MMSYSERR_NOERROR != lhMMRestult)
			return lhMMRestult;

		// ע�⣬ֻ������Buffer��return�˲��ܳɹ�
		lhMMRestult = waveInClose(mhWaveIn);
		if (MMSYSERR_NOERROR != lhMMRestult)
			return lhMMRestult;

		mhWaveIn = NULL;
	}
	return MMSYSERR_NOERROR;
}


// ����¼�����ݵ��ļ�
MMRESULT CSoundCapturer::SaveRecordToFile(
	IN wchar_t* nswFileName
	)
{
	MMRESULT lhMMResult = MMSYSERR_ERROR;
	do 
	{
		if(NULL == mpDataBuffer || 0 == mlCbBuffer)
		{
			break;
		}

		// �����ļ�
		CWaveFile loWaveFile;
		lhMMResult = loWaveFile.Open(nswFileName, &mdWaveFormatEx, WAVEFILE_WRITE);
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			loWaveFile.Close();
			break;
		}

		// д������
		UINT luiDataWrote;
		lhMMResult = loWaveFile.Write(mlCbBuffer, mpDataBuffer, &luiDataWrote);
		if(MMSYSERR_NOERROR != lhMMResult)
		{
			break;
		}

		// �ر��ļ�
		lhMMResult = loWaveFile.Close();
		
	} while (false);
	return lhMMResult;
}

// ��ȡ��������
void CSoundCapturer::GetErrorDescribe(
	IN MMRESULT nhMMResult,
	OUT wstring& noWStrDescrib)
{
	wchar_t* lswErrText = new wchar_t[MAXERRORLENGTH];
	assert(NULL != lswErrText);

	ZeroMemory(lswErrText, MAXERRORLENGTH);
	MMRESULT lhMMResult = waveInGetErrorTextW(nhMMResult, lswErrText, MAXERRORLENGTH);
	assert(lhMMResult == MMSYSERR_NOERROR);
	noWStrDescrib = lswErrText;

	delete [] lswErrText;
}

//////////////////////////////////////////////////////////////////////////
// ͨ��GUID��ȡ�豸������Ϣ

typedef WINUSERAPI MMRESULT (WINAPI *LPFNDLLGETCLASSOBJECT) (const CLSID &, const IID &, void **);
MMRESULT CSoundCapturer::DirectSoundPrivateCreate (OUT LPKSPROPERTYSET * ppKsPropertySet) 
{ 
	HMODULE                 hLibDsound              = NULL; 
	LPFNDLLGETCLASSOBJECT   pfnDllGetClassObject    = NULL; 
	LPCLASSFACTORY          pClassFactory           = NULL; 
	LPKSPROPERTYSET         pKsPropertySet          = NULL; 
	MMRESULT                 lhMMResult                      = DS_OK; 

	// Load dsound.dll 
	hLibDsound = LoadLibrary(TEXT("dsound.dll")); 

	if(!hLibDsound) 
	{ 
		lhMMResult = DSERR_GENERIC; 
	} 

	// Find DllGetClassObject 
	if(SUCCEEDED(lhMMResult)) 
	{ 
		pfnDllGetClassObject = 
			(LPFNDLLGETCLASSOBJECT)GetProcAddress ( hLibDsound, "DllGetClassObject" ); 


		if(!pfnDllGetClassObject) 
		{ 
			lhMMResult = DSERR_GENERIC; 
		} 
	} 

	// Create a class factory object     
	if(SUCCEEDED(lhMMResult)) 
	{ 
		lhMMResult = pfnDllGetClassObject (CLSID_DirectSoundPrivate, IID_IClassFactory, (LPVOID *)&pClassFactory ); 
	} 

	// Create the DirectSoundPrivate object and query for an IKsPropertySet 
	// interface 
	if(SUCCEEDED(lhMMResult)) 
	{ 
		lhMMResult = pClassFactory->CreateInstance ( NULL, IID_IKsPropertySet, (LPVOID *)&pKsPropertySet ); 
	} 

	// Release the class factory 
	if(pClassFactory) 
	{ 
		pClassFactory->Release(); 
	} 

	// Handle final success or failure 
	if(SUCCEEDED(lhMMResult)) 
	{ 
		*ppKsPropertySet = pKsPropertySet; 
	} 
	else if(pKsPropertySet) 
	{ 
		pKsPropertySet->Release(); 
	} 

	FreeLibrary(hLibDsound); 

	return lhMMResult; 
} 

 //Get the device information about a DirectSound GUID.  Description and Module is retrieved on a regular
 //DSound enumeration, but the Interface and the corresponding WaveID is not.
 //Thank you to anonymous person on DirectX team who demonstrated that I must call Get() twice in this case.
BOOL CSoundCapturer::GetInfoFromDSoundGUID( GUID i_sGUID, DWORD &dwWaveID, wstring &Description, wstring &Module, wstring &Interface)
{ 
	LPKSPROPERTYSET         pKsPropertySet = NULL; 
	MMRESULT                 lhMMResult; 
	BOOL					retval = FALSE;

	PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA psDirectSoundDeviceDescription = NULL; 
	DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA sDirectSoundDeviceDescription;

	memset(&sDirectSoundDeviceDescription,0,sizeof(sDirectSoundDeviceDescription)); 
	lhMMResult = DirectSoundPrivateCreate( &pKsPropertySet ); 
	if(SUCCEEDED(lhMMResult)) 
	{ 
		ULONG ulBytesReturned = 0;
		sDirectSoundDeviceDescription.DeviceId = i_sGUID; 

		// On the first call the final size is unknown so pass the size of the struct in order to receive
		// "Type" and "DataFlow" values, ulBytesReturned will be populated with bytes required for struct+strings.
		lhMMResult = pKsPropertySet->Get(DSPROPSETID_DirectSoundDevice, 
			DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION, 
			NULL, 
			0, 
			&sDirectSoundDeviceDescription, 
			sizeof(sDirectSoundDeviceDescription), 
			&ulBytesReturned
			); 

		if (ulBytesReturned)
		{
			// On the first call it notifies us of the required amount of memory in order to receive the strings.
			// Allocate the required memory, the strings will be pointed to the memory space directly after the struct.
			psDirectSoundDeviceDescription = (PDSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA)new BYTE[ulBytesReturned];
			*psDirectSoundDeviceDescription = sDirectSoundDeviceDescription;

			lhMMResult = pKsPropertySet->Get(DSPROPSETID_DirectSoundDevice, 
				DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION, 
				NULL, 
				0, 
				psDirectSoundDeviceDescription, 
				ulBytesReturned, 
				&ulBytesReturned
				); 

			dwWaveID  = psDirectSoundDeviceDescription->WaveDeviceId;
			Description = psDirectSoundDeviceDescription->Description;
			Module = psDirectSoundDeviceDescription->Module;
			Interface = psDirectSoundDeviceDescription->Interface;
			delete [] psDirectSoundDeviceDescription;
			retval = TRUE;
		}

		pKsPropertySet->Release(); 
	} 

	return retval; 
} 

//////////////////////////////////////////////////////////////////////////