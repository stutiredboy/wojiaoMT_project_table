/***********************************************************************
filename: 	IconManager.h
purpose:	��Ϸͼ�����(���ܼ�����ͼ��)
*************************************************************************/
#pragma once
#include "Singleton.hpp"

class IconManager : public CSingleton<IconManager>
{
public:
	IconManager();
	~IconManager();
	
	const CEGUI::String GetSkillIconPathByID(int id);   // ���ݼ��ܵ�id�������ͼ��ı�ʶ���� (imgeset+name),���򷵻ؿ��ַ���
	const CEGUI::String GetItemIconPathByID(int id);    // ���ݵ��ߵ�id�������ͼ��ı�ʶ���� (imgeset+name),���򷵻ؿ��ַ���
	const CEGUI::String GetImagePathByID(int id);

	const CEGUI::Image& GetTraceIcon();			//�õ�����׷�ٱ�־
	const CEGUI::Image* GetBuffIconByID(int id);	//����buff��id�������ͼ��,���򷵻�NULL
	const CEGUI::Image* GetSkillIconByID(int id);	//���ݼ��ܵ�id�������ͼ��,���򷵻�NULL
	const CEGUI::Image* GetItemIconByID(int id);	//���ݵ��ߵ�id�������ͼ��,���򷵻�NULL
	const CEGUI::Image* GetImageByID(int id);		//����ͼƬ��id���ͼƬ

	const CEGUI::Image& getDefaultIcon();

	// ���ݱ���Ļ�����ĵı�ʶ���� (imgeset+name),���򷵻ؿ��ַ��� 
	const CEGUI::Image* GetEmotionImageByFrame(int aniID, int frame);
	const CEGUI::String GetEmotionIconPathByFrame(int aniID, int frame);
private:

	//���ݳ�νID�õ�����Ӧ��ͼ
	CEGUI::String GetTitleIconPathByID(int titleID);

	void DestroyImageSet(const CEGUI::String& name); //����һ��imageset
	void CreateImageSet(const CEGUI::String& name);  //����һ��imageset

	CEGUI::String FindImageSetNameByID(int id);	//ͨ��IDѰ�����ڵ�imageset������,����Ҳ�������Ϊ��
	void InitIconInf();						//��ʼ��ͼ����Ϣ

	void AddCardImageSet();
	void AddTitleImageSet();

	void InitImagesetSizeInfo(std::vector<int>& vec, CEGUI::String prefix, int fromNum, int maxNum);
	
	typedef std::vector<CEGUI::String> IconImageSetList;
	typedef std::vector<CEGUI::String>::iterator IconImageSetListIt;
	typedef std::map<CEGUI::String, CEGUI::String> IconInfMap;
	typedef std::map<CEGUI::String, CEGUI::String>::iterator IconInfMapIt;

protected:
private:
	IconImageSetList m_vecIconImageSet;
	IconInfMap m_mapIconInfMap;
	const static int m_nItemIconSize=64;	//ÿһ��imageset�ĵ���ͼƬ��
	const static int m_nSkillIconSize=64;	//ÿһ��imageset�ļ���ͼƬ��
	const static int m_nBufferSize=16;		//ÿһ��imageset�ı���ͼƬ��
	const static int m_nRoleAndMonsterSize=128;
	const static int m_nRightTopRoleSize=84;
	const static int m_nRightTopPetSize=62;
	const static int m_nServentSize=72;
	const static int m_nRoleDlgHeadSize=153;
	const static int m_nSellPetIconSize=42; //��������ͼ���С
	
	const static int m_nImageSetSize=256;  //ÿһ��imageSet�Ĵ�
    
	std::vector<int> m_vecPetImagesetSize; //����ÿ��imageset���м���ͼ�꣬��Ŵ�0��ʼ by lg
};

inline IconManager* gGetIconManager()
{
	return IconManager::GetInstance();
}
