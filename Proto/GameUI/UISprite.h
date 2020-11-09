#pragma once
#include "ComponentsObject.h"

struct stUISpriteHandle
{
	Nuclear::EngineSpriteHandle handle;
	bool	baction;
	stUISpriteHandle();
};

////�ɱ�װ�ľ���
class UISprite
{
public:
	UISprite(int model, bool haveshadow = false);
	virtual ~UISprite();

public:
	Nuclear::EngineSpriteHandle GetSprite();

	Nuclear::ISprite* GetSpritePtr();

	void DeleteComponent(eSpriteComponentType type);		//ɾ��ĳ�����

	void DeleteViceWeaponSprite();
	bool IsCharacterModel();

public:
	void RenderUISprite();
	void SetDefaultAction(eActionType type);
	int	 GetModelID();
	void SetModel(const int& modelid, bool haveshadow = false);

	void SetUISpriteComponentByShapeID(const int& shapeid);
	const Nuclear::NuclearLocation& GetUILocation();

	void SetUIAlpha(unsigned char alpha);
	void SetUIScale(const float& scale);
	void SetUIDirection(const Nuclear::NuclearLocation& target);
	void SetUIDirection(const Nuclear::NuclearDirection& dir);
	void SetUIRotationSpeed(float speed);	//����ת���ٶ�
	void SetUILocation(const Nuclear::NuclearLocation& loc);

	void UpdateSpriteComponent(const ComponentInfoMap& components);//���ݷ������������Ļ�װmapֵˢ������Components

	void RemoveSpriteComponent();					//ɾ�����������m_ComponentInfo��Ϣ��������ɫ������
	void ClearSpriteComponent();					//ɾ�������������Ҫ�ǰ�̯ʱ���ã�
	void ResetSpriteComponent();					//��ԭ�����������Ҫ�ǰ�̯ʱ���ã�

	void SetSpriteComponent(eSpriteComponentType type, int baseid);

	void RefreshSpriteComponent(const ComponentInfoMap& components);//ˢ��component�����ڶ���������ʱ
	int GetCurActDuration();
public:
	std::wstring GetComponentActionName(eActionType type);
	std::wstring GetActionName(eActionType type);
	void PlayAction(eActionType actionType, float freq = 1.0f);

public:
	void SetRandomAction(bool b);
	void Run(int now, int delta);

public:
	//��Ч���
	Nuclear::IEffect* SetEngineSpriteDurativeEffect(const std::wstring &effect_name, bool underSprite = false, unsigned int flag = Nuclear::XPSPREFFFLAG_ASYNC | Nuclear::XPSPREFFFLAG_NO_SOUND);
	Nuclear::IEffect* PlayUISpriteEffect(const std::wstring &effectname, int times = 1, unsigned int flag = Nuclear::XPSPREFFFLAG_ASYNC | Nuclear::XPSPREFFFLAG_NO_SOUND);
	void SetDyePartIndex(int part, int index);
	void RemoveEngineSpriteDurativeEffect(Nuclear::IEffect*pEffect);

private:
	void UpdateWeaponColorParticle(int weaponid);	//��������Ч��
	void refreshActionID();
private:
	Nuclear::IEffect*	m_pViceWeaponColorParticle;
	Nuclear::IEffect*	m_pWeaponColorParticle;
	int	m_iWeaponColor;
	int m_iActionID;
private:
	Nuclear::NuclearLocation m_UILocation;
	int m_iModelID;
	Nuclear::EngineSpriteHandle m_SpriteHandle;

	int m_CurActDuration;					//��ǰ�����Ĳ���ʱ��
	stUISpriteHandle m_ViceWeaponHandle;	//����˫����������������Ӧ��������һ��������������
	std::map<eSpriteComponentType, stUISpriteHandle>	m_ComponentHandleMap;

	ComponentInfoMap m_ComponentInfo;

private:
	Nuclear::IEffect* m_UISpriteShadow;

private:
	bool m_bRandomAction;
	int	 m_iRandomActionInterval;

private:
	bool m_bShowHead;
	bool m_bShowFace2;
	bool m_bShowFace1;
	bool m_bShowBack;
};
