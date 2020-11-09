#include "stdafx.h"

#include "EmotionManager.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIPropertyHelper.h"
#include "GameTable/chat/Cbiaoqing.h"


EmotionManager::EmotionManager()
	: m_maxEmotionID(0)
{
	m_vecEmotionInfs.resize(0);
	m_vecImageSetInf.clear();
	LoadAllEmotionInf();
	InitEmitionImagesetIdxInf();
}

EmotionManager::~EmotionManager()
{ }


//�Ƿ������һλ�ı��飬����˵��id=20ʱ�治����idΪ210-219�ı���
bool EmotionManager::isNextCharEmotionExist(int id)
{
	if (id >= m_maxEmotionID)
	{
		return false;
	}

	if (id >= 100)
	{
		return false;
	}

	if (id > m_maxEmotionID / 10)
	{
		return false;
	}

	if (id >= 15 && id < 20)  //���ǵ�150-199�ű��鲻�����#
	{
		return false;
	}

	for (int i = 0; i < 10; ++i)
	{
		if (isEmotionExist(id * 10 + i))
		{
			return true;
		}
	}

	return false;
}

//ĳ�������Ƿ�棬����true������iD�ı������
bool EmotionManager::isEmotionExist(int id)
{
	if (id >= 150 && id < 200)  //���ǵ�150-199�ű��鲻�����#
	{
		return false;
	}

	size_t num = m_vecEmotionInfs.size();
	for (size_t i = 0; i < num; ++i) {
		if (m_vecEmotionInfs[i].id == id) {
			return true;
		}
	}

	return false;
}

int EmotionManager::GetEmotionsCount()
{
	return m_maxEmotionID;
}

//���ص�½����ʱ��������Ϣ
void EmotionManager::ClearEmotionPackInf()
{
	m_mapEmotionPackInf.clear();
}

//ĳ�������Ƿ����
bool EmotionManager::isEmotionCanUse(int id)
{
	if (id >= 0) {
		int packID = GetPackIDByEmotionID(id);
		if (packID >= 0) {
			return isEmotionPackCanUse(packID);
		}
	}

	return false;
}

//��������������б����Ƿ����
bool EmotionManager::CheckRichEditBoxEmotionCanUse(CEGUI::RichEditbox* pBox)
{
	if (NULL != pBox) {
		std::vector<int> ids;
		pBox->GetAllEmotionID(ids);
		std::vector<int>::iterator it = ids.begin();
		for (; it != ids.end(); ++it) {
			int id = *it;

			if (!isEmotionCanUse(id)) {
				return false;
			}
		}
	}

	return true;
}

//���ݱ���id��ö�Ӧ�İ�
int EmotionManager::GetPackIDByEmotionID(int id)
{
	return -1;
}

bool EmotionManager::isEmotionPackCanUse(int id)
{
	if (isEmotionPackFree(id)) {
		return true;
	}

	int64_t time = GetEmotionPackTime(id);
	if (time > 0 || time == -1) {
		return true;
	}

	return false;
}

bool EmotionManager::isEmotionPackFree(int id)
{
	return false;
}

const std::map<int, int64_t>& EmotionManager::GetEmotionPackInf()
{
	return m_mapEmotionPackInf;
}

//�õ�ĳ���������ʣ��ʱ�䣬��λ������
int64_t EmotionManager::GetEmotionPackTime(int packID)
{
	std::map<int, int64_t>::iterator it = m_mapEmotionPackInf.find(packID);
	if (it != m_mapEmotionPackInf.end()) {
		return m_mapEmotionPackInf[packID];
	}
	return 0;
}

void EmotionManager::RefreshEmotionPackTime(int elapse)
{
	bool bNeedRefreshEmotionDlg = false; //�費��Ҫˢ�±���Ի���

	std::map<int, int64_t>::iterator it = m_mapEmotionPackInf.begin();
	for (; it != m_mapEmotionPackInf.end();) {
		int64_t time = it->second;
		if (time == -1) {
			return;
		}
		time -= elapse;
		if (time <= 0) {
			m_mapEmotionPackInf.erase(it++);
			bNeedRefreshEmotionDlg = true;
		}
		else {
			it->second = time;
			++it;
		}
	}
}

//ˢ�±������Ϣ
void EmotionManager::RefreshEmotionPackInf(int packID, int64_t time)
{
	m_mapEmotionPackInf[packID] = time;
}

std::wstring EmotionManager::GetEmotionTips(int id)
{
	for (size_t i = 0; i < m_vecEmotionInfs.size(); ++i) {
		if (m_vecEmotionInfs[i].id == id) {
			return m_vecEmotionInfs[i].tips;
		}
	}

	return L"";
}

int EmotionManager::GetImageSetIndexByIDAndFrame(int id, int frame)
{
	int IconIndex = 0;
	int imageID = 90000 + id * 100 + frame;
	std::vector<stImageSetInf>::const_iterator it = m_vecImageSetInf.begin();
	for (; it != m_vecImageSetInf.end(); ++it) {
		if (imageID >= (*it).startImage && imageID <= (*it).endImage) {
			IconIndex = (*it).id;
			break;
		}
	}

	return IconIndex;
}

const std::vector<stEmotionInf>& EmotionManager::GetAllEmotion()
{
	return m_vecEmotionInfs;
}

//  pos>0.0f pos<1.0f  1.0��ʾ�������һ֡
int EmotionManager::GetFrameByElapseTime(int id, float fElapse)
{
	int frame = 0;
	float duration = GetEmotionDuration(id);
	int totalFrame = GetEmotionTotalFrame(id);

	int round = (int)(fElapse / duration);
	frame = static_cast<int>((fElapse - round*duration) / duration*totalFrame);
	if (frame < 0)
	{
		frame = 0;
	}
	if (frame > totalFrame)
	{
		frame = totalFrame;
	}
	return frame;
}

float EmotionManager::GetEmotionDuration(int id)
{
	for (size_t i = 0; i < m_vecEmotionInfs.size(); ++i) {
		if (m_vecEmotionInfs[i].id == id) {
			return m_vecEmotionInfs[i].duration;
		}
	}

	return 0.0f;
}

int EmotionManager::GetEmotionTotalFrame(int id)
{
	for (size_t i = 0; i < m_vecEmotionInfs.size(); ++i) {
		if (m_vecEmotionInfs[i].id == id) {
			return m_vecEmotionInfs[i].toalFrame;
		}
	}

	return 0;
}

void EmotionManager::AddEmotion(int id, int totalFrame, float duration, const std::wstring& strTips, const std::wstring& strAccessKey)
{
	stEmotionInf Inf;
	Inf.id = id;
	Inf.toalFrame = totalFrame;
	Inf.duration = duration;
	Inf.tips = strTips;
	Inf.accesskey = strAccessKey;
	m_vecEmotionInfs.push_back(Inf);
	if (id > m_maxEmotionID) {
		m_maxEmotionID = id;
	}
}

//��ʼ�������Ӧ��imageset��Ϣ
void EmotionManager::InitEmitionImagesetIdxInf()
{
	CEGUI::String strEmotionImageSetName("emotionicon");

	for (int i = 0; i < 1000; ++i) {
		CEGUI::String strImgSetName = strEmotionImageSetName + CEGUI::PropertyHelper::intToString(i);
		if (CEGUI::ImagesetManager::getSingleton().isDefined(strImgSetName)) {
			const CEGUI::Imageset& imageSet = CEGUI::ImagesetManager::getSingleton().get(strImgSetName);
			CEGUI::String startImgName = imageSet.GetFirstImageName();
			CEGUI::String endImgName = imageSet.GetEndImageName();

			if (!startImgName.empty() && !endImgName.empty()) {
				int startIdx = CEGUI::PropertyHelper::stringToInt(startImgName);
				int endIdx = CEGUI::PropertyHelper::stringToInt(endImgName);
				if (endIdx >= startIdx) {
					stImageSetInf inf(i, startIdx, endIdx);
					m_vecImageSetInf.push_back(inf);
				}
			}
		}
		else {
			break;
		}
	}
}

void EmotionManager::LoadAllEmotionInf()
{
	std::vector<int> vecAllID;
	GameTable::chat::GetCbiaoqingTableInstance().getAllID(vecAllID);
	for (size_t i = 0; i < vecAllID.size(); ++i) {
		int id = GameTable::chat::GetCbiaoqingTableInstance().getRecorder(vecAllID[i]).id;
		int totalFrame = GameTable::chat::GetCbiaoqingTableInstance().getRecorder(vecAllID[i]).imagenum;
		double dd = GameTable::chat::GetCbiaoqingTableInstance().getRecorder(vecAllID[i]).time;
		float duration = static_cast<float>(dd);
		std::wstring tips = GameTable::chat::GetCbiaoqingTableInstance().getRecorder(vecAllID[i]).tips;
		std::wstring accessKey = GameTable::chat::GetCbiaoqingTableInstance().getRecorder(vecAllID[i]).key;
		AddEmotion(id, totalFrame, duration, tips, accessKey);

		CEGUI::System::getSingleton().SetEmotionKey(CEGUI::PropertyHelper::stringToInt(ws2s(accessKey)));
	}
	CEGUI::System::getSingleton().SetEmotionNum(m_maxEmotionID);
}

stImageSetInf::stImageSetInf(int _id, int _startImage, int _endImage)
	:
	id(_id),
	startImage(_startImage),
	endImage(_endImage)
{ }
