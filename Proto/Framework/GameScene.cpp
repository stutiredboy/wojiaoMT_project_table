#include "stdafx.h"
#include "GameApplication.h"
#include "GameScene.h"
#include "MainCharacter.h"
#include "Pet.h"
#include "SceneNpc.h"
#include "FollowNpc.h"
#include "FossickNpc.h"
#include "MovieSceneNpc.h"
#include "DroptItem.h"
#include "MainRoleDataManager.h"
#include "BattleManager.h"
#include "BattleReplayManager.h"

#include "LoginManager.h"
//#include "fire/pb/move/SAddUserScreen.hpp"

//#include "../ProtoDef/fire/pb/move/SAddPickupScreen.hpp"

//#include "fire/pb/move/SRoleEnterScene.hpp"
//#include "Message/rpcgen/fire/pb/pet/PetState.hpp"


//#include "fire/pb/move/RoleBasicOctets.hpp"
//#include "fire/pb/move/ShowPetOctets.hpp"
//#include "fire/pb/move/TeamInfoOctets.hpp"
#include "NewRoleGuideManager.h"
#include "GameTable/message/CMessageTip.h"
#include "MessageManager.h"
#include "GameOperateState.h"
#include "rpcgen/fire/pb/npc/TransmitTypes.hpp"
#include "SceneMovieManager.h"
#include "fire/pb/mission/CMissionReachScene.hpp"
//#include "fire/pb/school/SShouxiShape.hpp"
#include "GameTable/EffectPath/CEffectPath.h"
#include "fire/pb/CAfterEnterWorld.hpp"
#include "GameUIManager.h"

#include "SimpleAudioEngine.h"
#include "ConfigManager.h"


#include "../ProtoDef/fire/pb/battle/newhand/CReqNewHandBattle.hpp"  // �ͻ�����������ս��

#include "nuiengine.h"
#include "engine/nuengine.h"
#include "utils/Utils.h"
#include "GameStateManager.h"
#include "../../../../engine/sprite/nusprite.h"

#ifdef ANDROID
#include "ChannelManager.h"
#include "Framework/DeviceInfo.h"
#elif defined(OS_IOS)
#include "ChannelManager.h"
#else
#endif
#include "MusicSoundVolumeMixer.h"



const int  s_iJumpMapFadeTime=300;	//��ת�黯ʱ�������
#define ContinueWalkDelay	1300	//��ת��ͼ���ӳ�800�����������

const int s_iToatalDreamFadeTime=4125;
const int s_iTotalDrawEnterMapNameTime=3000; //�ܵĽ����µ�ͼ������ʱ��
const int s_iTotalEnterMovieEffectTime=3000; //�ܵĽ��볡����������Ч��ʱ��

const int s_iNpcAutoPopoTimerCDTime=60;  //NPCð�ݵĶ�ʱ�����ʱ��,��λ��

void EnterDreamEffectNotify::OnEnd(Nuclear::IEffect *pEffect)
{
	if (pEffect)
	{
		pEffect->RemoveNotify(this);
		Nuclear::GetEngine()->ReleaseEffect(pEffect);
		gGetScene()->EmptyEnterDreamEffect();
		delete this;		//��������ڴ�й¶
	}
}
void EnterDreamEffectNotify::OnDelete(Nuclear::IEffect *pEffect)
{
	delete this;
}
//not move to lua
//void fire::pb::move::SRoleComponentsChange::Process(Manager *manager, Manager::Session::ID sid)
//{
//	if (gGetScene())
//	{
//		//0��ʾ��ɫ
//		if (spritetype == 0)
//		{
//			Character* pCharacter = gGetScene()->FindCharacterByID(roleid);
//			if (pCharacter)
//			{
//				pCharacter->UpdateSpriteComponent(components);
//                
//				if (pCharacter == GetMainCharacter())
//				{
//					cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeString("require 'logic.item.mainpackdlg'; if(CMainPackDlg:getInstanceOrNot())then CMainPackDlg:getInstanceOrNot():UpdataModel(); end");
//				}
//				else
//				{
//					pCharacter->CheckEquipEffect(components[eSprite_Effect]);
//				}
//				pCharacter->UpdateSpeed();
//				GetTeamManager()->UpdateMemberSpeed();
//			}
//		}
//		//1��ʾ��npc
//		else if (spritetype == 1)
//		{
//			Npc* pNpc = gGetScene()->FindNpcByID(roleid);
//			if (pNpc)
//			{
//				pNpc->UpdateSpriteComponent(components);
//			}
//		}
//	}
//}


//��ӵ�ͼ��ɫ��npc��Ϣ
//not move to lua
//void fire::pb::move::SAddUserScreen::Process(Manager * manager, Manager::Session::ID sid )
//{
//	if (NULL == gGetScene())
//	{
//		return;
//	}
//    
//	if (!rolelist.empty())
//	{
//		for (std::list<fire::pb::move::RoleBasic>::iterator iter = rolelist.begin();iter != rolelist.end();iter++)
//		{
//			fire::pb::move::RoleBasicOctets baseOctets;
//			FireNet::Marshal::OctetsStream octetSt(iter->rolebasicoctets);
//			baseOctets.unmarshal(octetSt);
//            
//			stCharacterData data;
//			data.dwID = baseOctets.roleid;
//			data.strName =  baseOctets.rolename;
//			data.ptPos = Nuclear::NuclearLocation(iter->pos.x,iter->pos.y);
//			data.dir = Nuclear::NuclearDirection((baseOctets.dirandschool & 0xF0)>>4);
//			data.eSchool = 	(eSchoolType)((baseOctets.dirandschool & 0x0F)+10);
//            data.level = baseOctets.level;
//			if(baseOctets.shape <=10)
//				data.shape = 1010100+baseOctets.shape;
//			else if(baseOctets.shape <300)
//				data.shape = 2010100+baseOctets.shape%100;
//			else
//				data.shape = baseOctets.shape;
//            data.camp = baseOctets.camp;
//			stMapPetData mapPetData;
//			mapPetData.roleid = baseOctets.roleid;
//			mapPetData.showpetid = 0;
//			for (std::map<char,FireNet::Octets>::iterator it=baseOctets.datas.begin();it!=baseOctets.datas.end();it++)
//			{
//				switch(it->first)
//				{
//					case fire::pb::move::RoleBasicOctets::SHOW_PET:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						fire::pb::move::ShowPetOctets petinfo;
//						petinfo.unmarshal(stream);
//						
//						mapPetData.showpetid = petinfo.showpetid;
//						mapPetData.showpetname = petinfo.showpetname;
//						mapPetData.showpetcolour = ePetColour(petinfo.petcoloursndsize>>4);
//						mapPetData.level = petinfo.petcoloursndsize&0x0f;
//						mapPetData.showskilleffect = petinfo.showskilleffect;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::TEAM_INFO:			//������Ϣ
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						fire::pb::move::TeamInfoOctets teaminfo;
//						teaminfo.unmarshal(stream);
//						data.teamID = teaminfo.teamid;
//						data.teamindex = (int)((teaminfo.teamindexstate & 0xF0) >>4);
//						data.teamstate = (int)(teaminfo.teamindexstate & 0x0F);
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::TITLE_ID:			//��νID
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int titleid = 0;
//						stream >> titleid;
//						data.TitleID = (int)titleid;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::TITLE_NAME:		//��νstring
//					{
						//FireNet::Marshal::OctetsStream stream(it->second);
						//FireNet::Octets oct;
						//stream >> oct ;
						//std::wstring titlename;

      //                  titlename.reserve(oct.size()/2);
      //                  typedef unsigned short utf16;
      //                  for(utf16* ch = (utf16*)oct.begin(); ch != oct.end(); ch++)
      //                  {
      //                      titlename.insert(titlename.end(), (wchar_t)*ch);
      //                  }
      //                  
						//data.strTitle = titlename;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::STALL_NAME:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						FireNet::Octets oct;
//						stream >> oct ;
//						std::wstring stallname;
//						FireNet::remove_const(stallname).assign((wchar_t*)oct.begin(),(wchar_t*)oct.end());
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::SCENE_STATE:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int state = 0;
//						stream >> state;
//						data.characterstate = state;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::ROLE_ACTUALLY_SHAPE:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int actuallyshape = 0;
//						stream >> actuallyshape;
//						data.actuallyshape = actuallyshape;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::PLAYING_ACTION:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						BYTE action = 0;
//						stream >> action;
//						data.actiondefault = action;
//					}
//                        break;
//                    case fire::pb::move::RoleBasicOctets::FOOT_LOGO_ID:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int footprintid = 0;
//						stream >> footprintid;
//						data.footprint = footprintid;
//					}
//                        break;
//					case fire::pb::move::RoleBasicOctets::CRUISE:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int automovepathid = 0;
//						stream >> automovepathid;
//						data.automovepathid = automovepathid;
//					}
//					break;
//					case fire::pb::move::RoleBasicOctets::EFFECT_EQUIP:
//					{
//						FireNet::Marshal::OctetsStream stream(it->second);
//						int equipEffect = 0;
//						stream >> equipEffect;
//						data.equipEffect = equipEffect;
//					}
//						break;
//						
//                    default:
//                        break;
//				}
//			}
//			//Ѱ·���
//			if (!iter->poses.empty())
//			{
//				//������ͨѰ·
//				if (iter->poses.size() == 1)
//				{
//					std::list<fire::pb::move::Pos>::iterator it=iter->poses.begin();
//					data.ptTargetPos = Nuclear::NuclearLocation(it->x,it->y);
//				}
//			}
//			else
//			{
//				data.ptTargetPos = data.ptPos;
//			}
//
//			//�ڵ�ͼ�ĵڼ��㣬falseΪ��һ�㣬trueΪ�ڶ���
//			data.bhighlevel = iter->posz == 1;
//			Character*pCharacter = gGetScene()->AddSceneCharacter(&data);
//            
//			if (pCharacter)
//			{                
//				//��װ���
//				pCharacter->UpdateSpriteComponent(baseOctets.components);
//
//				if (data.automovepathid > 0)
//				{
//					std::wstring RideName = pCharacter->GetAutoMoveRideName(data.automovepathid, gGetScene()->GetMapID());
//					pCharacter->SetSpriteComponent(eSprite_Horse, StringCover::WStrToNum<int>(RideName));
//					float MoveSpeed = pCharacter->GetAutoMoveSpeed(data.automovepathid, gGetScene()->GetMapID());
//					pCharacter->GetSprite()->SetMoveSpeed(MoveSpeed);
//					pCharacter->SetAutoMove(1);
//				}
//				else
//				{
//					pCharacter->GetSprite()->SetMoveSpeed(g_moveSpeed / 1000);
//					pCharacter->SetAutoMove(0);
//				}
//				pCharacter->UpdateSpeed();
//				GetTeamManager()->UpdateMemberSpeed();
//
//			}
//			if (mapPetData.showpetid != 0)
//			{
//				gGetScene()->AddScenePet(mapPetData);
//			}
//		}
//        if (GetMainCharacter())
//        {
//            GetMainCharacter()->HandleEnterOrLeavePVPArea();
//            cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.EnterLeavePVPArea");
//        }
//	}
//    
//	if (!npclist.empty())
//	{
//		for (std::list<fire::pb::move::NpcBasic>::iterator iter = npclist.begin();iter != npclist.end();iter++)
//		{
//			stNpcData data;
//			data.NpcID = iter->npckey;
//			data.NpcBaseID = iter->id;
//			data.strName = iter->name;
//			data.ptPos = Nuclear::NuclearLocation(iter->pos.x,iter->pos.y);
//			data.destPos = Nuclear::NuclearLocation(iter->destpos.x, iter->destpos.y);
//			data.moveSpeed = iter->speed;
//			data.dir = Nuclear::NuclearDirection(iter->dir);
//			data.ShapeID = iter->shape;
//			data.bHighlevel = iter->posz == 1;
//
//			bool bXinMo = false;
//			const GameTable::npc::CNPCConfig& npcTable = GameTable::npc::GetCNPCConfigTableInstance().getRecorder(data.NpcBaseID);
//			if (npcTable.id != -1)
//			{
//				if (npcTable.npctype == 27) //27 xinmo lei xing
//				{
//					bXinMo = true;
//				}
//			}
//			if (bXinMo)
//			{
//				fire::pb::move::NpcBasic npcData = *iter;
//
//				gGetScene()->AddMainCharacterNpc(npcData);
//
//			}
//			else
//			{
//				Npc* pNpc= gGetScene()->AddSceneNpc(&data);
//				if (pNpc)
//				{
//					pNpc->UpdateSpriteComponent(iter->components);
//				}
//			}
//		}
//	}
//	if (GetMainCharacter())
//	{
//		GetMainCharacter()->CheckGoto();
//	}
//}
    
std::wstring GameScene::GetTitleName(FireNet::Marshal::OctetsStream stream)
{
	FireNet::Octets oct;
	stream >> oct;
	std::wstring titlename;

	titlename.reserve(oct.size() / 2);
	typedef unsigned short utf16;
	for (utf16* ch = (utf16*)oct.begin(); ch != oct.end(); ch++)
	{
		titlename.insert(titlename.end(), (wchar_t)*ch);
	}

	return titlename;
}

void GameScene::AddScenePetData(int64_t roleid, int showpetid, std::wstring showpetname, char colour, char size, char showeffect)
{
	stMapPetData mapPetData;
	mapPetData.roleid = roleid;
	mapPetData.showpetid = showpetid;
	mapPetData.showpetname = showpetname;
	mapPetData.showpetcolour = ePetColour(colour);
	mapPetData.level = size;
	mapPetData.showskilleffect = showeffect;
	gGetScene()->AddScenePet(mapPetData);

}



//�����ͼ��Ϣ
//not move to lua
//void fire::pb::move::SRoleEnterScene::Process(Manager * manager, Manager::Session::ID sid )
//{
//	if (NULL == gGetScene())
//	{
//		return;
//	}
//
	//// �����У������õ�ͼ
	//if (SceneMovieManager::GetInstance() && SceneMovieManager::GetInstance()->isOnSceneMovie())
	//{
	//	return;
	//}
//
//	if (gGetGameApplication()->isReconnecting() && GetBattleManager() && GetBattleManager()->IsInBattle())
//	{
//		GetBattleManager()->EndBattleScene();
//	}
//	
//	GetBattleReplayManager()->Clear();
//    
//    gGetGameApplication()->SetWaitForEnterWorldState(false);
//    
//	gGetScene()->ChangeMap(this->sceneid,Nuclear::NuclearLocation(this->destpos.x,this->destpos.y),this->ownername,changetype,this->destz == 1);
//    
//#ifdef _LOCOJOY_SDK_
//#ifdef ANDROID
//	MT3::ChannelManager::onLogin_sta();
//#else
//    MT3::ChannelManager::onLogin_sta();
//#endif
//#endif
//}

//not move to lua
//void fire::pb::move::SAddPickupScreen::Process(aio::Protocol::Manager *, aio::Protocol::Manager::Session::ID)
//{
//	if (NULL == gGetScene())
//	{
//		return;
//	}
//	for (std::list<fire::pb::move::PickUpItem>::const_iterator iter = pickuplist.begin();iter != pickuplist.end();iter++)
//	{
//		gGetScene()->AddSceneDroptItem((*iter));
//	}
//}


//not move to lua
//void fire::pb::school::SShouxiShape::Process(Manager *, Manager::Session::ID)
//{
//	if (NULL == gGetScene())
//	{
//		return;
//	}
//	Npc* pNpc=gGetScene()->FindNpcByID(shouxikey);
//	if(pNpc)
//	{
//		pNpc->SetShouXiNewShapeAndName(shape,name,components);
//	}
//}


//GameScene���Timer
void GameSceneTimer::OnTimer()
{
	switch(m_TimerType)
	{
        case eGSTimerType_GiveServantTips:
		{
		}
            break;
        case eGSTimerType_MovieMapChange:
		{
			CancelSchedule();
		}
            break;
        case eGSTimerType_MapChangeRun:
		{
			gGetScene()->SetChangeMapForbidRun(false);
			//��ת��ͼ0.5s֮���������Ѱ·
			GetMainCharacter()->m_MapWalker.CrossGoTo();	//�����������Կ�
			CancelSchedule();
		}
            break;
        case eGSTimerType_EnterDreamRun:
		{
			if (gGetScene()->isOnDreamFade()&&gGetScene()->isOnDreamScene())
			{
				gGetScene()->BeginDreamFade();
				gGetScene()->SetDreamFadeTime(s_iToatalDreamFadeTime);
			}
		}
            break;
        case eGSTimerType_EndHideQuest:
		{
		}
            break;
        case eGSTimerType_MoneyOverLimit:
		{
		}
            break;
        case eGSTimerType_MapChangeDrawName:
		{
		}
            break;
        case eGSTimerType_ExistEquipReplace://�˳�װ���滻����
		{
		}
            break;
        case eGSTimerType_WeeHours:		// ����������
		{
		}
            break;
        case eGSTimerType_AvoidCreepBuffTip:		 //�Ի���bufferʣ��������ʱ ������ʾ
		{
		}
            break;
        case eGSTimerType_NpcAutoPopoStart:
		{
			if (gGetScene())
			{
				gGetScene()->StartNpcAutoPopoTimer();
			}
		}
            break;
        case eGSTimerType_NpcAutoPopoRun:
		{
			if (gGetScene())
			{
				gGetScene()->CheckNpcAutoPopo();
			}
		}
            break;
        case eGSTimerType_F9TipsRun:
		{
		}
            break;
        default:
            break;
	}
}

GameSceneTimer::GameSceneTimer()
	:m_TimerType(eGSTimerType_TimerNull)
{ }

GameSceneTimer::~GameSceneTimer()
{
	Nuclear::GetEngine()->CancelTimer(this);
}

bool GameSceneTimer::SetSchedule(eGameSceneTimerType type, int cdtime)
{
	m_TimerType = type;
	return Nuclear::GetEngine()->ScheduleTimer(this, cdtime);
}

void GameSceneTimer::CancelSchedule()
{
	m_TimerType = eGSTimerType_TimerNull;
	Nuclear::GetEngine()->CancelTimer(this);
}

GameScene::GameScene()
: m_pMouseOverObjects(NULL)
, m_bShieldCharacter(false)
, m_iJumpMapFadePicHandle(Nuclear::INVALID_PICTURE_HANDLE)
, m_ChangeMapPictureHandle(Nuclear::INVALID_PICTURE_HANDLE)
, m_bMapJumping(false)
, m_bLoadMaping(false)
, m_iFadeElapseTime(0)
, m_bIsLoadMapFrame(false)
, m_MapDataName(L"")
, m_MapDataID(0)
, m_DreamStatus(0)
, m_pOnDreamEffect(NULL)
, m_pEnterDreamEffect(NULL)
, m_iDreamFadeElapseTime(0)
, m_bIsInDreamFade(false)
, m_iDreamTotalFadeTime(3000)
, m_iDreamHideSceneTime(2500)
, m_bIsOnDrawEnterMapNameEffect(false)
, m_iEnterMapElapseTime(0)
, m_iEnterMapNameEffect(Nuclear::INVALID_PICTURE_HANDLE)
, m_MapSceneID(0)
, m_LastChangeMapPicID(-1)
, m_iLoadMapProgress(0)
, m_bEnbaleJumpMapFadeEffect(false)
, m_pFinishQuestEffect(NULL)
, m_bChangeMapForbidRun(false)
, m_pUndeadSceneFogEffect(NULL)
, m_lastmonsterindex(0)
, m_bFirstEnterScene(false)
, m_pLeftTower1(NULL)
, m_pLeftTower2(NULL)
, m_pRightTower1(NULL)
, m_pRightTower2(NULL)
, m_bStartNpcAutoPopoTimer(false)
, m_fStartNpcAutoPopoTimer(0.0f)
, m_bNpcAutoPopoTimer(false)
, m_fNpcAutoPopoTimer(0.0f)
, m_pFirstEnterBlackEffect(NULL)
, m_nNotTransparentManNum(0)
, m_nFactionBossShapeID(-1)
, m_nFactionBossBaseID(-1)
, m_iMovieCapturePic(Nuclear::INVALID_PICTURE_HANDLE)
, m_bJumpMapForAutoBattle(false)
, isFirstJuqingPlayed(false)
, jumpMapId1(0)
, jumpMapId2(0)
, m_bIsShaking(false)
, m_nLastShakeTime(0)
, m_nShakeBetweenTime(0)
, m_nShakeRange(0)
, m_nShakeEndTime(0)
, m_nShakeID(0)
, m_bJunmPointEffectShow(true)
, m_MapInfoId(0)
{
	jumpPoint1 = Nuclear::NuclearLocation(-10, -10);
	jumpPoint2 = Nuclear::NuclearLocation(-10, -10);
	jumpToPoint2 = Nuclear::NuclearLocation(-10, -10);
	jumpToPoint1 = Nuclear::NuclearLocation(-10, -10);
	Nuclear::GetEngine()->GetWorld()->SetCameraUpdateType(Nuclear::XPCAMERA_UPDATE_TYPE2);
	setSceneEffect();
	c_iBingfengMapIDBeg = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithStringData("GetNumberValueForStrKey", "BINGFENG_MAPID_BEGIN");
	c_iBingfengMapIDEnd = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithStringData("GetNumberValueForStrKey", "BINGFENG_MAPID_END");
	m_vecJumpPointEffect.clear();
}

GameScene::~GameScene()
{
	if (gGetGameApplication()->isReconnecting() && GetBattleManager() && GetBattleManager()->IsInBattle())
	{
		GetBattleManager()->EndBattleScene();//�����ս�����Ƚ���ս��
	}
    
	ReleaseFinishQuestEffect();
    
	ReleaseAllJumpPointEffect();
	Nuclear::GetEngine()->GetWorld()->SetWorldMode(Nuclear::XPWM_NORMAL);
	ClearScene();
	MainCharacter::RemoveInstance();
	m_SceneSprite[eSceneObjCharacter].clear();
    
	Nuclear::GetEngine()->GetWorld()->UnloadMap();
    
	EndJumpMap();
	if (m_pEnterDreamEffect!=NULL)
	{
		Nuclear::GetEngine()->ReleaseEffect(m_pEnterDreamEffect);
		m_pEnterDreamEffect = NULL;
	}
	if (m_pOnDreamEffect!=NULL)
	{
		Nuclear::GetEngine()->ReleaseEffect(m_pOnDreamEffect);
		m_pOnDreamEffect = NULL;
	}
	EndDrawEnterMapNameEffect();
	ClearSceneEffect();
	m_pFirstEnterBlackEffect=NULL;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
	ReleaseMovieCapturePic();

}

void GameScene::setSceneEffect()
{
	bool playEffect = gGetGameConfigManager()->GetConfigValue(L"sceneeffect") > 0 ? true : false;
	Nuclear::GetEngine()->GetWorld()->showSceneEffects(playEffect);
}

//���GameScene������
void GameScene::ClearScene()
{
	ReleaseAllJumpPointEffect();
	//���������ʱ��Ч
	m_SpecialSceneEffectList.clear();
	//�������npc
	if (GetSceneNpcManager())
	{
		GetSceneNpcManager()->ClearSceneNpc();
	}
    
	if (m_pUndeadSceneFogEffect)
	{
		Nuclear::GetEngine()->GetWorld()->RemoveEffect(m_pUndeadSceneFogEffect);
		m_pUndeadSceneFogEffect = NULL;
	}
	//��տͻ����Լ����صĵ�ͼnpc��Ϣ
	m_ClientNpcMap.clear();
    
	m_MapDataID = 0;
	m_MapDataName = L"";
	for (size_t type = eSceneObjItem;type<eSceneObjMax;type++)
	{
		RemoveSceneObject((eSceneObjType)type);
	}
	ClearMouseOverObjects();
	m_nNotTransparentManNum=0;
}

//ɾ��������λ
void GameScene::RemoveSceneObject(eSceneObjType type)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[type].begin();itor != m_SceneSprite[type].end();)
	{
		if (itor->second == GetMainCharacter())
		{
			itor++;
			continue;
		}
		else
		{
			delete itor->second;
			itor->second = NULL;
            m_SceneSprite[type].erase(itor++);
		}
	}
	if (type==eSceneObjCharacter)
	{
		m_nNotTransparentManNum=0;
	}
}

//ͨ��npcbaseid�ҵ�Npc
Npc* GameScene::FindNpcByBaseID(int npcbaseID)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end(); itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if(pNpc->GetNpcBaseID() == npcbaseID)
			return pNpc;
	}
	return NULL;
}

//ͨ��ID�ҵ�Npc
Npc* GameScene::FindNpcByID(int64_t npcID)
{
	SceneObjMap::iterator it= m_SceneSprite[eSceneObjNpc].find(npcID);
	if (it != m_SceneSprite[eSceneObjNpc].end())
	{
		return static_cast<Npc*>(it->second);
	}
	return NULL;
}

CScenePuppy* GameScene::FindPuppyByID(int64_t id)
{
	return NULL;
}

//ͨ��ID�ҵ���ɫ
Character*	GameScene::FindCharacterByID(int64_t characterID)
{
	SceneObjMap::iterator it= m_SceneSprite[eSceneObjCharacter].find(characterID);
	if (it != m_SceneSprite[eSceneObjCharacter].end())
	{
		return static_cast<Character*>(it->second);
	}
	return NULL;
}

int GameScene::GetNotTransparentManNum()
{
	return m_nNotTransparentManNum;
}

void GameScene::ClearMouseOverObjects()
{
	m_pMouseOverObjects = NULL; m_MouseOverObjectsList.clear();
}

//��ĳ����ɫɾ��ʱ��������������Ľ�ɫClearTeamFollower();
void GameScene::ClearTeamFollowWhileCharacterDelete(Character* pCharacter)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		Character* pChar = static_cast<Character*>(itor->second);
		if (pChar && pChar->GetTeamFollow() == pCharacter)
		{
			pChar->ClearTeamFollower();
		}
	}
}

//ͨ������ID������ҵ���ɫ
Character*	GameScene::FindCharacterByTeamIDandIndex(int64_t teamID,int index)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		Character* pChar = static_cast<Character*>(itor->second);
		if (pChar && !pChar->IsTeamInfoOutOfDate() && pChar->GetTeamID() == teamID && pChar->GetTeamIndex() == index)
			return pChar;
	}
	return NULL;
}

FollowNpc*	GameScene::FindFollowNpcByIndex(int nNumber)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjFollowNpc].begin(); itor != m_SceneSprite[eSceneObjFollowNpc].end(); itor++)
	{
		FollowNpc* pNpc = static_cast<FollowNpc*>(itor->second);
		if (pNpc  && pNpc->GetFollowNumber() == nNumber)
			return pNpc;
	}
	return NULL;
}

void GameScene::RefreshFollowNpcDistance()
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjFollowNpc].begin(); itor != m_SceneSprite[eSceneObjFollowNpc].end(); itor++)
	{
		FollowNpc* pNpc = static_cast<FollowNpc*>(itor->second);
		if (pNpc)
			pNpc->refreshDistance();
	}
}

size_t GameScene::GetCharacterNum()
{
	return m_SceneSprite[eSceneObjCharacter].size();
}

//ͨ������ID�ҵ�����
ScenePet*	GameScene::FindPetByMasterID(int64_t masterID)
{
	SceneObjMap::iterator it= m_SceneSprite[eSceneObjPet].find(masterID);
	if (it != m_SceneSprite[eSceneObjPet].end())
	{
		return static_cast<ScenePet*>(it->second);
	}
	return NULL;
}

DroptItem* GameScene::FindSceneItemByID(int64_t itemID)
{
    SceneObjMap::iterator it= m_SceneSprite[eSceneObjItem].find(itemID);
    if (it != m_SceneSprite[eSceneObjItem].end())
    {
    	return static_cast<DroptItem*>(it->second);
    }
	return NULL;
}

//ɾ��NPC
void GameScene::RemoveNpcByID(int64_t npcID)
{
	RemoveSceneObjectByID(eSceneObjNpc, npcID);
}

//ɾ��Character
void GameScene::RemoveCharacterByID(int64_t characterID)
{
	if (GetMainRoleDataNumValue<int64_t>("roleid") != characterID)
	{
		RemoveSceneObjectByID(eSceneObjCharacter, characterID);
	}
}

//ɾ����ͼ�ϳ���
void GameScene::RemovePetByMasterID(int64_t masterID)
{
	RemoveSceneObjectByID(eSceneObjPet,masterID);
}

void GameScene::RemoveSceneObjectByID(eSceneObjType type,int64_t id)
{
	SceneObjMap::iterator it= m_SceneSprite[type].find(id);
    
	if (it != m_SceneSprite[type].end())
	{

		OnSceneObjectRemove(it->second);

		delete it->second;
		it->second = NULL;
		m_SceneSprite[type].erase(it);
	}
}

Npc* GameScene::AddSceneNpc(stNpcData* pData)
{
	if (pData->NpcBaseID == m_nFactionBossBaseID)
	{
		pData->ShapeID = m_nFactionBossShapeID;
	}

	Npc* pNpc = FindNpcByID(pData->NpcID);
	if (pNpc != NULL)
	{
		pNpc->SetAttribute(pData);
	}
	else
	{
		pNpc = new Npc();
		if(pNpc == NULL)
			return NULL;
        
		if (pNpc->SetAttribute(pData))
			m_SceneSprite[eSceneObjNpc][pData->NpcID] = pNpc;
		else
		{
			delete pNpc;
			pNpc = NULL;
		}
	}
    
	if(pNpc)
	{
		// ����npcԭ������
        eNpcMissionState state = GetNpcStateByID(pData->NpcID,pData->NpcBaseID);
        pNpc->SetQuestState(state);

		int nNpcId = pData->NpcBaseID;
		int npcTableid = GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "id");
		if (npcTableid != -1)
		{
			if (pNpc->IsAction(eActionDeath) == false)
			{
				int nState = eActionStand;
				if (GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "nstate") > 0)
				{
					nState = GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "nstate");
				}
				if (nState == eActionDeath)
				{
					pNpc->SetDefaultAction(eActionType(eActionDeath), true);
				}
				else
				{
					pNpc->SetDefaultAction(eActionType(nState));
				}
			}
		}
	}
    
	if (gGetSceneMovieManager() && gGetSceneMovieManager()->isOnSceneMovie())
	{
		if (pNpc&&pNpc->GetSceneObjectType() != eSceneObjMovie)
		{
			pNpc->SetVisible(false);
		}
	}

    cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("LuaAddSenceNpc", pData->NpcBaseID, pData->NpcID);
	return pNpc;
}


bool GameScene::AddMainCharacterNpc(fire::pb::move::NpcBasic npcData)
{
	if (!GetMainCharacter())
		return false;

	stNpcData data;
	data.NpcID = npcData.npckey;
	data.NpcBaseID = npcData.id;
	data.strName = GetMainCharacter()->GetName()+ npcData.name;
	data.ptPos = Nuclear::NuclearLocation(npcData.pos.x, npcData.pos.y);
	data.destPos = Nuclear::NuclearLocation(npcData.destpos.x, npcData.destpos.y);
	data.moveSpeed = npcData.speed;
	data.dir = Nuclear::NuclearDirection(npcData.dir);
	data.ShapeID = npcData.shape;
	data.bHighlevel = npcData.posz == 1;
	data.scenestate = npcData.scenestate;
	data.ShapeID = GetMainCharacter()->GetShapeID();

	const std::map<char, int>& compon = GetMainCharacter()->GetComponentInfo();
	npcData.components = compon;


	Npc* pNpc = gGetScene()->AddSceneNpc(&data);
	if (pNpc)
	{
		pNpc->UpdateSpriteComponent(npcData.components);
	}
	return true;

}



bool GameScene::AddSceneFossickNpc(stNpcData* pData)
{
	FossickNpc* pFossickNpc = static_cast<FossickNpc*>(FindNpcByID(pData->NpcID));
	if (pFossickNpc != NULL)
	{
		pFossickNpc->SetAttribute(pData);
	}
	else
	{
		pFossickNpc = new FossickNpc();
		if(pFossickNpc == NULL)
			return false;
        
		if (pFossickNpc->SetAttribute(pData))
			m_SceneSprite[eSceneObjNpc][pData->NpcID] = pFossickNpc;
		else
		{
			delete pFossickNpc;
			pFossickNpc = NULL;
		}
	}
    
 	if(pFossickNpc)
 	{
 		eNpcMissionState state = GetNpcStateByID(pData->NpcID,pData->NpcBaseID);
 		pFossickNpc->SetQuestState(state);
 	}
    
	return true;
}

/////////������/////
Character* GameScene::AddSceneCharacter(stCharacterData* pData)
{
	if (pData)
	{
		Character* pExistCharacter=FindCharacterByID(pData->dwID);
		if (pExistCharacter)
		{
			if (pExistCharacter)
			{
				pExistCharacter->SetAttribute(pData);
				if (gGetSceneMovieManager() && gGetSceneMovieManager()->isOnSceneMovie())
				{
					pExistCharacter->SetVisible(false);
				}
			}
			return pExistCharacter;
		}
		else
		{
			Character* pCharacter = new Character();
            
			
			pCharacter->SetAttribute(pData);
            
			m_SceneSprite[eSceneObjCharacter][pData->dwID] = pCharacter;
			if (pCharacter->GetTeamID() == GetMainCharacter()->GetTeamID()
                && pCharacter->GetTeamIndex() == GetMainCharacter()->GetTeamIndex() - 1)
			{
				GetMainCharacter()->SetTeamFollow();	//���б�Ҫ�����¸���ӳ�
			}
			pCharacter->SetTeamInfoOutOfDate(false);
			pCharacter->SetVisible(!m_bShieldCharacter);

			pCharacter->CheckEquipEffect(pData->equipEffect);
            
			if (gGetSceneMovieManager() && gGetSceneMovieManager()->isOnSceneMovie())
			{
				pCharacter->SetVisible(false);
			}
			return pCharacter;
		}
	}
	else
		return NULL;
}

//������ǣ�������Ϸ���� �ú�������Ϸ�˳�ǰӦ��ֻ��ִ��һ��
bool GameScene::AddMainCharacter(int64_t roleid, int sex, int shape, int camp)
{
	GetBattleManager()->EventBeginBattle += CBroadcastEvent<NoParam>::EventBind(this,&GameScene::OnBattleBegin);
	GetBattleManager()->EventEndBattle += CBroadcastEvent<NoParam>::EventBind(this,&GameScene::OnBattleEnd);
	if (Nuclear::GetEngine()->GetWorld())
	{
		MainCharacter::sPurgeData();
		MainCharacter::NewInstance();
		m_SceneSprite[eSceneObjCharacter][roleid] = GetMainCharacter();
        
		GetMainCharacter()->SetAttribute(roleid, sex, shape, camp);
		GetMainCharacter()->UpdataTitleTexture();
		GetMainCharacter()->UpdatNameTexture(true);
        
		if (GetMainCharacter()->GetSprite())
		{
			GetMainCharacter()->GetSprite()->SetUpdateEveryFrame(true);

			GetMainCharacter()->StopAutoMove();
		}

		Nuclear::GetEngine()->GetWorld()->SetFlyOffsetYStep(0);
		Nuclear::GetEngine()->GetWorld()->SetFlyOffsetYTgt(0);
		Nuclear::GetEngine()->GetWorld()->SetFlyOffsetYCur(0);
		Nuclear::GetEngine()->GetWorld()->SetScale(1.0f);
        
		return true;
	}
	return false;
}

/////////��ӳ�������/////
bool GameScene::AddScenePet(const stMapPetData& petData)
{
	ScenePet* pPet = FindPetByMasterID(petData.roleid);
	if (pPet)
	{
		pPet->SetAttribute(petData);
	}
	else
	{
		pPet = new ScenePet();
        
		bool bIsTransparent=false;
		int64_t ownerID=petData.roleid;
		if (ownerID != GetMainRoleDataNumValue<int64_t>("roleid"))
		{
			Character* pChar=FindCharacterByID(ownerID);
		}
        if (pPet->SetAttribute(petData))
        {
            m_SceneSprite[eSceneObjPet][petData.roleid] = pPet;
            //��������Լ��ĳ���
			if (ownerID != GetMainRoleDataNumValue<int64_t>("roleid"))
            {
                pPet->SetVisible(!m_bShieldCharacter);
            }
        }
	}
	return true;
}

bool GameScene::AddSceneDroptItem(const fire::pb::move::PickUpItem& data)
{
	if (FindSceneItemByID(data.uniqueid))
	{
		return false;
	}
	else
	{
		DroptItem* pSenceItem = new DroptItem();
		if(pSenceItem && pSenceItem->SetAttribute(data))
		{
			m_SceneSprite[eSceneObjItem][data.uniqueid] = pSenceItem;
			if (gGetSceneMovieManager() && gGetSceneMovieManager()->isOnSceneMovie())
			{
				pSenceItem->SetVisible(false);
			}
		}
		else if(pSenceItem)
		{
			delete pSenceItem;
		}

	}
	return true;
}

/////////��Ӹ���npc/////
bool GameScene::AddSceneFollowNpc(const int& basedata, int nNum)
{    
	FollowNpc* pFollowNpc = new FollowNpc();
	if (pFollowNpc && pFollowNpc->Init(basedata, nNum, basedata))
	{
		int64_t npcid = static_cast<int64_t>(basedata);
		m_SceneSprite[eSceneObjFollowNpc][npcid] = pFollowNpc;

		//����3D��Ч
		bool bindType = false;
		int nX = 0;
		int nY = 0;

		Nuclear::Sprite* pSprite = (Nuclear::Sprite*)pFollowNpc->GetSprite();
		if (!pSprite) {
			return false;
		}

		int nEffectId = 11049;
		std::wstring strPath =  MHSD_UTILS::GetEffectPath(nEffectId);//L"geffect/ui/mt_gensui";
		pFollowNpc->SetDurativeEffect(strPath, bindType, nX, nY, false, false);

		if (gGetSceneMovieManager()&&gGetSceneMovieManager()->isOnSceneMovie())
		{
			pFollowNpc->SetVisible(false);
		}
	}
	else if(pFollowNpc)
	{
		delete pFollowNpc;
	}
	return true;
}

//�õ���ͼ����
std::wstring GameScene::GetMapName()
{
    
	if (m_MapDataName != L"")
	{
        return m_MapDataName;
	}
	else
	{

		return GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "mapName");
	}
}

//�ô�����С��ͼ��ʾ�ĵ�ͼ��
std::wstring GameScene::GetMapNameUsingInMiniMap()
{
    
	if (m_MapDataName != L"")
	{
        return m_MapDataName;
	}
	else
	{
		return GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "mapName");
	}
}

int GameScene::GetMapID()
{
	return m_MapInfoId;
}

//��ͼ��ת
bool GameScene::ChangeMap(int64_t sceneID,Nuclear::NuclearLocation ptLocation,std::wstring mapName,int changetype,bool highlevel)
{
#ifdef ANDROID
	//��ͼ��תʱ�Ƚ�����������(ֻ�е�Andorid4.0֮ǰ�İ汾���ڴ澯��ʱ�Ž���)//add by eagle
	if (DeviceInfo::sGetOSVersionCode() < 14)
		gGetGameApplication()->CollectingGCMemory();
#endif
	int pet_enter = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("fire_pb.Move_Lua_SRoleEnterScene_ENTER");
	int ret_gc = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("fire_pb.Move_Lua_SRoleEnterScene_QUEST_CG");
	if (changetype == pet_enter)
	{
		gGetGameApplication()->DrawLoginBar(21);
	}
	m_MapSceneID = sceneID;
	int mapID = (int)(sceneID & 0x00000000FFFFFFFF);
	int mapDataID = (int)(sceneID>>32);
	bool bSameMap = false;
	//������ǵ�һ�ν�����Ϸ���磬�����黯
	bool bDrawMapTextEffect=m_MapInfoId==mapID?false:true;  //ͬһ����ͼ��ʱ������ͼ��תЧ��
	bDrawMapTextEffect = false;
	bSameMap = (m_MapInfoId==mapID)?true:false;
    
    
	if (changetype != pet_enter)
	{
        gGetGameUIManager()->CloseDialogBeforeMapChange();

        //�����Ѱ·����ת��ģ�������ת���ˣ�������ֹͣѰ·
		if (m_MapInfoId == GetMainCharacter()->m_MapWalker.GetTargetMapID()
            && GetMainCharacter()->m_MapWalker.GetMapWalkerType() == eMapWalkerType_JumpPoint)
		{
			GetMainCharacter()->m_MapWalker.ClearGoTo();
		}
		//����ǲ�С��·����ת�㣬������ֹͣѰ·
		
		if (Nuclear::distance(GetMainCharacter()->m_MapWalker.GetCurrentMapTarget(),GetMainCharacter()->GetLogicLocation()) < 80)
		{
			Nuclear::NuclearLocation pt = GetMainCharacter()->GetLogicLocation();
			GetMainCharacter()->m_MapWalker.ClearGoTo();
		}
	}
	if (changetype == pet_enter)
	{
		gGetGameApplication()->DrawLoginBar(22);
	}

	ClearScene();

	int	m_LastMapInfo = m_MapInfoId;
	m_MapInfoId = mapID;//���ݵ�ͼID��ȡ��ͼ��Ϣ
	if ( GetMainCharacter() && m_MapInfoId != -1)
	{
        AttachCameraTo(GetMainCharacter()->GetSprite());
		Nuclear::GetEngine()->GetWorld()->SetCameraUpdateType(Nuclear::XPCAMERA_UPDATE_TYPE2);
        
        gGetGameApplication()->BeginDrawServantIntro();
        
		bool bLoadSuccess = true;
		if (!bSameMap)
		{
			bLoadSuccess = LoadMap(ptLocation);
		}
		else
		{
			Nuclear::GetEngine()->GetWorld()->ImmediatelyAssureRegionResource(Nuclear::NuclearWorldLogicCoord::logic2world(ptLocation));
		}
        
		m_bFirstEnterScene = false;	//����Ϳ�����false��
		if (bLoadSuccess)
		{
			int64_t sculptid = GetTableNumberFromLua("map.cworldmapconfig", m_MapInfoId, "sculptid");
			if (sculptid == 0){
				//m_bJumpMapForAutoBattle = false;
				GetMainCharacter()->StopPacingMove();
			}
			//��ʼ������λ�ã�������ǰ��ͼ����
			GetMainCharacter()->InitPosition(ptLocation,highlevel);
			if (GetMainCharacter()->GetMoveState() == eMove_Pacing)
			{
				m_bJumpMapForAutoBattle = true;
			}

			AttachCameraTo(GetMainCharacter()->GetSprite());

			GetMainCharacter()->SetVisible(true);
				
			Nuclear::GetEngine()->GetWorld()->SetCameraUpdateType(Nuclear::XPCAMERA_UPDATE_TYPE2);
			CEGUI::uint32 color = static_cast<CEGUI::uint32>(CEGUI::PropertyHelper::stringToColour(GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "sceneColor")));
			Nuclear::GetEngine()->GetWorld()->SetMaskBoxColor(color);

			//����ǵ�һ�ν�����Ϸ����
			if (changetype == pet_enter)
			{
				gGetNetConnection()->SetStatOpenFlag(true);
				gGetGameUIManager()->OnGameStart();					//��ʼ��GameUIManager
                
				cocos2d::gGetScriptEngine()->executeGlobalFunction("MainRoleData_addTaskShowNpcAll");;
				//������Ϸ���ж��Ƿ�������־���ս��
				if (gGetGameApplication() && GetMainRoleDataAttr(fire::pb::attr::AttrType::LEVEL) == 1)
				{
					if (gGetGameApplication()->IsNormalVer() == false)
					{
						gGetSceneMovieManager()->EnterMovieScene(14002);	cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("guideModelSelectDlg.getInstanceAndShow");
					}
					else
					{
						if (gGetGameApplication()->isFirstTimeEnterGame() <= 1)
						{
#ifdef SHOW_NEWUSER_BATTLE_CONFIRM
							gGetMessageManager()->AddConfirmBox(eConfirmExitGame, GameTable::message::GetCMessageTipTableInstance().getRecorder(160043).msg,
								Event::Subscriber(&GameScene::handleConfirmPlayXinshouJuqing, this), Event::Subscriber(&GameScene::handleCancelXinshouJuqing, this));
#else
							isFirstJuqingPlayed = true;
							gGetSceneMovieManager()->EnterMovieScene(14001);
							gGetGameApplication()->setFirstTimeEnterGameValue(1);
#endif // SHOW_NEWUSER_BATTLE
						}
						else if (gGetGameApplication()->isFirstTimeEnterGame() == 3)
						{
							gGetSceneMovieManager()->EnterMovieScene(14002);
							if (gGetNewRoleGuideManager()->getGuideModel() == 2)
							{
								cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("guideModelSelectDlg.getInstanceAndShow");
							}
						}
					}
				}
			}
			else
			{
				cocos2d::gGetScriptEngine()->executeGlobalFunction("MainRoleData_AddSceneFollowNpcOnMapChange");//���¼��ظ���npc
				cocos2d::gGetScriptEngine()->executeGlobalFunction("MainRoleData_addTaskShowNpcAll");//

				//MessageBox������ͼ������һ�ν�����Ϸ���粻�õ��ô˺���
				if (gGetMessageManager())
				{
					gGetMessageManager()->OnMapChange();
				}
                
				EndDrawEnterMapNameEffect();
                
                if (gGetScene()->isOnDreamFade()&&gGetScene()->isOnDreamScene())
                {
                    gGetScene()->BeginDreamFade();
                    gGetScene()->SetDreamFadeTime(s_iToatalDreamFadeTime);
                }
			}
            
            gGetGameApplication()->EndDrawServantIntro();
			//������Ϣ
			m_MapDataID = mapDataID;
			m_MapDataName = mapName;
			cocos2d::gGetScriptEngine()->executeGlobalFunction("MainPetDataManager_AddScenePetIfShowPetExist");
            
			EventMapChange.Bingo();
			if(changetype == ret_gc)//������������Ի�����ת��ͼ��������Ҫ���Ż����Ч��
			{
				fire::pb::mission::CMissionReachScene reachscene;
				gGetNetConnection()->send(reachscene);

			}
           
            cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("FubenGuideDialog.DestroyDialog");
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("deathNoteDlg.DestroyDialog");
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("NpcDialog.DestroyDialog");
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("familybossBloodBar.DestroyDialog");
			// �ж��߼��Ƶ��ű�
			int nParam1 = m_MapInfoId;
			int nParam2 = 0;
			int nParam3 = 0;
			int nParam4 = 0;
			int nJingjiMapTypeEnter = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("getJingjiMapType", nParam1, nParam2, nParam3, nParam4);
			nParam1 = m_LastMapInfo;
			int nJingjiMapTypeExit = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("getJingjiMapType", nParam1, nParam2, nParam3, nParam4);
			if (nJingjiMapTypeExit > 0 || (c_iBingfengMapIDBeg <= m_LastMapInfo && m_LastMapInfo <= c_iBingfengMapIDEnd))
			{
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("Renwulistdialog.trySetVisibleTrue");
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithBooleanData("LogoInfoDialog.HideOrShowAllBtn", true);
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("bingfengTaskTips.DestroyDialog");
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithBooleanData("bingfengwangzuomanager.setInBingfeng", false);
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.ExitEnChouPVPScene");
			}
			if (c_iBingfengMapIDBeg <= m_MapInfoId && m_MapInfoId <= c_iBingfengMapIDEnd)
            {
                cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("Renwulistdialog.trySetVisibleFalse");

				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("bingfengTaskTips.getInstanceAndShow");
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithBooleanData("LogoInfoDialog.HideOrShowAllBtn", false);
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithBooleanData("bingfengwangzuomanager.setInBingfeng", true);
				HideJumpEffect();
                cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.EnterEnChouScene");
            }
			if (nJingjiMapTypeExit > 0)
			{
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("exitJingjiMap", nJingjiMapTypeExit, 0, 0, 0);
			}
			if (nJingjiMapTypeEnter > 0)
			{
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("enterJingjiMap", nJingjiMapTypeEnter, 0, 0, 0);
			}
			
            if(!bSameMap)
            {
				if (GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "dynamic") == 1) //normal fuben to dynamic
                {
					if (GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "fubenType") == 2) // ��ͨ����
					{
						//�״ν�����Ϸ��LastMapInfo������
						if (GetTableNumberFromLua("map.cmapconfig", m_LastMapInfo, "id") == -1 || !GetTableNumberFromLua("map.cmapconfig", m_LastMapInfo, "dynamic"))
						{
							cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.EnterFuben");
							cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithIntegerData("Jingyingfubendlg.getInstanceAndShow", 1);
						}
					}
					else if (GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "fubenType") == 3) //ʱ��֮Ѩ
					{
						if (GetTableNumberFromLua("map.cmapconfig", m_LastMapInfo, "id") == -1 || !GetTableNumberFromLua("map.cmapconfig", m_LastMapInfo, "dynamic"))
						{
							cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.EnterFuben");
							cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithIntegerData("Jingyingfubendlg.getInstanceAndShow", 2);
						}
					}
                }
                else
                {
					if (GetTableNumberFromLua("map.cmapconfig", m_LastMapInfo, "dynamic") == 1) // dynamic to normal
					{
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.ExitFuben");
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("Jingyingfubendlg.DestroyDialog");
					}
                }
                
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
                PlayMapBackGroundMusic();
            }

			LoadClientNpcInfo();

			//����NPC��������ʼ������NPC
			//�������npc
			if (GetSceneNpcManager())
			{
				GetSceneNpcManager()->InitSceneNpc(m_MapInfoId);
			}
            
			//����������������Ϸ��ϵ�Э��
			if (changetype == pet_enter)
			{
				fire::pb::CAfterEnterWorld AfterEnterWorld;
				gGetNetConnection()->send(AfterEnterWorld);
			}
            
            //��ת��ͼ���Ƿ��Զ�Ѳ��
            if (m_bJumpMapForAutoBattle&&GetMainCharacter())
            {
                GetMainCharacter()->SetRandomPacing();
                
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("LogoInfoDialog.GetSingletonDialogAndShowIt");
                
                m_bJumpMapForAutoBattle=false;
            }
		}

		//////////////////////////////////
        cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("ShowHide.ChangeMap", m_LastMapInfo, m_MapInfoId);
        cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("ShowHide.EnterLeavePVPArea");
		if (gGetGameUIManager()->getTreasureMapId() != mapID)
		{
			gGetGameUIManager()->setTreasureMapId(-1);
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("supertreasuremap.DestroyDialog");
		}

		return bLoadSuccess;
	}
	else
		return false;
}

//���ص�ͼ
bool GameScene::LoadMap(Nuclear::NuclearLocation ptLocation)
{
	m_bIsLoadMapFrame=true;
	m_bLoadMaping=true;

	Nuclear::Engine* pEngine = static_cast<Nuclear::Engine*>(Nuclear::GetEngine());

	Nuclear::XPLoadmapParam lmParam;
	lmParam.objLoc = Nuclear::NuclearWorldLogicCoord::logic2world(ptLocation);
	if (Nuclear::GetEngine()->GetWorld())
	{
		StartJumMap();
		if (Nuclear::GetEngine()->GetWorld()->LoadMap(GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir"), GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/maze.dat", &lmParam, false))
		{
			//����Ĭ��ս����ͼ
			if (GetBattleManager() && GetBattleManager()->IsInBattle()==false)
			{
				GetBattleManager()->ResetBattleGround();
			}
            
			EndLoadMap();
			//������ת��
			if (GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "jumpmappoint")  == 1){
				LoadJumpMapPointInf();
			}
			Nuclear::NuclearLocation mapsize;
			Nuclear::GetEngine()->GetWorld()->GetMapSize(mapsize);
			//���ص�ͼ�������ã�����PK̨���򣬰�̯����
			
			std::wstring regionfilename = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/regiontypeinfo.dat";
			if (!m_RegionBuffer.Load(LPCTSTR(regionfilename.c_str())))
			{
				m_RegionBuffer.Init((mapsize.x + 24 -1)/24,(mapsize.y + 16 -1)/16);
			}
			//������Ծ�赲��Ϣ����ʱҲ��regiontypeinfo.dat�ɣ���ʱ���ٸ�
			std::wstring jumpfilename = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/JumpBlock.dat";
			if (!m_JumpPointBuffer.Load(LPCTSTR(jumpfilename.c_str())))
			{
				m_JumpPointBuffer.Init((mapsize.x + 24 -1)/24,(mapsize.y + 16 -1)/16);
			}
			//���ص�ͼ�µ���Ϣ��
			std::wstring isolatedinfo = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/Island.dat";
			if (!m_IsolatedIslandBuffer.Load(LPCTSTR(isolatedinfo.c_str())))
			{
				m_IsolatedIslandBuffer.Init((mapsize.x + 24 -1)/24,(mapsize.y + 16 -1)/16);
			}
			std::wstring isolatedinfo2 = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/Island2.dat";
			if (!m_IsolatedIslandBuffer2.Load(LPCTSTR(isolatedinfo2.c_str())))
			{
				m_IsolatedIslandBuffer2.Init((mapsize.x + 24 -1)/24,(mapsize.y + 16 -1)/16);
			}
            
			if (gGetGameUIManager()->isSuperTreasureMapEnable() == true)
			{
				gGetGameUIManager()->setSuperTreasureMapEnable(false);
				Nuclear::NuclearLocation loc = GetMainCharacter()->GetSuperMapTargetPos();
				//gGetGameUIManager()->AddMessageTip(GameTable::message::GetCMessageTipTableInstance().getRecorder(170001).msg);
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushStringToLuaStack(ws2s(GameTable::message::GetCMessageTipTableInstance().getRecorder(170001).msg).c_str());
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("CTipsManager.AddMessageTip_", 1);
				cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("supertreasuremap.getInstanceAndShow", loc.x, loc.y);
			}
			return true;
		}
		else
		{
			EndLoadMap();
			return false;            
		}
	}
	else
	{
		EndLoadMap();
		XPTRACE(MHSD_UTILS::GETSTRING(991).c_str());
		return false;
	}
}

//�����˶�����״̬�ı�ʱ�ص�
void GameScene::OnUpdateSpriteAction(Nuclear::ISprite * sprite, Nuclear::XPUSA_TYPE type) // ������״̬�����ı�ʱ���ص�����������¶�����
{
	SceneObject* pSceneObject = FindSceneObjectBySprite(sprite);
	if (pSceneObject)
	{
		pSceneObject->UpdateAction(type);
	}
}

//�ı䳡����npc������״̬
void GameScene::UpdateSceneNpcQuestState(const int64_t& npckey, eNpcMissionState& state,bool bBaseID)
{
	Npc* pNpc = NULL;
    
	if(bBaseID)
	{
		pNpc = FindNpcByBaseID((int)npckey);
	}
	else
	{
		pNpc = FindNpcByID(npckey);
	}
	if(pNpc)
	{
		pNpc->SetQuestState(state);
	}
}

void GameScene::AddFossicNpcEffect()
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end(); itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if(pNpc->GetNpcTypeID() == eNpcTypeFossick)
		{
			FossickNpc* pFossickNpc = static_cast<FossickNpc*>(itor->second);
			pFossickNpc->AddEffect();
		}
	}
}

void GameScene::RemoveFossicNpcEffect(int itemid)
{
    return;
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end(); itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if(pNpc->GetNpcTypeID() == eNpcTypeFossick)
		{
			FossickNpc* pFossickNpc = static_cast<FossickNpc*>(itor->second);
			pFossickNpc->RemoveEffect(itemid);
		}
	}
}

void GameScene::RemoveFossicNpcCoolingState(int itemid)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end(); itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if(pNpc->GetNpcTypeID() == eNpcTypeFossick)
		{
			FossickNpc* pFossickNpc = static_cast<FossickNpc*>(itor->second);
			pFossickNpc->EndCoolingState(itemid);
		}
	}
}

//ͨ�������ҵ���SceneObject
SceneObject* GameScene::FindSceneObjectBySprite(Nuclear::ISprite * sprite, bool bInBattle)
{
	if (sprite)
	{
		return (SceneObject*)sprite->GetUserData();
	}

	return NULL;
}

//ͨ��ID�ҵ���Ӧ��sceneObject
SceneObject* GameScene::FindSceneObjectByTypeID(eSceneObjType type, int64_t id, bool bInBattle)
{
	if (!bInBattle)
	{
		SceneObjMap::iterator it = m_SceneSprite[type].find(id);
		if (it != m_SceneSprite[type].end())
		{
			return it->second;
		}
		//�����
		else if (type == eSceneObjClientNpc)
		{
			if (GetSceneNpcManager())
			{
				return GetSceneNpcManager()->FindSceneNpcByID(id);
			}
			else
			{
				return NULL;
			}
		}
	}
	else
	{
		return (SceneObject*)(GetBattleManager()->FindBattlerByID(id));
	}

	return NULL;
}

//��ĳ��������ʧʱ
void GameScene::OnSceneObjectRemove(SceneObject* pObj)
{
	if (pObj == m_pMouseOverObjects)
		m_pMouseOverObjects = NULL;
	for (std::list<SceneObject*>::iterator it=m_MouseOverObjectsList.begin();it!=m_MouseOverObjectsList.end();it++)
	{
		if ((*it) == pObj)
		{
			it = m_MouseOverObjectsList.erase(it);
			break;
		}
	}
}

SceneObject* GameScene::GetMouseOverObjects()
{
	return m_pMouseOverObjects;
}

std::list<SceneObject*> GameScene::GetMouseOverObjectsList()
{
	return m_MouseOverObjectsList;
}

//�����Ļ���굽�����߼������ת��
Nuclear::NuclearLocation GameScene::MousePointToPixel(Nuclear::NuclearLocation mousepoint)
{
	Nuclear::NuclearLocation ptPixel;
	Nuclear::NuclearRect cp = GetViewport();
	ptPixel.x = cp.left + mousepoint.x;
	ptPixel.y = cp.top + mousepoint.y;
	return ptPixel;
}

Nuclear::NuclearLocation GameScene::PixelToGrid(Nuclear::NuclearLocation ptPixel)
{
	return Nuclear::NuclearLocation(ptPixel.x/g_gridWidth,ptPixel.y/g_gridHeight);
}

Nuclear::NuclearLocation GameScene::GirdToPixel(Nuclear::NuclearLocation ptGrid)
{
	return Nuclear::NuclearLocation(ptGrid.x*g_gridWidth + g_gridWidth/2,ptGrid.y*g_gridHeight + g_gridHeight/2);
}

bool GameScene::IsMoveBlock(Nuclear::NuclearLocation logicposition,eMoveMask movemask)
{
	unsigned char mask = Nuclear::GetEngine()->GetWorld()->GetMazeMask(logicposition.x,logicposition.y);
	return (mask&movemask) != 0x00;
}

int GameScene::GetIslandAreaID(Nuclear::NuclearLocation desposition,bool bhighlevel)
{
	if (bhighlevel)
	{
		return m_IsolatedIslandBuffer2.GetPointValue(desposition.x/g_logicGrid,desposition.y/g_logicGrid);
	}
	else
	{
		return m_IsolatedIslandBuffer.GetPointValue(desposition.x/g_logicGrid,desposition.y/g_logicGrid);
	}
}

//�ж��������ڵ��Ƿ�����ͨ�ģ���ֹ�µ�֮���Ѱ·
bool GameScene::IsTheSameArea(Nuclear::NuclearLocation desposition,Nuclear::NuclearLocation curposition,bool bhighlevel)
{
	if (bhighlevel)
	{
		return m_IsolatedIslandBuffer2.GetPointValue(desposition.x/g_logicGrid,desposition.y/g_logicGrid) == m_IsolatedIslandBuffer2.GetPointValue(curposition.x/g_logicGrid,curposition.y/g_logicGrid);
	}
	else
	{
		return m_IsolatedIslandBuffer.GetPointValue(desposition.x/g_logicGrid,desposition.y/g_logicGrid) == m_IsolatedIslandBuffer.GetPointValue(curposition.x/g_logicGrid,curposition.y/g_logicGrid);
	}
}

////1��2��3��4�ĸ���Ծ�赲�ȼ�
bool GameScene::IsJumpBlock(Nuclear::NuclearLocation logicposition,int jumplevel)
{
	return m_JumpPointBuffer.GetPointValue(logicposition.x/g_logicGrid,logicposition.y/g_logicGrid) >= 0x01<<(jumplevel-1);
}

bool GameScene::IsInChallengeArea(Nuclear::NuclearLocation logicposition)
{
	return m_RegionBuffer.CheckPointType(logicposition.x/g_logicGrid,logicposition.y/g_logicGrid,eRegionType_QIEZUO);
}

bool GameScene::IsInPVPArea(Nuclear::NuclearLocation logicLoc)
{
	return m_RegionBuffer.CheckPointType(logicLoc.x/g_logicGrid,logicLoc.y/g_logicGrid,eRegionType_PVP);
}

//�ж��Ƿ�����������
bool GameScene::IsMaskArea(Nuclear::NuclearLocation logicloc)
{
	return m_RegionBuffer.CheckPointType(logicloc.x/g_logicGrid,logicloc.y/g_logicGrid,eRegionType_Mask);
}

//mask�ĸ���λ����ر����ͣ�0ΪĬ�ϣ�1���أ�2�ݵأ�3ˮ��
unsigned char GameScene::GetGroundType(Nuclear::NuclearLocation logicposition)
{
	unsigned char mask = Nuclear::GetEngine()->GetWorld()->GetMazeMask(logicposition.x,logicposition.y);
	return mask>>6;
}

int GameScene::GetGridDistanceByPixel(Nuclear::NuclearLocation pt1, Nuclear::NuclearLocation pt2)
{
	return Nuclear::distance(PixelToGrid(pt1),PixelToGrid(pt2));
}

//����MouseoverObject
bool GameScene::UpdateMouseOverObjects(Nuclear::NuclearLocation mousepoint)
{
	Nuclear::NuclearLocation maploc = MousePointToPixel(mousepoint);
	std::vector<Nuclear::ISelectableObj*> objs;
	SelectObjs(maploc, objs);
	//����ͼ��ʱ���øı������ʽ
	if (!objs.empty())
	{
		m_MouseOverObjectsList.clear();
		for (std::vector<Nuclear::ISelectableObj*>::iterator it=objs.begin();it!=objs.end();it++)
		{
			Nuclear::ISprite* sprobj = dynamic_cast<Nuclear::ISprite*>(*it);
			SceneObject* pObject = FindSceneObjectBySprite(sprobj);
			if (pObject != NULL && pObject->GetID() != GetMainCharacter()->GetID())
			{
				m_MouseOverObjectsList.push_back(pObject);
			}
			
		}
		if(m_MouseOverObjectsList.empty())
		{
            m_pMouseOverObjects = NULL;
			return true;
		}
		m_MouseOverObjectsList.sort(SceneObject::sComparewithSceneObjType);
		std::list<SceneObject*>::iterator it=m_MouseOverObjectsList.begin();
		m_pMouseOverObjects = (*it);
		
		if (m_pMouseOverObjects && !m_pMouseOverObjects->IsSceneObjectType(eSceneObjClientNpc))
		{
			m_pMouseOverObjects->OnSetCursor();
			return true;
		}
		else
		{
			UpdateMouseOverNull();
			return true;
		}
	}
	else
	{
		ClearMouseOverObjects();
		UpdateMouseOverNull();
		return true;
	}
	return false;
}
bool GameScene::UpdateMouseOverNull()
{
	return true;
}

Nuclear::NuclearRect GameScene::GetViewport()
{
	return Nuclear::GetEngine()->GetWorld()->GetViewport();
}

bool GameScene::OnBeforeRender(int now)
{
	return true;
}
void GameScene::BeginShake(int id, int range, int time){

	m_nShakeRange = range;
	m_nShakeBetweenTime = 0;
	m_nShakeEndTime = time;
	m_bIsShaking = true;
	m_nShakeID = id;
	m_nShakeTop = 0;
	m_nShakeLeft = 0;
	m_CurViewportRect = Nuclear::GetEngine()->GetWorld()->GetViewport();
}

////��������
void GameScene::UpdateShake(int del)
{

	if (m_bIsShaking)
	{
		if (m_nShakeEndTime <=0)
		{
			m_bIsShaking = false;
			m_CurViewportRect.top -= m_nShakeTop;
			m_CurViewportRect.left -= m_nShakeLeft;
			Nuclear::GetEngine()->GetWorld()->SetViewportLT(m_CurViewportRect.left, m_CurViewportRect.top);
			return;
		
		}
		else{
			Nuclear::NuclearRect rect = Nuclear::GetEngine()->GetWorld()->GetViewport();
			switch (m_nShakeID)

			{
			case 1:{
				int nTop = (rand() % m_nShakeRange);
				int nLeft = (rand() % m_nShakeRange);
				if (m_nShakeTop <= 0){
					m_nShakeTop += nTop;
					rect.top += nTop;
				}
				else{
					m_nShakeTop -= nTop;
					rect.top -= nTop;
				}
				if (m_nShakeLeft <= 0){
					m_nShakeLeft += nLeft;
					rect.left += nLeft;
				}
				else{
					m_nShakeLeft -= nLeft;
					rect.left -= nLeft;
				}

				break;
			}
			case 2:{
				int nTop = (rand() % m_nShakeRange);
				if (m_nShakeTop <= 0){
					m_nShakeTop += nTop;
					rect.top += nTop;
				}
				else{
					m_nShakeTop -= nTop;
					rect.top -= nTop;
				}
				break;
			}
			default:
				break;
			}

			m_CurViewportRect = rect;
			m_nShakeEndTime -= del;
			Nuclear::GetEngine()->GetWorld()->SetViewportLT(m_CurViewportRect.left, m_CurViewportRect.top);
		}
		
		
	}
}

void GameScene::DecNotTransparentManNum()
{
	m_nNotTransparentManNum--;
}

void GameScene::AddNotTransparentManNum()
{
	m_nNotTransparentManNum++;
}

//�Ƿ��ǽ�ֹ��Ծ�ĵ�ͼ
bool GameScene::IsJumpForbiddenMap()
{
	return GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "qinggong") == 0;	//Ϊ0��ʾ��ֹ��Ծ
}

void GameScene::Run(int now, int delta)
{
	NpcRun(now,delta);
	CharacterRun(now,delta);
	PetRun(now,delta); 
	MovieNpcRun(now,delta);
	FollowNpcRun(now,delta);
	PuppyRun(now,delta);
	m_nowTime = now;
	UpdateShake(delta);
	SceneEffectRun(now,delta);

	//����NPC��run
	if (GetSceneNpcManager())
	{
		GetSceneNpcManager()->Run(now,delta);
	}
    
	if (m_bEnbaleJumpMapFadeEffect)
	{
		if (m_bMapJumping&&!m_bLoadMaping&&!m_bIsLoadMapFrame)
		{
			m_iFadeElapseTime+=delta;
			if (m_iFadeElapseTime>s_iJumpMapFadeTime)
			{
				EndJumpMap();
			}
		}
	}
    
	if (m_bIsLoadMapFrame)
	{
		m_bIsLoadMapFrame=false;
	}
	
	if (m_bIsOnDrawEnterMapNameEffect)
	{
		m_iEnterMapElapseTime+=delta;
		if (m_iEnterMapElapseTime>s_iTotalDrawEnterMapNameTime)
		{
			EndDrawEnterMapNameEffect();
		}
	}
    
    if (m_bStartNpcAutoPopoTimer) {
        m_fStartNpcAutoPopoTimer -= delta;
        if (m_fStartNpcAutoPopoTimer < 0)
        {
            m_bStartNpcAutoPopoTimer = false;
            if (gGetScene())
			{
				gGetScene()->StartNpcAutoPopoTimer();
			}
        }
    }
    
    if (m_bNpcAutoPopoTimer) {
        m_fNpcAutoPopoTimer -= delta;
        if (m_fNpcAutoPopoTimer < 0)
        {
            m_fNpcAutoPopoTimer = s_iNpcAutoPopoTimerCDTime * 1000;
            if (gGetScene())
			{
				gGetScene()->CheckNpcAutoPopo();
			}
        }
    }
#if (defined WIN7_32) || (defined WINAPI_FAMILY && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	if (gGetSceneMovieManager() && gGetSceneMovieManager()->isOnSceneMovie())
	{
		if (::GetKeyState(VK_CONTROL) < 0 && gGetGameApplication()->isFirstTimeEnterGame() == 1)
		{
			gGetGameApplication()->setFirstTimeEnterGameValue(10);
			gGetSceneMovieManager()->OnBreakMoive();
		}
	}
#endif
}

void GameScene::SetSceneMapMaze(int mapid,int mazetypeid)
{
	std::wstring mazefilepath = L"";
	if (mazetypeid == 0)
	{
		mazefilepath = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/maze.dat";
	}
	else
	{
		mazefilepath = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/maze" + StringCover::intTowstring(mazetypeid) + L".dat";
	}
	size_t length= 0;
	LJFM::LJFMF binary_file;
	if (binary_file.Open(mazefilepath,LJFM::FM_EXCL,LJFM::FA_RDONLY))
	{
		size_t size = static_cast<size_t>(binary_file.GetSize());
		char* MazeBuffer = new char[size];
		binary_file.ReadAll((void*)MazeBuffer,size);
        
		Nuclear::GetEngine()->GetWorld()->SetMapMaze(MazeBuffer,size);
        
		delete [] MazeBuffer;
		binary_file.Close();
	}
}

void GameScene::RefreshAllSpriteNameTexture()
{    
    for(int spritetype= eSceneObjItem; spritetype < eSceneObjMax; spritetype ++)
    {
        for(SceneObjMap::iterator itor = m_SceneSprite[spritetype].begin();itor != m_SceneSprite[spritetype].end(); itor++)
        {
            SceneObject* entity = itor->second;
            if(entity)
            {
                entity->UpdatNameTexture(true);
            }
        }
    }
}
void GameScene::ReleaseAllSpriteNameTexture()
{
	for (int spritetype = eSceneObjItem; spritetype < eSceneObjMax; spritetype++)
	{
		for (SceneObjMap::iterator itor = m_SceneSprite[spritetype].begin(); itor != m_SceneSprite[spritetype].end(); itor++)
		{
			SceneObject* entity = itor->second;
			if (entity)
			{
				entity->ReleaseNameTexture();
			}
		}
	}
}
void GameScene::ReloadAllSpriteNameTexture()
{
	for (int spritetype = eSceneObjItem; spritetype < eSceneObjMax; spritetype++)
	{
		for (SceneObjMap::iterator itor = m_SceneSprite[spritetype].begin(); itor != m_SceneSprite[spritetype].end(); itor++)
		{
			SceneObject* entity = itor->second;
			if (entity)
			{
				entity->ReloadNameTexture();
			}
		}
	}
}

void GameScene::SetChangeMapForbidRun(bool b)
{
	m_bChangeMapForbidRun = b;
}

bool GameScene::IsChangeMapForbidRun()
{
	return m_bChangeMapForbidRun;
}

const int& GameScene::GetMapInfo()
{
	return m_MapInfoId;
}

std::map<int, stClientNpcInfo>& GameScene::GetClientNpcMap()
{
	return m_ClientNpcMap;
}

void GameScene::NpcRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end();)
	{
		//����õ�λ�Ѿ�disappear�ˣ���ɾ��
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if (pNpc)
		{
			if (pNpc->IsDisappear())
			{
				delete itor->second;
				m_SceneSprite[eSceneObjNpc].erase(itor++);
			}
			else
			{
				itor->second->Run(now,delta);
				itor++;
			}
		}
		else
		{
            m_SceneSprite[eSceneObjNpc].erase(itor++);
		}
	}
}

void GameScene::CharacterRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		itor->second->Run(now,delta);
	}
}

void GameScene::PetRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjPet].begin();itor != m_SceneSprite[eSceneObjPet].end();itor++)
	{
		itor->second->Run(now,delta);
	}
}

void GameScene::PuppyRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjPuppy].begin();itor != m_SceneSprite[eSceneObjPuppy].end();itor++)
	{
		itor->second->Run(now,delta);
	}
}

void GameScene::FollowNpcRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjFollowNpc].begin();itor != m_SceneSprite[eSceneObjFollowNpc].end();itor++)
	{
		itor->second->Run(now,delta);
	}
}

void GameScene::MovieNpcRun(int now, int delta)
{
	for(SceneObjMap::iterator itor = m_SceneSprite[eSceneObjMovie].begin();itor != m_SceneSprite[eSceneObjMovie].end();itor++)
	{
		itor->second->Run(now,delta);
	}
}

void GameScene::SceneEffectRun(int now, int delta)  //������Ч����Ҫ��ָ��ĻЧ�����罥�ڽ���
{
	VECSceneEffect::iterator it=m_vecSceneEffect.begin();
	for (;it!=m_vecSceneEffect.end();)
	{
		(*it)->Update(delta);
		if ((*it)->IsEnd())
		{
			delete *it;
			it=m_vecSceneEffect.erase(it);
		}else
		{
			++it;
		}
	}
}


void GameScene::SetShieldCharacter(bool b,bool includemain)
{
	if (m_bShieldCharacter == b)
		return;
	m_bShieldCharacter = b;
    
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		if (itor->second == GetMainCharacter())
		{
			if (includemain)
				itor->second->SetVisible(!m_bShieldCharacter);
			continue;
		}
		else
		{
			itor->second->SetVisible(!m_bShieldCharacter);
		}
	}
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjPet].begin();itor != m_SceneSprite[eSceneObjPet].end();itor++)
	{
		if (itor->first == GetMainRoleDataNumValue<int64_t>("roleid"))
			continue;
		else
			itor->second->SetVisible(!m_bShieldCharacter);
	}
}


bool GameScene::isInShieldCharacterState()
{
	return m_bShieldCharacter;
}

void GameScene::Draw(int now)
{
	if (!GetBattleManager()->IsInBattle())
	{
		for (size_t type = eSceneObjItem; type < eSceneObjClientNpc; type++)
		{
			//ֻ��NPC����ͨ��UI����Ⱦ����
			if (type == eSceneObjNpc || type == eSceneObjFollowNpc || type == eSceneObjTaskShowNpc || type == eSceneObjClientNpc)
			{
				for (SceneObjMap::iterator it = m_SceneSprite[type].begin(); it != m_SceneSprite[type].end(); it++)
				{
					it->second->Draw(now);
				}
			}
		}

		//����NPC��draw
		if (GetSceneNpcManager())
		{
			GetSceneNpcManager()->Draw(now);
		}
	}

	//��Ⱦ����
	Nuclear::IParticleManager* pParMgr=Nuclear::GetEngine()->GetRenderer()->GetParticleManager();
	for (std::list<int>::iterator it=m_ParticleList.begin();it!=m_ParticleList.end();it++)
	{
		pParMgr->RenderParticleSystem((*it));
	}

	DrawDreamImage();
    
	if (m_bEnbaleJumpMapFadeEffect)
	{
		DrawJumpMapFade();
	}
    
	DrawSceneEffect();

}

void GameScene::OnDrawNameCB(Nuclear::ISprite* pSprite)
{
	SceneObject* sceneObject = FindSceneObjectBySprite(pSprite, GetBattleManager()->IsInBattle());
	if (sceneObject)
	{
		sceneObject->Draw(0);
	}
}

//����������ս��ģʽ
void GameScene::OnBattleBegin()
{
	Nuclear::GetEngine()->GetWorld()->SetWorldMode(Nuclear::XPWM_WORLD_BATTLE);
	//����ս�������������ͷ�������
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjPet].begin();it!=m_SceneSprite[eSceneObjPet].end();it++)
	{
		it->second->ShowHideAllTalk(false);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjCharacter].begin();it!=m_SceneSprite[eSceneObjCharacter].end();it++)
	{
		it->second->ShowHideAllTalk(false);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjPuppy].begin();it!=m_SceneSprite[eSceneObjPuppy].end();it++)
	{
		it->second->ShowHideAllTalk(false);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjNpc].begin();it!=m_SceneSprite[eSceneObjNpc].end();it++)
	{
		it->second->ShowHideAllTalk(false);
	}
	for (SceneObjMap::iterator it = m_SceneSprite[eSceneObjFollowNpc].begin(); it != m_SceneSprite[eSceneObjFollowNpc].end(); it++)
	{
		it->second->ShowHideAllTalk(false);
	}
	for (SceneObjMap::iterator it = m_SceneSprite[eSceneObjTaskShowNpc].begin(); it != m_SceneSprite[eSceneObjTaskShowNpc].end(); it++)
	{
		it->second->ShowHideAllTalk(false);
	}
}

//���������ս��ģʽ
void GameScene::OnBattleEnd()
{
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjPet].begin();it!=m_SceneSprite[eSceneObjPet].end();it++)
	{
		it->second->ShowHideAllTalk(true);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjCharacter].begin();it!=m_SceneSprite[eSceneObjCharacter].end();it++)
	{
		it->second->ShowHideAllTalk(true);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjPuppy].begin();it!=m_SceneSprite[eSceneObjPuppy].end();it++)
	{
		it->second->ShowHideAllTalk(true);
	}
	for (SceneObjMap::iterator it=m_SceneSprite[eSceneObjNpc].begin();it!=m_SceneSprite[eSceneObjNpc].end();it++)
	{
		it->second->ShowHideAllTalk(true);
	}
	for (SceneObjMap::iterator it = m_SceneSprite[eSceneObjFollowNpc].begin(); it != m_SceneSprite[eSceneObjFollowNpc].end(); it++)
	{
		it->second->ShowHideAllTalk(true);
	}
	for (SceneObjMap::iterator it = m_SceneSprite[eSceneObjTaskShowNpc].begin(); it != m_SceneSprite[eSceneObjTaskShowNpc].end(); it++)
	{
		it->second->ShowHideAllTalk(true);
	}
    
    PlayMapBackGroundMusic();

	int lastBattleID = GetBattleManager()->GetLastBattleId();

	int startID = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithStringData("GetNumberValueForStrKey", "NEWER_BATTLE_ID_START");
	int endID = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithStringData("GetNumberValueForStrKey", "NEWER_BATTLE_ID_END");
    
	if (lastBattleID >= startID && lastBattleID <= endID && !gGetGameApplication()->isReconnecting())
	{
		isFirstJuqingPlayed = false;
		gGetSceneMovieManager()->EnterMovieScene(14002);
		gGetGameApplication()->setFirstTimeEnterGameValue(3);

		//GetBattleManager()->SetAutoCommandOperateType(0, 1);
		//GetBattleManager()->SetAutoCommandOperateID(0, 0);//0Player,1Pet
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("guideModelSelectDlg.getInstanceAndShow");
	}
	Nuclear::GetEngine()->GetWorld()->SetWorldMode(Nuclear::XPWM_NORMAL);
}

//����SceneObject֮��ĸ��Ӿ���
int GameScene::GetDistanceFromMainCharacter(const int64_t& sceneobject_1,eSceneObjType object_1Type)
{
	SceneObject* pcso_1 = FindSceneObjectByTypeID(object_1Type,sceneobject_1);
	
	if ( !pcso_1)
		return INT_MAX;
	
	return GetGridDistanceByPixel(pcso_1->GetLocation(),GetMainCharacter()->GetLocation());
	
}

void GameScene::DrawJumpMapFade() //����ͼ��ת�黯
{
	if (!m_bMapJumping)
	{
		return;
	}
    
	unsigned char alpha= 255;
	if (m_iLoadMapProgress>99)
	{
		alpha=128-(unsigned char)(((float)m_iFadeElapseTime/(float)s_iJumpMapFadeTime)*128.0f);
	}else
	{
		alpha= 255-(unsigned char)(((float)m_iLoadMapProgress/100.0f)*128.0f);
	}

	if (m_iJumpMapFadePicHandle!=Nuclear::INVALID_PICTURE_HANDLE)
	{		
		Nuclear::NuclearColor color(alpha,255,255,255);
		Nuclear::NuclearDisplayMode mode=Nuclear::GetEngine()->GetRenderer()->GetDisplayMode();
		Nuclear::NuclearFRectt rect(0.0f,0.0f,(float)mode.width,(float)mode.height);
		Nuclear::GetEngine()->GetRenderer()->DrawPicture(m_iJumpMapFadePicHandle,rect,color);
	}
	
}

void GameScene::DrawFinishQuestAndChengjiuEffect()
{
	if (m_pFinishQuestEffect)
	{
		Nuclear::GetEngine()->DrawEffect(m_pFinishQuestEffect);
	}
}

extern bool gIsInBackground();

void GameScene::StartJumMap()
{
	if (!m_bEnbaleJumpMapFadeEffect)
	{
		return;
	}
    
	if (m_bFirstEnterScene)
	{
		return;
	}
	EndJumpMap();
	m_bMapJumping=true;
	m_bLoadMaping=true;
	m_iFadeElapseTime=0;

	Nuclear::Engine* pEngine = static_cast<Nuclear::Engine*>(Nuclear::GetEngine());

	if (!gIsInBackground())
    {
        m_iJumpMapFadePicHandle=Nuclear::GetEngine()->CaptureWorld();
    }    
}
void GameScene::StartEndBattleSceneFade()
{
	if (m_bMapJumping)
	{
		return;
	}
	else
	{
		m_bLoadMaping=false;

		Nuclear::Engine* pEngine = static_cast<Nuclear::Engine*>(Nuclear::GetEngine());
	}
}

void GameScene::EndLoadMap()
{
	m_bLoadMaping=false;
	m_iFadeElapseTime=0;

	Nuclear::Engine* pEngine = static_cast<Nuclear::Engine*>(Nuclear::GetEngine());
}

bool GameScene::isLoadMaping()
{
	return m_bLoadMaping;
}

bool GameScene::IsMapJumping()
{
	return m_bMapJumping;
}

void GameScene::SetLoadMapProgress(int pro)
{
	m_iLoadMapProgress = pro;
}

void GameScene::SetFirstEnterScene(bool b)
{
	m_bFirstEnterScene = b;
}

bool GameScene::IsFirstEnterMap()
{
	return m_bFirstEnterScene;
}

void GameScene::EndJumpMap()
{
	if (!m_bEnbaleJumpMapFadeEffect)
	{
		return;
	}
	m_bMapJumping=false;
	m_bLoadMaping=false;
	m_iFadeElapseTime=0;
	m_iLoadMapProgress=0;

	Nuclear::Engine* pEngine = static_cast<Nuclear::Engine*>(Nuclear::GetEngine());

	if (m_iJumpMapFadePicHandle != Nuclear::INVALID_PICTURE_HANDLE)
	{
		Nuclear::GetEngine()->GetRenderer()->FreeRenderTarget(m_iJumpMapFadePicHandle);
	}
	m_iJumpMapFadePicHandle=Nuclear::INVALID_PICTURE_HANDLE;
}

//�Ƿ��ǰ�ȫ����ͼ
bool GameScene::IsSafeMap()
{
	return GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "safemap") == 1;
}

bool GameScene::IsAnLeiQuMap()
{
	return GetTableNumberFromLua("map.cmapconfig", m_MapInfoId, "fightinfor")  == 1;
}

void GameScene::OnEnterSceneNpcSpeakState() //�������npc speakģʽ
{
    HideOrShowAllCharExceptMainChar(false);
}

void GameScene::OnExitSceneNpcSpeakState() //�˳�����npc speakģʽ
{
	if (!gGetSceneMovieManager()->isOnSceneMovie())
	{
		HideOrShowAllCharExceptMainChar(true);
	}
}

void GameScene::HideOrShowAllCharExceptMainChar(bool bVis) //���ػ���ʾ���еľ���
{
    for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();++itor)
    {
        if(itor->second->GetID() != GetMainCharacter()->GetID())
            itor->second->SetVisible(bVis);
    }
}

void GameScene::HideAllCharExceptTeammate()
{
	OnEnterSceneNpcSpeakState();

	cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("TeamManager.HideAllCharExceptTeammate");
}

void GameScene::OnEnterMovieScene() //�������ģʽ
{
	HideOrShowAllSprite(false);
	ReleaseAllJumpPointEffect();
}

void GameScene::OnExitMovieScene(int curMovieMapID) //�˳�����ģʽ
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

    int worldPicHandle = 0;
    if(!gIsInBackground())
    {
        worldPicHandle =  Nuclear::GetEngine()->CaptureWorld();
    }
	
    m_iMovieCapturePic=worldPicHandle;
    
	DelAllMovieSceneNpc();
	
    
	Nuclear::NuclearLocation mainRolePos=GetMainCharacter()->GetLocation();
	if (m_MapInfoId!=curMovieMapID)
	{
		AttachCameraTo(GetMainCharacter()->GetSprite());
        
		Nuclear::XPLoadmapParam lmParam;
		
		lmParam.objLoc=mainRolePos;
		Nuclear::GetEngine()->GetWorld()->LoadMap(GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir"), GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/maze.dat", &lmParam, false);
		
        if (gGetScene()->isOnDreamFade()&&gGetScene()->isOnDreamScene())
        {
            gGetScene()->BeginDreamFade();
            gGetScene()->SetDreamFadeTime(s_iToatalDreamFadeTime);
        }
	}
	else
	{
		AttachCameraTo(GetMainCharacter()->GetSprite());
	}

	LoadJumpMapPointInf();
    
    PlayMapBackGroundMusic();
    ReleaseMovieCapturePic();
}

void GameScene::OnExitMovieScene(int curMovieMapID, int mapId, const Nuclear::NuclearLocation& pos)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

	int worldPicHandle = 0;
	if (!gIsInBackground())
	{
		worldPicHandle = Nuclear::GetEngine()->CaptureWorld();
	}

	m_iMovieCapturePic = worldPicHandle;

	DelAllMovieSceneNpc();

	if (mapId != curMovieMapID)
	{
		m_MapInfoId = curMovieMapID;
		ChangeMap(mapId, pos, L"", -1);

		if (gGetScene()->isOnDreamFade() && gGetScene()->isOnDreamScene())
		{
			gGetScene()->BeginDreamFade();
			gGetScene()->SetDreamFadeTime(s_iToatalDreamFadeTime);
		}
	}
	else
	{
		AttachCameraTo(GetMainCharacter()->GetSprite());
	}

	LoadJumpMapPointInf();

	PlayMapBackGroundMusic();
	ReleaseMovieCapturePic();
}

void GameScene::handleFirstJuqingPlayedEnded()
{
	if (isFirstJuqingPlayed && gGetGameApplication()->isFirstTimeEnterGame() == 1)
	{
		gGetGameApplication()->setFirstTimeEnterGameValue(2);  //��������ս��
	}
}

void GameScene::HideOrShowAllSprite(bool bVis) //���ػ���ʾ���еľ���
{
	for (size_t type = eSceneObjItem;type<eSceneObjClientNpc;type++)
	{
		for (SceneObjMap::iterator itor = m_SceneSprite[type].begin();itor != m_SceneSprite[type].end();++itor)
		{
			itor->second->SetVisible(bVis);
		}
	}
	if (GetSceneNpcManager())
	{
		GetSceneNpcManager()->HideOrShowSceneNpc(bVis);
	}
}

void GameScene::UpdateNpcStateAfterEndMovie()
{
	HideOrShowAllSprite(true);
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end();++itor)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		eNpcMissionState state = GetNpcStateByID(pNpc->GetID(),pNpc->GetNpcBaseID());
		pNpc->SetQuestState(state);
	}
}

void GameScene::RefreshScenarioDisplayNpcState(int npcbaseid, eNpcMissionState state)
{
	SceneObjMap& allnpcs = GetSceneObject(eSceneObjNpc);
	for (SceneObjMap::iterator itor = allnpcs.begin(); itor != allnpcs.end(); itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if (pNpc->GetNpcBaseID() == npcbaseid)
		{
			pNpc->SetQuestState(state, false);
		}
	}
}

bool GameScene::AddMovieSceneNpc(int64_t id, const std::wstring& strName, int title, int modelid, int Logic_X, int Logic_Y, int dir, int colorTemplate, eActionType actype,
	float scale, const std::wstring& efName, int repeat, int ex, int ey, const std::wstring& chengwei, const std::wstring& cwColor) //����һ����������NPC
{
	DWORD chengweiColor = static_cast<CEGUI::uint32>(CEGUI::PropertyHelper::stringToColour(GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "sceneColor")));

	stMovieSceneNpcData npcData(id,strName,title,modelid,(Nuclear::NuclearDirection)dir,colorTemplate, chengwei, chengweiColor);
	MovieSceneNpc* pNpc = FindMovieSceneNpcByID(npcData.id);
	if (pNpc != NULL)
	{
		pNpc->SetAttribute(npcData);
		pNpc->SetLogicLocation(Logic_X,Logic_X);
		
	}
	else
	{
		pNpc = new MovieSceneNpc();
		if(pNpc == NULL)
			return false;
        
		if (pNpc->SetAttribute(npcData))
		{
			pNpc->SetLogicLocation(Logic_X,Logic_Y);
			pNpc->SetDefaultAction(actype);

			m_SceneSprite[eSceneObjMovie][id] = pNpc;
		}
        
	}
	if (id==0)
	{
		pNpc->SetNameColour(0xFF00FF42);
		pNpc->SetNameShadowColor(0xFF011620);
	}

	pNpc->SetScale(scale);
	if (efName != L"")
	{
		pNpc->PlayEffect(efName, ex, ey, repeat, false, true, false, 0, 0); //  false, false, false, repeat, -1, 0); // 1:Top,           0 : Mid,           -1 : Bottom
	}
	return true;
}

void GameScene::DelMovieSceneNpc(int64_t id) //ɾ��һ����������NPC
{
	RemoveSceneObjectByID(eSceneObjMovie,id);
}

void GameScene::DelAllMovieSceneNpc()  //ɾ�����еĳ�������NPC
{
	RemoveSceneObject(eSceneObjMovie);
}

void GameScene::DelAllSceneObj()  //ɾ�����еĳ�������
{
	for (size_t type = eSceneObjItem; type < eSceneObjMax; type++)
	{
		RemoveSceneObject((eSceneObjType)type);
	}
}

MovieSceneNpc* GameScene::FindMovieSceneNpcByID(int64_t npcID)
{
	SceneObjMap::iterator it= m_SceneSprite[eSceneObjMovie].find(npcID);
	if (it != m_SceneSprite[eSceneObjMovie].end())
	{
		return static_cast<MovieSceneNpc*>(it->second);
	}
	return NULL;
}

void GameScene::OnSceneMovieChangeMap(int newMapId,int oldMoveMapID,int Logic_X, int Logic_Y) //��������ģʽ�е���ת��ͼ
{
	int mapconfigid = GetTableNumberFromLua("map.cmapconfig", newMapId, "id");

	if (mapconfigid == -1)
	{
		return;
	}
	
	if (!gGetGameApplication()->isFirstEnterGame() && !gIsInBackground())
    {
        int worldPicHandle=Nuclear::GetEngine()->CaptureWorld();
        
        m_iMovieCapturePic=worldPicHandle;
    }
    
	AddMovieSceneNpc(1,MHSD_UTILS::GETSTRING(993).c_str(),0,5001,0,0,0,1);
	MovieSceneNpc* pMovieNpc=FindMovieSceneNpcByID(1);
	if (pMovieNpc!=NULL)
	{
		AttachCameraTo(pMovieNpc->GetSprite());
		pMovieNpc->SetVisible(false);
	}
	
	Nuclear::XPLoadmapParam lmParam;
	Nuclear::NuclearLocation LogicLoc(Logic_X,Logic_Y);
	lmParam.objLoc=LogicLoc;
	if (newMapId != oldMoveMapID)
	{
		if (gGetSceneMovieManager())
		{
			gGetSceneMovieManager()->RemoveAllMovieEffect();
		}
		Nuclear::GetEngine()->GetWorld()->LoadMap(GetTableWStringFromLua("map.cmapconfig", mapconfigid, "resdir"), GetTableWStringFromLua("map.cmapconfig", mapconfigid, "resdir") + L"/maze.dat", &lmParam, false);
        
		if (pMovieNpc!=NULL)
		{
			pMovieNpc->SetLogicLocation(Logic_X,Logic_Y);
		}
	}
	else
	{
		AttachCameraTo(NULL);
		Nuclear::NuclearLocation pixLoc=Nuclear::NuclearWorldLogicCoord::logic2world(LogicLoc);
		Nuclear::NuclearPoint pt(pixLoc.x,pixLoc.y);
		Nuclear::GetEngine()->GetWorld()->SetViewport(pixLoc,true);
	}
    
    ReleaseMovieCapturePic();	
}

void GameScene::ReleaseAllJumpPointEffect()
{
	std::vector<Nuclear::IEffect*>::iterator it=m_vecJumpPointEffect.begin();
	for (;it!=m_vecJumpPointEffect.end();++it)
	{
		Nuclear::GetEngine()->GetWorld()->RemoveEffect(*it);
	}
	m_vecJumpPointEffect.clear();
}

//������ת��
void GameScene::LoadJumpMapPointInf()
{
	ReleaseAllJumpPointEffect();
	std::wstring strGotoXmlPath = L"/map/" + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir") + L"/goto.dat";
    
	std::wstring strJumpEffectName = L"";	
    
	char* fileBuf = NULL;
	std::streamsize ss = 0;

	GetMainCharacter()->SetIsSending(false);
	jumpPoint1 = Nuclear::NuclearLocation(-10, -10);
	jumpToPoint1 = Nuclear::NuclearLocation(-10, -10);
	jumpMapId1 = 0;

	jumpPoint2 = Nuclear::NuclearLocation(-10, -10);
	jumpToPoint2 = Nuclear::NuclearLocation(-10, -10);
	jumpMapId2 = 0;

	if (GetBuffFromFile(strGotoXmlPath, fileBuf, ss) != 0)
	{
		return;
	}

	std::wstring fileData;
	LJXMLStringHelper::EncodeLJ codeType;
	if (!LJXMLStringHelper::reallyLoadFromMemory((unsigned char*)fileBuf, ss, fileData, codeType))
	{
		delete[] fileBuf;
		return;
	}

	delete[] fileBuf;

	LJXML::LJXML_Doc<LJXML::Char> doc;
	LJXML::Char* charData = doc.LoadFromString(fileData);
	if (!doc.first_node())
	{
		return;
	}

	LJXML::LJXML_Node<LJXML::Char>* root = (LJXML::LJXML_Node<LJXML::Char>*)doc.first_node();
	LJXML::LJXML_NodeList typenl;
	root->GetSubNodeList(typenl);

	int firstrecord = g_jumpAreaUseGridCount*g_jumpAreaUseGridCount / 2;
	int step = g_jumpAreaUseGridCount*g_jumpAreaUseGridCount;
	if (step > (int)typenl.size())
	{
		return;
	}

	for (size_t curIdx = firstrecord; curIdx < typenl.size(); curIdx += step)
	{
		int pos_X = _wtoi(typenl[curIdx]->first_attribute(L"posx")->value());
		int pos_Y = _wtoi(typenl[curIdx]->first_attribute(L"posy")->value());
		int destX = _wtoi(typenl[curIdx]->first_attribute(L"destx")->value());
		int destY = _wtoi(typenl[curIdx]->first_attribute(L"desty")->value());
		int destmap = _wtoi(typenl[curIdx]->first_attribute(L"destmap")->value());
		if (curIdx == firstrecord)
		{
			jumpPoint1 = Nuclear::NuclearLocation(pos_X, pos_Y);
			jumpToPoint1 = Nuclear::NuclearLocation(destX, destY);
			jumpMapId1 = destmap;
		}
		else
		{
			jumpPoint2 = Nuclear::NuclearLocation(pos_X, pos_Y);
			jumpToPoint2 = Nuclear::NuclearLocation(destX, destY);
			jumpMapId2 = destmap;
		}

		if ((destmap >= 1300 && destmap < 1400) || (m_MapInfoId >= 1300 && m_MapInfoId < 1400))
			strJumpEffectName = MHSD_UTILS::GetEffectPath(10062);
		else
			strJumpEffectName = MHSD_UTILS::GetEffectPath(10063);

		Nuclear::IEffect* pEffect = Nuclear::GetEngine()->GetWorld()->SetEffect(strJumpEffectName, Nuclear::XPEL_NORMAL_UNDER_SPRITE, pos_X*g_gridWidth, pos_Y*g_gridHeight, true);
		if (pEffect != NULL)
		{
			m_vecJumpPointEffect.push_back(pEffect);
		}
	}
}

void GameScene::HideJumpEffect()
{
	m_bJunmPointEffectShow = false;
	std::vector<Nuclear::IEffect*>::iterator it = m_vecJumpPointEffect.begin();
	for (; it != m_vecJumpPointEffect.end(); ++it)
	{
		Nuclear::Effect* pEffect = static_cast<Nuclear::Effect*>(*it);
		if (pEffect)
			pEffect->SetVisibility(false);
	}
}

void GameScene::ShowJumpEffect()
{
	m_bJunmPointEffectShow = true;
	std::vector<Nuclear::IEffect*>::iterator it = m_vecJumpPointEffect.begin();
	for (; it != m_vecJumpPointEffect.end(); ++it)
	{
		Nuclear::Effect* pEffect = static_cast<Nuclear::Effect*>(*it);
		if (pEffect)
			pEffect->SetVisibility(true);
	}
}

bool GameScene::getJumpEffectShow()
{
	return m_bJunmPointEffectShow;
}

void GameScene::setJumpEffectShow(bool show)
{
	m_bJunmPointEffectShow = show;
}

void GameScene::AddSceneParticle(const std::wstring& strEffectName,float width,float height,float x,float y,bool cycle)
{
	Nuclear::IParticleManager* pParMgr=Nuclear::GetEngine()->GetRenderer()->GetParticleManager();
	if (pParMgr!=NULL)
	{
		Nuclear::PSParameter pspara;
		pspara.autorender = true;
		pspara.layer = 1;
		pspara.cycle = cycle;
		pspara.m_bScreenCoord=true;
		pspara.m_psModifyParam.m_pointCent.x = x;
		pspara.m_psModifyParam.m_pointCent.y = y;
		pspara.m_psModifyParam.m_fRctWidth = width;
		pspara.m_psModifyParam.m_fRctHeight = height;
		pspara.time = 50000;
		int handle=pParMgr->CreateParticleSystem(strEffectName,pspara,true,true);
		m_ParticleList.push_back(handle);
	}
}

//ɾ��һ��������Ч
void GameScene::RemoveSceneParticle(int handle)
{
	for (std::list<int>::iterator it=m_ParticleList.begin();it!=m_ParticleList.end();it++)
	{
		if (handle == (*it))
		{
			Nuclear::IParticleManager* pParMgr=Nuclear::GetEngine()->GetRenderer()->GetParticleManager();
			if (pParMgr!=NULL)
			{
				pParMgr->DeleteParticleSystem(handle);
			}
			it = m_ParticleList.erase(it);
			break;
		}
	}
	
}

void GameScene::BeginDreamFade()
{
	if (m_pEnterDreamEffect == NULL)
	{
		int curMapID=m_MapInfoId;
		GameTable::EffectPath::CEffectPath path = GameTable::EffectPath::GetCEffectPathTableInstance().getRecorder(curMapID);
		if (path.id!=-1)
		{
			m_pEnterDreamEffect=Nuclear::GetEngine()->CreateEffect(path.Patn);
			if(m_pEnterDreamEffect)
			{
				m_pEnterDreamEffect->AddNotify(new EnterDreamEffectNotify);
				Nuclear::NuclearDisplayMode mode=Nuclear::GetEngine()->GetRenderer()->GetDisplayMode();
				m_pEnterDreamEffect->SetLocation(Nuclear::NuclearLocation(mode.width/2,mode.height/2));
			}
		}
	}
    
	m_bIsInDreamFade=true;
	m_iDreamFadeElapseTime=0;
	m_iDreamTotalFadeTime=4125;
}

void GameScene::SetDreamFadeTime(int time)
{
	m_iDreamTotalFadeTime = time;
}

void GameScene::SetDreamHideSceneTime(int time)
{
	m_iDreamHideSceneTime = time;
}

int GameScene::GetDreamHideSceneTime()
{
	return m_iDreamHideSceneTime;
}

void GameScene::SetDreamStatus(int dreamStatus)
{
	if (m_DreamStatus!=dreamStatus)
	{
		if (m_DreamStatus!=0)
		{
			HideSceneEffect* pBlack=new HideSceneEffect;  //�ڵ�ͼЧ��
			std::wstring blackRes(L"/image/loading/hei.tga");
			int blackHandle=Nuclear::GetEngine()->GetRenderer()->LoadPicture(blackRes);
			if (blackHandle!=Nuclear::INVALID_PICTURE_HANDLE&&pBlack)
			{
				pBlack->SetTotalTime(m_iDreamHideSceneTime);
				pBlack->SetPictureHandle(blackHandle);
				AddSceneEffect(pBlack);
			}
            
			DreamFadeEffect* pDreamEffect=new DreamFadeEffect;
			pDreamEffect->SetIsRenderTarget(true);
			AddSceneEffect(pDreamEffect);
		}
		
		if ((m_DreamStatus==0&&dreamStatus==2)
			||(m_DreamStatus==1&&dreamStatus==2)
			||(m_DreamStatus == 3&&dreamStatus==2)
			)
		{
			m_bIsInDreamFade=true;
		}
        
		if (m_DreamStatus==0&&dreamStatus==1)    //��Ϊ�տ�ʼ����ʱ��Ϊ�����״̬
		{
			m_bIsInDreamFade=false;
		}
		m_DreamStatus=dreamStatus;
		if (m_DreamStatus==2&&m_pOnDreamEffect==NULL)
		{
			OnChangeDisplayMode();
		}
		
		if (!isOnDreamScene()&&m_pOnDreamEffect)
		{
			Nuclear::GetEngine()->ReleaseEffect(m_pOnDreamEffect);
			m_pOnDreamEffect=NULL;
		}
	}
}

bool GameScene::CanEnterDream()
{
	if (GetBattleManager()->IsInBattle())
	{
		return false;
	}
    
	return true;
}

bool GameScene::isOnDreamScene()
{
	return m_DreamStatus == 2 ? true : false;
}

void GameScene::DrawDreamImage() //������-����ģʽ�ı���ͼ
{
    if (GetBattleManager()->IsInBattle()) return;
    
	if (isOnDreamScene())
	{
		if (m_pOnDreamEffect)
		{
			Nuclear::GetEngine()->DrawEffect(m_pOnDreamEffect);
		}
	}
    
	if (m_bIsInDreamFade)
	{
		if (m_pEnterDreamEffect)
		{
			Nuclear::GetEngine()->DrawEffect(m_pEnterDreamEffect);
		}
	}
}

bool GameScene::isOnDreamFade()
{
	return m_bIsInDreamFade;
}

int GameScene::getJumpMapID(Nuclear::NuclearLocation pt)
{
	int a = abs(pt.x - jumpPoint1.x);
	int b = abs(pt.y - jumpPoint1.y);
	if (abs(pt.x - jumpPoint1.x) <= 5 && abs(pt.y - jumpPoint1.y) <= 5)
	{
		return jumpMapId1;
	}
	if (abs(pt.x - jumpPoint2.x) <= 5 && abs(pt.y - jumpPoint2.y) <= 5)
	{
		return jumpMapId2;
	}
	return -1;
}

Nuclear::NuclearLocation GameScene::getJumpPointByMapId(int mapId)
{
	if (mapId == jumpMapId1)
	{
		return jumpToPoint1;
	}
	else
	{
		return jumpToPoint2;
	}
}

void GameScene::DrawEnterMapNameEffect()
{
	if (m_bIsOnDrawEnterMapNameEffect&&m_iEnterMapNameEffect!=Nuclear::INVALID_PICTURE_HANDLE)
	{
		
		Nuclear::NuclearDisplayMode mode=Nuclear::GetEngine()->GetRenderer()->GetDisplayMode();
		Nuclear::NuclearFRectt rect(0.0f,0.0f,(float)mode.width,(float)mode.height);
		Nuclear::NuclearPictureInfo picInf;
		Nuclear::GetEngine()->GetRenderer()->GetPictureInfo(m_iEnterMapNameEffect,picInf);
		rect.left=rect.right-300.0f;
		rect.right=rect.left+(float)picInf.m_nPicWidth;
		rect.top=105.0f;
		rect.bottom=rect.top+(float)picInf.m_nPicHeight;
        
		unsigned char alpha=255;
		float scale=(float)m_iEnterMapElapseTime/(float)s_iTotalDrawEnterMapNameTime;
		scale=sinf(scale*PI);
		alpha=(unsigned char)(scale*255.0f);
		Nuclear::NuclearColor color(alpha,255,255,255);
		Nuclear::GetEngine()->GetRenderer()->DrawPicture(m_iEnterMapNameEffect,rect,color);
	}
    
}
void GameScene::EndDrawEnterMapNameEffect()
{
	m_bIsOnDrawEnterMapNameEffect=false;
	if (m_iEnterMapNameEffect!=Nuclear::INVALID_PICTURE_HANDLE)
	{
		Nuclear::GetEngine()->GetRenderer()->FreePicture(m_iEnterMapNameEffect);
	}
	m_iEnterMapNameEffect=Nuclear::INVALID_PICTURE_HANDLE;
	m_iEnterMapElapseTime=0;
}

bool GameScene::IsMySchoolMap(int mapid)
{
	return false;
}

bool GameScene::IsMySchoolInsideMap(int mapid)
{
	return false;
}

bool GameScene::IsInMySchoolInsideMap()
{
	return false;
}

bool GameScene::IsInMySchoolMap()
{
	return false;
}

bool GameScene::IsInLinanMap()
{
	return m_MapInfoId == 1007;
}

bool GameScene::IsInLinanNeijingMap()
{
	return m_MapInfoId >= 1370 && m_MapInfoId <= 1376;
}

bool GameScene::IsInLinanNeijingMap(int mapid)
{
	return mapid >= 1370 && mapid <= 1376;
}

int GameScene::GetMySchoolChefuPosition(Nuclear::NuclearLocation& loc)
{
	int chefuid = 0;

	for (IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.begin(); it != m_ClientNpcMap.end(); ++it)
	{
		const stClientNpcInfo& clientNpcInfo = it->second;

		int npcid = it->first;
		int NpcBaseid = clientNpcInfo.baseId;
		if (NpcBaseid == -1 || GetTableNumberFromLua("npc.cnpcconfig", npcid, "npctype") != eNpcTypeTranslate)
		{
			continue;
		}
		else
		{
			chefuid = npcid;
			loc = clientNpcInfo.loc;
			break;
		}
	}

	return chefuid;
}

int GameScene::GetLinanChefuPosition(Nuclear::NuclearLocation& loc)
{
	int chefuid = 0;

	for (IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.begin(); it != m_ClientNpcMap.end(); ++it)
	{
		const stClientNpcInfo& clientNpcInfo = it->second;

		int npcid = it->first;
		int NpcBaseid = clientNpcInfo.baseId;
		if (NpcBaseid == 10122)
		{
			chefuid = npcid;
			loc = clientNpcInfo.loc;
			break;
		}
	}

	return chefuid;
}
void GameScene::getGuaJiMapNpc()
{
	for (IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.begin(); it != m_ClientNpcMap.end(); ++it)
	{
		const stClientNpcInfo& clientNpcInfo = it->second;
		
		int npcid = it->first;
		int x = clientNpcInfo.loc.x;
		int y = clientNpcInfo.loc.y;
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithParamsData("SmallMapDlg.InitNpcList", npcid, x, y, 0);
	}
}



void GameScene::AttachCameraTo(Nuclear::ISprite* pXPSprite)
{
	Nuclear::GetEngine()->GetWorld()->AttachCameraTo(pXPSprite);
}

bool GameScene::SelectObjs(const Nuclear::NuclearLocation &loc, std::vector<Nuclear::ISelectableObj*> &objs)
{
	return Nuclear::GetEngine()->GetWorld()->SelectObjs(loc, objs);
}

int GameScene::GetFamilyManagerPosition(Nuclear::NuclearLocation& loc)
{
	int chefuid = 0;

	for (IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.begin(); it != m_ClientNpcMap.end(); ++it)
	{
		const stClientNpcInfo& clientNpcInfo = it->second;

		int npcid = it->first;
		int NpcBaseid = clientNpcInfo.baseId;
		if (NpcBaseid == 10057)
		{
			chefuid = npcid;
			loc = clientNpcInfo.loc;
			break;
		}
	}

	return chefuid;
}

//�õ�NPC�ڿͻ������õķ���
Nuclear::NuclearDirection GameScene::GetClientConfigNpcDirByBaseID(int npcbaseID)
{
	IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.find(npcbaseID);
	if (it != m_ClientNpcMap.end())
	{
		const stClientNpcInfo& clientNpcInfo = it->second;
		return clientNpcInfo.dir;
	}

	return Nuclear::XPDIR_BOTTOMLEFT;
}

void GameScene::OnChangeDisplayMode()
{
	Nuclear::NuclearDisplayMode XPmode=Nuclear::GetEngine()->GetRenderer()->GetDisplayMode();
	if (isOnDreamScene())
	{
		if (m_pOnDreamEffect==NULL)
		{
			m_pOnDreamEffect=Nuclear::GetEngine()->CreateEffect(MHSD_UTILS::GetEffectPath(10091));
		}
		if (m_pOnDreamEffect)
		{
			float xScale=(float)XPmode.width/1024.0f;
			float yScale=(float)XPmode.height/768.0f;
			m_pOnDreamEffect->SetLocation(Nuclear::NuclearLocation(XPmode.width/2,XPmode.height/2));
            
			m_pOnDreamEffect->SetScale(Nuclear::NuclearFPoint(xScale,yScale));
		}
        
	}
	if (m_pEnterDreamEffect)
	{
		m_pEnterDreamEffect->SetLocation(Nuclear::NuclearLocation(XPmode.width/2,XPmode.height/2));
	}
}

int GameScene::GetDreamState()
{
	return m_DreamStatus;
}

void GameScene::EmptyEnterDreamEffect()
{
	m_pEnterDreamEffect = NULL;
	m_bIsInDreamFade = false;
}

void GameScene::EnableJumpMapFadeEffect(bool b)  //�Ƿ�������ͼʱ�Ƿ��黯Ч��
{
	m_bEnbaleJumpMapFadeEffect=b;
}

void GameScene::ToggleEnableJumpMapFadeEffect()
{
	m_bEnbaleJumpMapFadeEffect = !m_bEnbaleJumpMapFadeEffect;
}

void GameScene::DrawSceneEffect()
{
	VECSceneEffect::iterator it=m_vecSceneEffect.begin();
	for (;it!=m_vecSceneEffect.end();++it)
	{
		(*it)->Draw();
	}
    
}
void GameScene::ClearSceneEffect()
{
	VECSceneEffect::iterator it=m_vecSceneEffect.begin();
	for (;it!=m_vecSceneEffect.end();++it)
	{
		(*it)->End(false);
		delete *it;
	}
	m_vecSceneEffect.clear();
    
}
void GameScene::AddSceneEffect(SceneEffect* pEffect)
{
	if (NULL!=pEffect)
	{
		pEffect->Start();
		m_vecSceneEffect.push_back(pEffect);
	}
    
}
void GameScene::RemoveSceneEffect(SceneEffect* pEffect)
{
	VECSceneEffect::iterator it=std::find(m_vecSceneEffect.begin(),m_vecSceneEffect.end(),pEffect);
	if (it!=m_vecSceneEffect.end())
	{
		(*it)->End(false);
		delete *it;
		m_vecSceneEffect.erase(it);
	}
    
}

void GameScene::BeginEnterMovieEffect(int handle)
{
	SceneEffect* pWorldCapture=new SceneEffect;
	if(pWorldCapture&&handle!=Nuclear::INVALID_PICTURE_HANDLE)
	{
		pWorldCapture->SetPictureHandle(handle);
		pWorldCapture->SetIsRenderTarget(true);
		pWorldCapture->SetTotalTime(s_iTotalEnterMovieEffectTime/2);
		AddSceneEffect(pWorldCapture);
	}
    
	EnterMoiveBlendEffect* pShowAlpha=new EnterMoiveBlendEffect;  //��͸����ͼЧ��
	std::wstring alphaRes(L"/image/loading/bandou.tga");
	int alphaHandle=Nuclear::GetEngine()->GetRenderer()->LoadPicture(alphaRes);
	if (alphaHandle!=Nuclear::INVALID_PICTURE_HANDLE&&pShowAlpha)
	{
		pShowAlpha->SetTotalTime(s_iTotalEnterMovieEffectTime);
		pShowAlpha->SetPictureHandle(alphaHandle);
		AddSceneEffect(pShowAlpha);
	}
    
	EnterMoiveBlackEffect* pBlack=new EnterMoiveBlackEffect;  //�ڵ�ͼЧ��
	std::wstring blackRes(L"/image/loading/hei.tga");
	int blackHandle=Nuclear::GetEngine()->GetRenderer()->LoadPicture(blackRes);
	if (blackHandle!=Nuclear::INVALID_PICTURE_HANDLE&&pShowAlpha)
	{
		pBlack->SetTotalTime(s_iTotalEnterMovieEffectTime*3/4);
		pBlack->SetPictureHandle(blackHandle);
		AddSceneEffect(pBlack);
	}
}

void GameScene::ReleaseFinishQuestEffect()
{
	if(NULL != m_pFinishQuestEffect)
	{
		Nuclear::GetEngine()->ReleaseEffect(m_pFinishQuestEffect);
		m_pFinishQuestEffect = NULL;
	}
}

//���ؿͻ��˵�npc������Ϣ
void GameScene::LoadClientNpcInfo()
{
	std::wstring strMinimapPath = L"/map/";
	strMinimapPath += GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "resdir");
	std::wstring strMapNpcXmlPath = strMinimapPath + L"/npc.dat";

	char* fileBuf = NULL;
	std::streamsize ss = 0;
	if (GetBuffFromFile(strMapNpcXmlPath, fileBuf, ss) != 0)
	{
		return ;
	}

	std::wstring fileData;
	LJXMLStringHelper::EncodeLJ codeType;
	if (!LJXMLStringHelper::reallyLoadFromMemory((unsigned char*)fileBuf, ss, fileData, codeType))
	{
		delete[] fileBuf;
		return ;
	}

	delete[] fileBuf;

	LJXML::LJXML_Doc<LJXML::Char> doc;
	LJXML::Char* charData = doc.LoadFromString(fileData);
	if (!doc.first_node())
	{
		return;
	}
	LJXML::LJXML_Node<LJXML::Char>* root = (LJXML::LJXML_Node<LJXML::Char>*)doc.first_node();
	LJXML::LJXML_NodeList typenl;
	root->GetSubNodeList(typenl);
	for (size_t i = 0; i < typenl.size(); i++)
	{
		int id = _wtoi(typenl[i]->first_attribute(L"id")->value()); //typeIt->GetAttributeInteger(L"id");
		int NpcBaseid = GetTableNumberFromLua("npc.cnpcconfig", id, "id");
		if (NpcBaseid == -1 || GetTableWStringFromLua("npc.cnpcconfig", id, "minimapquery").empty() == true)
		{
			continue;
		}
		stClientNpcInfo NpcInfo;
		NpcInfo.baseId = NpcBaseid;
		NpcInfo.dir = Nuclear::NuclearDirection(_wtoi(typenl[i]->first_attribute(L"dir")->value())/*typeIt->GetAttributeInteger(L"dir")*/);
		NpcInfo.loc = Nuclear::NuclearLocation(_wtoi(typenl[i]->first_attribute(L"posx")->value()), _wtoi(typenl[i]->first_attribute(L"posy")->value())/*typeIt->GetAttributeInteger(L"posx"), typeIt->GetAttributeInteger(L"posy")*/);
		m_ClientNpcMap[id] = NpcInfo;
	}
}

//��õ�ͼ�ϵ�npc����
int GameScene::GetClientNpcCount()
{
	int npcCount = 0;
	
	for (IdToClientNpcInfoMap::iterator it = m_ClientNpcMap.begin(); it != m_ClientNpcMap.end(); ++it)
	{
		int id = it->first;
		if (GetTableNumberFromLua("npc.cnpcconfig", id, "npctype") >= 1 && GetTableNumberFromLua("npc.cnpcconfig", id, "npctype") <= 4 && GetTableNumberFromLua("npc.cnpcconfig", id, "hide") == 0)
		{
			npcCount++;
		}
	}

	return npcCount;
}

//����npc�� �õ��þ���npc������character���� С��g_gridDistance 13�������㿿��
int GameScene::GetNearByCharacterNum(const Nuclear::NuclearLocation& scenenpcloc,const int& idistance)
{
	int num=0;
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		if (Nuclear::distance(itor->second->GetLogicLocation(),scenenpcloc) < idistance)
		{
			num++;
		}
	}
	return num;
}

//�õ�midpos������λ�ã�radiusΪ�뾶
Nuclear::NuclearLocation GameScene::GetNearByPos(SceneObject* pObject,int radius)
{
	if (NULL == pObject)
	{
		return Nuclear::NuclearLocation(0,0);
	}
	Nuclear::NuclearLocation midpos = pObject->GetLogicLocation();
	
	eMoveMask movemask = pObject->IsInHighLevel()?eMoveMaskHigh:eMoveMaskNormal;
    
	int randombegin = rand()%(2*radius+1) - radius;
	for (int i=randombegin;i<radius;i++)
	{
		int index = rand()%4;
		Nuclear::NuclearLocation target = midpos+gGetRandomDirection(index,i,radius);
		if (!IsMoveBlock(target,movemask))
			return target;
		else
		{
			index++;
			target = midpos+gGetRandomDirection(index,i,radius);
			if (!IsMoveBlock(target,movemask))
				return target;
			else
			{
				index++;
				target = midpos+gGetRandomDirection(index,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
				else
				{
					index++;
					target = midpos+gGetRandomDirection(index,i,radius);
					if (!IsMoveBlock(target,movemask))
						return target;
				}
			}
		}
	}
	for (int i=-radius;i<randombegin;i++)
	{
		int index = rand()%4;
		Nuclear::NuclearLocation target = midpos+gGetRandomDirection(index,i,radius);
		if (!IsMoveBlock(target,movemask))
			return target;
		else
		{
			index++;
			target = midpos+gGetRandomDirection(index,i,radius);
			if (!IsMoveBlock(target,movemask))
				return target;
			else
			{
				index++;
				target = midpos+gGetRandomDirection(index,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
				else
				{
					index++;
					target = midpos+gGetRandomDirection(index,i,radius);
					if (!IsMoveBlock(target,movemask))
						return target;
				}
			}
		}
	}
	return midpos;
}

//�õ�midpos������λ�ã�radiusΪ�뾶�����ȿ���Y����ƫ��
Nuclear::NuclearLocation GameScene::GetNearByPosPreferY(Nuclear::NuclearLocation midpos,int radius,bool bhighlevel)
{
	eMoveMask movemask = bhighlevel?eMoveMaskHigh:eMoveMaskNormal;
	
	//�������±�һ����
	if (rand()%2 == 0)
	{
		int randombegin = 0;
		if (GetMainCharacter()->GetLogicLocation().x >= midpos.x)
		{
			randombegin = rand()%radius;
			for (int i=randombegin;i<=radius;i++)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=-radius;i--)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
		else
		{
			randombegin = -rand()%radius;
			for (int i=randombegin;i>=-radius;i--)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin+1;i<=radius;i++)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
		randombegin = rand()%radius;
		if (GetMainCharacter()->GetLogicLocation().x >= midpos.x)
		{
			for (int i=randombegin;i<=radius;i++)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin;i<=radius;i++)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
		else
		{
			for (int i=randombegin;i<=radius;i++)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin;i<=radius;i++)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
	}
	//�����������ߵ��°벿��
	else
	{
		int randombegin = rand()%radius;
		if (GetMainCharacter()->GetLogicLocation().x >= midpos.x)
		{
			for (int i=randombegin;i<=radius;i++)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin;i<=radius;i++)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			randombegin = rand()%radius;
			for (int i=randombegin;i<=radius;i++)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=-radius;i--)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
		else
		{
			for (int i=randombegin;i<=radius;i++)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//3����������
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(3,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin;i<=radius;i++)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin-1;i>=0;i--)
			{
				//2���������ҷ�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(2,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			randombegin = -rand()%radius;
			for (int i=randombegin;i>=-radius;i--)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
			for (int i=randombegin+1;i<=radius;i++)
			{
				//0���������·�
				Nuclear::NuclearLocation target = midpos+gGetRandomDirection(0,i,radius);
				if (!IsMoveBlock(target,movemask))
					return target;
			}
		}
	}
	return midpos;
}

//����npc�Ƿ�ɼ����
void GameScene::UpdateInstanceNpcVisible(int npcbaseid,bool bvisible)
{
	for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end();itor++)
	{
		Npc* pNpc = static_cast<Npc*>(itor->second);
		if (pNpc->GetNpcBaseID() == npcbaseid)
		{
			pNpc->SetVisible(bvisible);
		}
	}
}

int64_t GameScene::GetTimeByString(const std::wstring& strTime)
{
	int year=0;
	int month=0;
	int day=0;
	int hour=0;
	int minute=0;
	int second=0;
    
#ifdef ANDROID
    std::string str = SHARE_Wstring2String(strTime);
    sscanf(str.c_str(), "%d-%d-%d %d-%d-%d", &year,&month,&day,&hour,&minute,&second);
#else
    swscanf(strTime.c_str(),L"%d-%d-%d %d-%d-%d",&year,&month,&day,&hour,&minute,&second);
#endif

	struct tm times;
    
	times.tm_year=year-1900;
	times.tm_mon=month-1;
	times.tm_mday=day;
	times.tm_hour=hour;
	times.tm_min=minute;
	times.tm_sec=second;
    times.tm_isdst=0;
    
	return mktime(&times);
}


bool GameScene::LoadNpcAutoPopInf() //����npc�Զ�ð������ʾ��ĩ���Ϣ
{
	return false;
}


void GameScene::InitNpcAutoPopo() //��ʼ��npc�Զ�ð������ʾ��ĩ�
{
	if (!LoadNpcAutoPopInf())
	{
		return;
	}

	int64_t curTime=gGetServerTime()/1000;
	time_t et = curTime;
	struct tm times;
	localtime_s(&times,&et);
	if (times.tm_sec==0)
	{
		CheckNpcAutoPopo();
		StartNpcAutoPopoTimer();
	}else
	{
		if (times.tm_sec<60)
		{
			int elapseSecond=60-times.tm_sec;
            m_bStartNpcAutoPopoTimer = true;
            m_fStartNpcAutoPopoTimer = elapseSecond * 1000;
		}else
		{
			return;
		}
	}
}

void GameScene::CheckNpcAutoPopo()//ÿ�����ӿ���ʲô����Ҫð
{
	int64_t curTime=gGetServerTime()/1000;

	std::vector<stNpcAutoPopoInf>::iterator it=m_vecNpcAutoPopoInf.begin();
	for (;it!=m_vecNpcAutoPopoInf.end();)
	{
		int64_t iStartTime=(*it).startTime;
		int64_t iEndTime=(*it).endTime;
		int64_t interval=(int64_t)((*it).interval);
		if (curTime<=iEndTime)
		{
			if (curTime>=iStartTime)
			{
				int64_t elapseMinute= (curTime - (*it).lastTime) / 60;

				if (elapseMinute >= interval)
				{
                    (*it).lastTime = curTime;
					int npcID=(*it).npcBaseID;
					Npc* pNpc=FindNpcByBaseID(npcID);
					if (NULL!=pNpc)
					{
						if (NULL==GetBattleManager()
							||(GetBattleManager()&&!GetBattleManager()->IsInBattle()))
						{
							pNpc->AddTalk((*it).content,false);
						}

						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushIntegerToLuaStack(0);
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushIntegerToLuaStack(0);
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushIntegerToLuaStack(0);
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushIntegerToLuaStack(0);
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushStringToLuaStack(ws2s(pNpc->GetName()).c_str());
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->pushStringToLuaStack(ws2s((*it).content).c_str());
						cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunction("CChatManager.AddMsg_CurChannel_", 6);
					}
				}
			}
			++it;
		}else
		{
			it=m_vecNpcAutoPopoInf.erase(it);
		}
	}
    
}

void GameScene::StartNpcAutoPopoTimer() //��ʼ��Ӽ�ʱ��
{
    m_bStartNpcAutoPopoTimer = false;
    
	CheckNpcAutoPopo();
    m_bNpcAutoPopoTimer = true;
    m_fNpcAutoPopoTimer = s_iNpcAutoPopoTimerCDTime * 1000;
}

void GameScene::AddFirstEnterBlackEffect()
{
	EndFirstEnterBlackEffect();
    
	SceneEffect* pBlack=new SceneEffect;  //�ڵ�ͼЧ��
	std::wstring blackRes(L"/image/loading/hei.tga");
	int blackHandle=Nuclear::GetEngine()->GetRenderer()->LoadPicture(blackRes);
	if (blackHandle!=Nuclear::INVALID_PICTURE_HANDLE&&pBlack)
	{
		pBlack->SetTotalTime(5*60*1000);
		pBlack->SetPictureHandle(blackHandle);
		AddSceneEffect(pBlack);
		m_pFirstEnterBlackEffect=pBlack;
	}
}

void GameScene::EndFirstEnterBlackEffect()
{
	if (m_pFirstEnterBlackEffect!=NULL)
	{
		RemoveSceneEffect(m_pFirstEnterBlackEffect);
		m_pFirstEnterBlackEffect=NULL;
	}
}

void GameScene::SetFactionBossInfo(int64_t sceneid, int shapeid, int baseid)
{
	m_nFactionBossShapeID = shapeid;
	m_nFactionBossBaseID = baseid;
    
	UpdateFactionBossShape();
}

void GameScene::UpdateFactionBossShape()
{
	Npc* pNpc = FindNpcByBaseID(m_nFactionBossBaseID);
	if (pNpc != NULL)
	{
		pNpc->SetShapeID(m_nFactionBossShapeID);
		pNpc->SetVisible(true);
		pNpc->ChangeSpriteModel(m_nFactionBossShapeID);
	}
}

void GameScene::ShowFactionBossPickups()
{
	for (int i=14566; i<=14595; i++)
	{
		Npc* pPickupNpc = FindNpcByBaseID(i);
		if (pPickupNpc != NULL)
		{
			pPickupNpc->SetVisible(true);
		}
	}
}

void GameScene::HideFactionBossPickups()
{
	for (int i=14566; i<=14595; i++)
	{
		Npc* pPickupNpc = FindNpcByBaseID(i);
		if (pPickupNpc != NULL)
		{
			pPickupNpc->SetVisible(false);
		}
	}
}

bool GameScene::IsInPrison()
{
	int map_id = GetMapID();
	const int JIANYU_ID_1 = 1390;
	const int JIANYU_ID_2 = 1391;
    
	if (JIANYU_ID_1 == map_id || JIANYU_ID_2 == map_id)
	{
		return true;
	}
    
	return false;
}

void GameScene::OnDeleteSprite(Nuclear::ISprite* pISprite)
{
	for (SceneObjMap::iterator itor=m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end();itor++)
	{
		if (itor->second && itor->second->FitSprite(pISprite))
		{
			delete itor->second;
			itor->second = NULL;
			m_SceneSprite[eSceneObjNpc].erase(itor);
			return;
		}
	}
	for (SceneObjMap::iterator itor=m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++)
	{
		if (itor->second && itor->second->FitSprite(pISprite) && itor->second != GetMainCharacter())
		{
			delete itor->second;
			itor->second = NULL;
			m_SceneSprite[eSceneObjCharacter].erase(itor);
			return;
		}
	}
}

void GameScene::PlayMapBackGroundMusic()
{   
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    
    if (gGetGameConfigManager()&&gGetGameConfigManager()->isPlayBackMusic())
    {
		if (!GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "music").empty())
        {
			std::wstring ws = StringCover::to_wstring(g_musicResPath) + GetTableWStringFromLua("map.cmapconfig", m_MapInfoId, "music");
			std::string newSoundRes;
			std::wstring newws;
			newws = LJFM::LJFMF::GetFullPathFileName(ws);
			if (!newws.empty())
			{
				newSoundRes = StringCover::to_string(newws);
			}

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(newSoundRes.c_str(), true);
			int BackMusicValue = gGetGameConfigManager()->GetConfigValue(L"soundvalue");
			if (MusicSoundVolumeMixer::GetInstance())
				MusicSoundVolumeMixer::GetInstance()->setBackgroundMusicVolume((float)(BackMusicValue / 255.0f));
        }
    }
}

void GameScene::EnableJumpMapForAutoBattle(bool b)
{
	m_bJumpMapForAutoBattle = b;
}

void GameScene::DrawMovieCapturePic(float pro)
{
    if (m_iMovieCapturePic!=Nuclear::INVALID_PICTURE_HANDLE)
	{
		
		int alpha=255-(int)(255.0f*pro/100.0f);
        Nuclear::NuclearColor color(alpha,255,255,255);
		Nuclear::NuclearDisplayMode mode=Nuclear::GetEngine()->GetRenderer()->GetDisplayMode();
		Nuclear::NuclearFRectt rect(0.0f,0.0f,(float)mode.width,(float)mode.height);
		Nuclear::GetEngine()->GetRenderer()->DrawPicture(m_iMovieCapturePic,rect,color);
	}
}

void GameScene::ReleaseMovieCapturePic()
{
    if (m_iMovieCapturePic!=Nuclear::INVALID_PICTURE_HANDLE)
	{
        Nuclear::GetEngine()->GetRenderer()->FreeRenderTarget(m_iMovieCapturePic);
    }
}

int GameScene::GetSceneNPCNum()
{
	return GetSceneObject(eSceneObjNpc).size();
}

Npc* GameScene::GetSceneNPC(int num)
{
    int i = 1;
    for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjNpc].begin();itor != m_SceneSprite[eSceneObjNpc].end();itor++,i++)
    {
        if (num == i)
        {
            return static_cast<Npc*>(itor->second);
        }
    }
    return NULL;
}

int GameScene::GetSceneCharNum()
{
	return GetSceneObject(eSceneObjCharacter).size();
}

Character* GameScene::GetSceneCharacter(int num)
{
    int i = 1;
    for (SceneObjMap::iterator itor = m_SceneSprite[eSceneObjCharacter].begin();itor != m_SceneSprite[eSceneObjCharacter].end();itor++,i++)
    {
        if (num == i)
        {
            return static_cast<Character*>(itor->second);
        }
    }
    return NULL;
}

bool GameScene::IsInFuben()
{
    int special = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeGlobalFunctionWithIntegerData("ShowHide.IsSpecialFuben", GetMapInfo());

    if(special)
    {
        return true;
    }
	else
	{
		return GetTableNumberFromLua("map.cmapconfig", GetMapInfo(), "dynamic") > 0;
	}

}

int GameScene::GetMapBattleGroundID()
{
	return 0;
}

int GameScene::GetMapDataID()
{
	return m_MapDataID;
}

int64_t GameScene::GetMapSceneID()
{
	return m_MapSceneID;
}

eNpcMissionState GameScene::GetNpcStateByID(int64_t npckey, int npcbaseid)
{
	cocos2d::CCScriptEngineProtocol* pScriptEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
	if (pScriptEngine)
	{
		CallLuaUtil util;
		util.addArg(npckey);
		util.addArg(npcbaseid);
		if (util.callLua(pScriptEngine->getLuaState(), "TaskManager_CToLua_GetNpcStateByID"))
		{
			return (eNpcMissionState)util.getRetInt();
		}
	}

	return eNpcMissionNoQuest;
}

SceneObjMap& GameScene::GetSceneObject(eSceneObjType type)
{
	return m_SceneSprite[type];
}

std::vector<int> GameScene::GetAllNpcIDByType(eSceneObjType type) {
	std::vector<int> npcIDVec;
	for (SceneObjMap::iterator itor = m_SceneSprite[type].begin(); itor != m_SceneSprite[type].end();itor++)
	{
		Npc* pNpc = dynamic_cast<Npc*>(itor->second);
		npcIDVec.push_back(pNpc->GetNpcBaseID());
	}

	return npcIDVec;
}

void GameScene::ResetMouseOverObjectsListWithNpcBaseID(int  npcBaseID) {
	Npc* pNpc = FindNpcByBaseID(npcBaseID);
	if (!pNpc) return;
	m_MouseOverObjectsList.clear();
	m_MouseOverObjectsList.push_back(pNpc);
	m_pMouseOverObjects = pNpc;

}


Npc* GameScene::AddNpcCommon(stNpcData* pNpcData, eSceneObjType sceneObjType)
{
	if (!pNpcData)
		return NULL;
	Npc* pNpc = new Npc();
	if (pNpc == NULL)
		return NULL;

	int64_t nMapKey = 0;
	if (pNpcData->NpcID == 0)
	{
		nMapKey = static_cast<int64_t>(pNpcData->NpcBaseID);
	}
	else
	{
		nMapKey = pNpcData->NpcID;
	}
	if (pNpc->SetAttribute(pNpcData))
	{
		m_SceneSprite[sceneObjType][nMapKey] = pNpc;
	}
	else
	{
		delete pNpc;
		pNpc = NULL;
	}
	return pNpc;
}

void GameScene::addSceneTaskShowNpc(int nNpcId)
{
	int64_t nMapKey = static_cast<int64_t>(nNpcId);
	SceneObject* pSceneObj = FindSceneObjectByTypeID(eSceneObjTaskShowNpc, nMapKey);
	if (pSceneObj)
	{
		return;
	}
	int npcTableid = GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "id");
	if (npcTableid == -1)
		return;
	
	stNpcData npcData;
	npcData.ShapeID = GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "modelID");
	npcData.moveSpeed = 0;
	npcData.NpcBaseID = nNpcId;
	npcData.ptPos = Nuclear::NuclearLocation(GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "xPos")*g_logicGrid, GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "yPos") *g_logicGrid);
	npcData.dir = (Nuclear::NuclearDirection)GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "ndir"); //nstate
	npcData.strName = GetTableWStringFromLua("npc.cnpcconfig", nNpcId, "name");

	Npc* pNpc = AddNpcCommon(&npcData, eSceneObjTaskShowNpc);
	if (!pNpc)
		return;

	int nState = eActionStand;
	if (GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "nstate") > 0)
	{
		nState = GetTableNumberFromLua("npc.cnpcconfig", nNpcId, "nstate");
	}
	pNpc->SetVisible(true);
	if (nState == eActionDeath)
	{
		pNpc->SetDefaultAction(eActionType(eActionDeath), true);
	}
	else
	{
		pNpc->SetDefaultAction(eActionType(nState));
	}
}

void GameScene::deleteSceneTaskShowNpc(int nNpcId)
{
	SceneObject* pSceneObj = FindSceneObjectByTypeID(eSceneObjTaskShowNpc, nNpcId);
	if (!pSceneObj)
	{
		return;
	}
	RemoveSceneObjectByID(eSceneObjTaskShowNpc, nNpcId);
}

bool GameScene::handleConfirmPlayXinshouJuqing(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs& windowargs = static_cast<const  CEGUI::WindowEventArgs&>(e);
	stConfirmBoxInfo* pConfirmBoxInfo = static_cast<stConfirmBoxInfo*>(windowargs.window->getUserData());
	if (pConfirmBoxInfo)
	{
		isFirstJuqingPlayed = true;
		gGetSceneMovieManager()->EnterMovieScene(14001);
		gGetGameApplication()->setFirstTimeEnterGameValue(1);
		gGetMessageManager()->RemoveConfirmBox(pConfirmBoxInfo);
	}
	return true;
}

bool GameScene::handleCancelXinshouJuqing(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs& windowargs = static_cast<const  CEGUI::WindowEventArgs&>(e);
	stConfirmBoxInfo* pConfirmBoxInfo = static_cast<stConfirmBoxInfo*>(windowargs.window->getUserData());
	if (pConfirmBoxInfo)
	{
		isFirstJuqingPlayed = false;
		gGetGameApplication()->setFirstTimeEnterGameValue(10);
		gGetMessageManager()->RemoveConfirmBox(pConfirmBoxInfo);
	}
	return true;
}

Nuclear::NuclearLocation GameScene::getJumpPoint1Pos()
{
	return jumpPoint1;
}

void GameScene::pauseSceneEffects()
{
	Nuclear::GetEngine()->GetWorld()->pauseSceneEffects();
}

void GameScene::resumeSceneEffects()
{
	Nuclear::GetEngine()->GetWorld()->resumeSceneEffects();
}
