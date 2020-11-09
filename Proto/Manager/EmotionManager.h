/***********************************************************************
filename: 	IconManager.h
purpose:	�������()
*************************************************************************/
#pragma once
#include "Singleton.hpp"


struct stEmotionInf 
{
	int id;
	std::wstring accesskey;		//��ݷ�ʽ
	std::wstring tips;			//����
	float duration;				//����ʱ��  �������벥����һ��
	int toalFrame;				//��֡��
};

struct stImageSetInf 
{
	int id;
	int endImage;				//imageset������image
	int startImage;				//imageset��ʼ��image

	stImageSetInf(int _id, int _startImage, int _endImage);
};

class EmotionManager : public CSingleton<EmotionManager>
{
public: 
	EmotionManager();
	~EmotionManager();

	const static int s_iPerImageSetEmotioIconNum = 144;		//ÿһ��imageset�����ı���ͼ����

	bool isNextCharEmotionExist(int id);					//�Ƿ������һλ�ı��飬����˵��id=20ʱ�治����idΪ210-219�ı���
	bool isEmotionExist(int id);							//ĳ�������Ƿ�棬����true������iD�ı������
	void ClearEmotionPackInf();								//���ص�½����ʱ��������Ϣ
	bool isEmotionCanUse(int id);							//ĳ�������Ƿ����
	bool CheckRichEditBoxEmotionCanUse(CEGUI::RichEditbox* pBox);	//��������������б����Ƿ����
	int GetPackIDByEmotionID(int id);						//���ݱ���id��ö�Ӧ�İ�
	bool isEmotionPackCanUse(int id);
	bool isEmotionPackFree(int id);
	const std::map<int, int64_t>& GetEmotionPackInf();
	int64_t GetEmotionPackTime(int packID);					//�õ�ĳ���������ʣ��ʱ�䣬��λ������
	void RefreshEmotionPackTime(int elapse);
	void RefreshEmotionPackInf(int packID, int64_t time);	//ˢ�±������Ϣ
	std::wstring GetEmotionTips(int id);
	int GetImageSetIndexByIDAndFrame(int id, int frame);
	int GetEmotionsCount();
	const std::vector<stEmotionInf>& GetAllEmotion();
	int GetFrameByElapseTime(int id, float fElapse);			//  pos>0.0f pos<1.0f  1.0��ʾ�������һ֡
	float GetEmotionDuration(int id);
	int GetEmotionTotalFrame(int id);
	void AddEmotion(int id, int totalFrame, float duration, const std::wstring& strTips, const std::wstring& strAccessKey);
	void LoadAllEmotionInf();
	void InitEmitionImagesetIdxInf();						//��ʼ�������Ӧ��imageset��Ϣ

private:
	int m_maxEmotionID;
	std::map<int, int64_t> m_mapEmotionPackInf; //�������Ϣ
	std::vector<stImageSetInf> m_vecImageSetInf;
	std::vector<stEmotionInf> m_vecEmotionInfs;


};

inline EmotionManager* gGetEmotionManager()
{
	return EmotionManager::GetInstance();
}

