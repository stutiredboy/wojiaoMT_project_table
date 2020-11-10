
// GENERATE BY RPCGEN. DO NOT EDIT THIS FILE.

#include "rpcgen.hpp"
#include "__depends_rpcgen.hpp"
#include "protocols.hpp"


// protocol stubs
namespace ProtoDef { 
void _protocolsStubs(bool add)
{
	static aio::Protocol::TStub<fire::pb::BeanImport> fire_pb_BeanImport;
	static aio::Protocol::TStub<fire::pb::CAfterEnterWorld> fire_pb_CAfterEnterWorld;
	static aio::Protocol::TStub<fire::pb::CEndPlayCG> fire_pb_CEndPlayCG;
	static aio::Protocol::TStub<fire::pb::CEnterWorld> fire_pb_CEnterWorld;
	static aio::Protocol::TStub<fire::pb::CNotifyDeviceInfo> fire_pb_CNotifyDeviceInfo;
	static aio::Protocol::TStub<fire::pb::CPingStat> fire_pb_CPingStat;
	static aio::Protocol::TStub<fire::pb::CRoleList> fire_pb_CRoleList;
	static aio::Protocol::TStub<fire::pb::LuaBeanImport> fire_pb_LuaBeanImport;
	static aio::Protocol::TStub<fire::pb::battle::CEndWatchBattle> fire_pb_battle_CEndWatchBattle;
	static aio::Protocol::TStub<fire::pb::battle::CReqRePlay> fire_pb_battle_CReqRePlay;
	static aio::Protocol::TStub<fire::pb::battle::CSendAction> fire_pb_battle_CSendAction;
	static aio::Protocol::TStub<fire::pb::battle::CSendRoundPlayEnd> fire_pb_battle_CSendRoundPlayEnd;
	static aio::Protocol::TStub<fire::pb::battle::CStopRePlay> fire_pb_battle_CStopRePlay;
	static aio::Protocol::TStub<fire::pb::battle::SRemoveWatcher> fire_pb_battle_SRemoveWatcher;
	static aio::Protocol::TStub<fire::pb::battle::SReqRePlay> fire_pb_battle_SReqRePlay;
	static aio::Protocol::TStub<fire::pb::battle::SSendAddFighters> fire_pb_battle_SSendAddFighters;
	static aio::Protocol::TStub<fire::pb::battle::SSendBattleEnd> fire_pb_battle_SSendBattleEnd;
	static aio::Protocol::TStub<fire::pb::battle::SSendBattleStart> fire_pb_battle_SSendBattleStart;
	static aio::Protocol::TStub<fire::pb::battle::SSendCameraUrl> fire_pb_battle_SSendCameraUrl;
	static aio::Protocol::TStub<fire::pb::battle::SSendRoundScript> fire_pb_battle_SSendRoundScript;
	static aio::Protocol::TStub<fire::pb::battle::SSendRoundStart> fire_pb_battle_SSendRoundStart;
	static aio::Protocol::TStub<fire::pb::battle::newhand::CReqNewHandBattle> fire_pb_battle_newhand_CReqNewHandBattle;
	static aio::Protocol::TStub<fire::pb::circletask::CReqGotoPatrol> fire_pb_circletask_CReqGotoPatrol;
	static aio::Protocol::TStub<fire::pb::hook::CSetAutoBattle> fire_pb_hook_CSetAutoBattle;
	static aio::Protocol::TStub<fire::pb::mission::CMissionReachScene> fire_pb_mission_CMissionReachScene;
	static aio::Protocol::TStub<fire::pb::mission::CReqGoto> fire_pb_mission_CReqGoto;
	static aio::Protocol::TStub<fire::pb::move::CCheckMove> fire_pb_move_CCheckMove;
	static aio::Protocol::TStub<fire::pb::move::CRelocateRolePos> fire_pb_move_CRelocateRolePos;
	static aio::Protocol::TStub<fire::pb::move::CRoleMove> fire_pb_move_CRoleMove;
	static aio::Protocol::TStub<fire::pb::move::CRoleStop> fire_pb_move_CRoleStop;
	static aio::Protocol::TStub<fire::pb::move::CRoleTurn> fire_pb_move_CRoleTurn;
	static aio::Protocol::TStub<fire::pb::move::CSendAutoMovePathID> fire_pb_move_CSendAutoMovePathID;
	static aio::Protocol::TStub<fire::pb::npc::CVisitNpc> fire_pb_npc_CVisitNpc;
	static aio::Protocol::TStub<fire::pb::skill::CUseSceneSkill> fire_pb_skill_CUseSceneSkill;

	if (add)
	{
		aio::Protocol::AddStub(&fire_pb_BeanImport);
		aio::Protocol::AddStub(&fire_pb_CAfterEnterWorld);
		aio::Protocol::AddStub(&fire_pb_CEndPlayCG);
		aio::Protocol::AddStub(&fire_pb_CEnterWorld);
		aio::Protocol::AddStub(&fire_pb_CNotifyDeviceInfo);
		aio::Protocol::AddStub(&fire_pb_CPingStat);
		aio::Protocol::AddStub(&fire_pb_CRoleList);
		aio::Protocol::AddStub(&fire_pb_LuaBeanImport);
		aio::Protocol::AddStub(&fire_pb_battle_CEndWatchBattle);
		aio::Protocol::AddStub(&fire_pb_battle_CReqRePlay);
		aio::Protocol::AddStub(&fire_pb_battle_CSendAction);
		aio::Protocol::AddStub(&fire_pb_battle_CSendRoundPlayEnd);
		aio::Protocol::AddStub(&fire_pb_battle_CStopRePlay);
		aio::Protocol::AddStub(&fire_pb_battle_SRemoveWatcher);
		aio::Protocol::AddStub(&fire_pb_battle_SReqRePlay);
		aio::Protocol::AddStub(&fire_pb_battle_SSendAddFighters);
		aio::Protocol::AddStub(&fire_pb_battle_SSendBattleEnd);
		aio::Protocol::AddStub(&fire_pb_battle_SSendBattleStart);
		aio::Protocol::AddStub(&fire_pb_battle_SSendCameraUrl);
		aio::Protocol::AddStub(&fire_pb_battle_SSendRoundScript);
		aio::Protocol::AddStub(&fire_pb_battle_SSendRoundStart);
		aio::Protocol::AddStub(&fire_pb_battle_newhand_CReqNewHandBattle);
		aio::Protocol::AddStub(&fire_pb_circletask_CReqGotoPatrol);
		aio::Protocol::AddStub(&fire_pb_hook_CSetAutoBattle);
		aio::Protocol::AddStub(&fire_pb_mission_CMissionReachScene);
		aio::Protocol::AddStub(&fire_pb_mission_CReqGoto);
		aio::Protocol::AddStub(&fire_pb_move_CCheckMove);
		aio::Protocol::AddStub(&fire_pb_move_CRelocateRolePos);
		aio::Protocol::AddStub(&fire_pb_move_CRoleMove);
		aio::Protocol::AddStub(&fire_pb_move_CRoleStop);
		aio::Protocol::AddStub(&fire_pb_move_CRoleTurn);
		aio::Protocol::AddStub(&fire_pb_move_CSendAutoMovePathID);
		aio::Protocol::AddStub(&fire_pb_npc_CVisitNpc);
		aio::Protocol::AddStub(&fire_pb_skill_CUseSceneSkill);
	}
	else
	{
		aio::Protocol::DelStub(&fire_pb_BeanImport);
		aio::Protocol::DelStub(&fire_pb_CAfterEnterWorld);
		aio::Protocol::DelStub(&fire_pb_CEndPlayCG);
		aio::Protocol::DelStub(&fire_pb_CEnterWorld);
		aio::Protocol::DelStub(&fire_pb_CNotifyDeviceInfo);
		aio::Protocol::DelStub(&fire_pb_CPingStat);
		aio::Protocol::DelStub(&fire_pb_CRoleList);
		aio::Protocol::DelStub(&fire_pb_LuaBeanImport);
		aio::Protocol::DelStub(&fire_pb_battle_CEndWatchBattle);
		aio::Protocol::DelStub(&fire_pb_battle_CReqRePlay);
		aio::Protocol::DelStub(&fire_pb_battle_CSendAction);
		aio::Protocol::DelStub(&fire_pb_battle_CSendRoundPlayEnd);
		aio::Protocol::DelStub(&fire_pb_battle_CStopRePlay);
		aio::Protocol::DelStub(&fire_pb_battle_SRemoveWatcher);
		aio::Protocol::DelStub(&fire_pb_battle_SReqRePlay);
		aio::Protocol::DelStub(&fire_pb_battle_SSendAddFighters);
		aio::Protocol::DelStub(&fire_pb_battle_SSendBattleEnd);
		aio::Protocol::DelStub(&fire_pb_battle_SSendBattleStart);
		aio::Protocol::DelStub(&fire_pb_battle_SSendCameraUrl);
		aio::Protocol::DelStub(&fire_pb_battle_SSendRoundScript);
		aio::Protocol::DelStub(&fire_pb_battle_SSendRoundStart);
		aio::Protocol::DelStub(&fire_pb_battle_newhand_CReqNewHandBattle);
		aio::Protocol::DelStub(&fire_pb_circletask_CReqGotoPatrol);
		aio::Protocol::DelStub(&fire_pb_hook_CSetAutoBattle);
		aio::Protocol::DelStub(&fire_pb_mission_CMissionReachScene);
		aio::Protocol::DelStub(&fire_pb_mission_CReqGoto);
		aio::Protocol::DelStub(&fire_pb_move_CCheckMove);
		aio::Protocol::DelStub(&fire_pb_move_CRelocateRolePos);
		aio::Protocol::DelStub(&fire_pb_move_CRoleMove);
		aio::Protocol::DelStub(&fire_pb_move_CRoleStop);
		aio::Protocol::DelStub(&fire_pb_move_CRoleTurn);
		aio::Protocol::DelStub(&fire_pb_move_CSendAutoMovePathID);
		aio::Protocol::DelStub(&fire_pb_npc_CVisitNpc);
		aio::Protocol::DelStub(&fire_pb_skill_CUseSceneSkill);
	}
}



void RegisterProtocols()
{
_protocolsStubs(true);
}

void UnregisterProtocols()
{
_protocolsStubs(false);
}
} 
