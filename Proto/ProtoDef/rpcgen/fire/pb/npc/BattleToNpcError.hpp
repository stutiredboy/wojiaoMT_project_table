
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class BattleToNpcError : public FireNet::Marshal
{
public:
	enum {
		NoTeam = -1, // δ���
		LeaderLevelIsNotEnough = -2, // �ӳ����𲻹�
		TeamMemberIsNotEnough = -3, // ��Ա��������
		NpcOnBattle = -4, // npc����ս��
	};

	BattleToNpcError() {
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

	bool operator<(const BattleToNpcError &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const BattleToNpcError &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
