
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class BattleType : public FireNet::Marshal
{
public:
	enum {
		BATTLE_PVE = 10, // ��� ,����pve %10����0
		BATTLE_HIDEAREA = 1100, // ������ս��
		BATTLE_SHOWAREA = 1200, // ������ս��
		BATTLE_BOSS = 30, // pve�е�bossս,��ս����ʱ����Ҫ��һ����ʾ(141614)
		BATTLE_LINE = 40, // ����ս��
		BATTLE_CLANBOSS = 50, // ����boss
		BATTLE_SHOUXI = 60, // capital apprentice
		BATTLE_PVP = 11, // �д�,����pvp %10����1
		BATTLE_LIVEDIE = 21, // ����ս
		BATTLE_DUEL_SINGLE = 31, // ���˾���
		BATTLE_DUEL_TEAM = 41, // ��Ӿ���
		BATTLE_BINGFENG_WAR = 100, // ��������ս��
		BATTLE_INST_BATTLE = 110, // ���ḱ��ս��
		BATTLE_CLAN_FIGHT = 201, // ����ս by changhao
	};

	BattleType() {
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

	bool operator<(const BattleType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const BattleType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
