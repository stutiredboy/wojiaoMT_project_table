/***********************************************************************
filename: 	Dialog.h
purpose:	Defines the interface for the dialog
*************************************************************************/

#ifndef __DIALOG_HPP
#define __DIALOG_HPP

#include "CEGUIWindow.h"
#include "CEGUIWindowManager.h"
#include "CEGUISystem.h"
#include "SingletonDialog.h"
#include "elements/CEGUIPushButton.h"


#include "../Event.h"

namespace Nuclear
{
	class IEffect;
}

enum eDialogType
{
	eDialogType_Null = 0x00,
	eDialogType_TimeLimit = 0x01 << 0,		//�Ի�����������
	eDialogType_BattleClose = 0x01 << 1,	//��ս���ر�
	eDialogType_MoveClose = 0x01 << 2,		//�����ƶ��ر�
	eDialogType_RBtnClose = 0x01 << 3,		//�Ҽ��հ״��ر�
	eDialogType_MapChangeClose = 0x01 << 4,	//����ͼ�ر�
	eDialogType_ChatOutWnd = 0x01 << 5,		//�������촰���еĶԻ���
	eDialogType_SceneMovieWnd = 0x01 << 6,  //���������еĶԻ���
	eDialogType_InScreenCenter = 0x01 << 7, //��ʼ��ʱ���л��ֱ��ʺ���еĴ���
	eDialogType_ImmeDel = 0x01 << 8,		//����ɾ��ģʽ
	eDialogType_Max,
};

class Dialog
{
public:
    friend class GameUImanager;

public:
	Dialog();
	virtual ~Dialog();

	void OnCreate(CEGUI::Window* pParentWindow = NULL, const CEGUI::String& name_prefix = ""); //�����Ի���

	virtual void RemoveWindowEvent();//ֻ���Ƴ���Ϸ����½������ɫѡ�����ʱ����
	virtual void DestroyDialog() = 0;
	virtual void OnClose2(bool waitAnimAndEffect, bool ClearGameUIManager); //�رնԻ���
	virtual void OnClose(); //�رնԻ���

	virtual void SetVisible(bool bVisible);
	bool IsVisible(); //��ǰ�Ի����Ƿ�ɼ� true �ɼ���false ���ɼ�

	virtual void CheckDisTimerCallBack();

	virtual CEGUI::String GetLayoutFileName() = 0; //�õ����ضԻ��������layout�ļ���

	void SetCloseIsHide(bool bCloseIsHide);
	virtual void setEscClose(bool escclose);
	bool CloseIsHide();

	CEGUI::Window* GetWindow();

	CEGUI::PushButton* GetCloseBtn();

	bool HandleDialogClose(const CEGUI::EventArgs&); //����رջ������أ�������Ч�������ڴ�������ǰ���ã�
	bool HandleDialogOpen(const CEGUI::EventArgs&);  //�����

	static void OnEffectOver(Nuclear::IEffect* effect);
	static void OnTickAllDlg(unsigned int deltaTime);
	virtual bool HandleCloseEffectEnd(const CEGUI::EventArgs&);

	virtual bool HandleTimePast(const CEGUI::EventArgs&);
	virtual bool HandleRightButtonDown(const CEGUI::EventArgs&);
	virtual bool HandleCloseBtnClick(const CEGUI::EventArgs&);
    
	CEGUI::Window* m_pParentWindow;
	CEGUI::Window* m_pMainFrame;	 //�Ի����������
	int		m_eDialogType;
	bool    m_bEscClose;	 //�Ƿ�esc���˳�
	unsigned int   m_dwLife; //������
private:

	void OnDestroyAnimation(CEGUI::Window* wnd);
	void ReleaseDialog(bool ClearGameUIManager = true);
	void OnDestroyEffect(CEGUI::Window* wnd);
	bool OnCloseEffect(CEGUI::Window* wnd);//���û����Ч������������ʧ��.
	virtual void OnTick(unsigned int deltaTime);

	bool m_bRelease;
	unsigned int  m_dwCreatTime; //�Ի���Ĵ���ʱ��
	bool m_bCloseIsHide;	//�Ƿ����ؼ��ر�
	static Dialog* s_pTickingDlg;
	bool m_bCloseing;
	std::map<CEGUI::Window*, float> m_mapOnCloseAnimationNotify;
	float m_fElapseTime;
	static std::set<Dialog*> m_setDlgs;
	std::set<Nuclear::IEffect*> m_setOnCloseEffectNotify;
};

#endif
