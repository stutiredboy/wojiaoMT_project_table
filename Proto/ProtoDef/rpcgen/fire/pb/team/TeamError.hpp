
#pragma once


namespace fire { 
namespace pb { 
namespace team { 

class TeamError : public FireNet::Marshal
{
public:
	enum {
		UnkownError = 0, // δ֪����
		SelfInTeam = 1, // �Լ��Ѿ��ڶ�����
		SelfNotInTeam = 2, // �Լ����ڶ�����
		ObjectInTeam = 3, // �Է��Ѿ��ڶ�����
		SelfNOtLeader = 4, // �Լ����Ƕӳ�
		ObjectNotLeader = 5, // �Է����Ƕӳ�
		ObjectOffline = 6, // �Է������ߣ���ͳһ��Error��
		SelfTeamFunctionClose = 7, // �Լ���ӿ��عر�
		ObjectTeamFunctionClose = 8, // �Է���ӿ��عر�
		SelfInUnteamState = 9, // �Լ��ڲ������״̬
		ObjectInUnteamState = 10, // �Է��ڲ������״̬
		TeamFull = 11, // ������������
		InvitedInTeam = 12, // �Է��Ѿ��ڶ�����
		BeingInvited = 13, // �Է����ڱ�������������
		InvitedIn30s = 14, // 30����ֻ������һ��ͬһ���
		InviteingsFull = 15, // �������������ﵽ4�����������������
		InviterTeamNotExist = 16, // �������Ķ����Ѿ���ɢ
		InviterNotLeader = 17, // �����߲��Ƕӳ�
		ApplierInTeam = 18, // �������Ѿ��ڶ�����
		ApplyTimeout = 19, // �������Ѿ���ʱ
		ApplyListFull = 20, // ���������б�����
		ApplierLevelValid = 21, // �����߼��𲻷��϶���Ҫ��
		ChangeLeaderUnable = 22, // ���鴦�ڲ����Ի��ӳ���״̬
		InChangeLeaderStatus = 23, // �Ѿ���������ӳ����ȴ���Ӧ��
		ChangeLeaderInCD = 24, // ����2����ֻ�ܸ����ӳ�һ��
		MembersNotNormal = 25, // ��Ա����������״̬
		TooFar = 26, // �����Զ�����ܹ��
		NoAbsentMember = 27, // ����û������Ķ�Ա
		RefuseChangeLeader = 28, // �ܾ���Ϊ�ӳ�
		ObjectNotInTeam = 29, // �Է����ڶ�����
		AlreadyApply = 30, // �Է��Ѿ��ڴ˶���������б���
		AbsentCantBeLeader = 31, // �����Ա���ܳ�Ϊ�ӳ�
		LevelSetError = 32, // �ȼ����ô��� by changhao
		LevelError = 33, // �ȼ������� by changhao
		NoTarget = 34, // û������Ŀ�� by changhao
		TeamEnoughFull = 35, // �����Ѿ����� by changhao
		InMatching = 36, // �Ѿ���ƥ���� by changhao
		ActiveNotOpen = 37, // �δ���� by changhao
		NoFaction = 38, // û�й��� by changhao
		TeamStateError = 39, // ���״̬�ͻ��˷�������ͬ�� by changhao
		OneKeyApplyTeamNoTime = 40, // һ����������ʱ�� by changhao
		NoRollNotInTeam = 50, // ���ڶ����в���ROLL�� by changhao
		NoReward = 51, // û�н����ɷ��� by changhao
		FormBookHalfNotEnough = 55, // �⻷�о��� by changhao
		UnKnuownFormBook = 56, // ��Ч�Ĺ⻷�� by changhao
		FromLevelMax = 57, // �⻷�ȼ��Ѿ������ by changhao
		FormIdError = 58, // �⻷ID ���� by changhao
		FormBookNotEnough = 59, // �⻷�鲻�� by changhao
	};

	TeamError() {
	}

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		return _os_;
	}

	bool operator<(const TeamError &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const TeamError &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
