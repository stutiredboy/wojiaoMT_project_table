
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class BattleAimRelation : public FireNet::Marshal
{
public:
	enum {
		SELF = 1, // ս�����Լ����������ˡ��衢�֡�NPC��
		SELF_PET = 2, // �Լ��ĳ���
		FRIEND_ROLE = 4, // �ѷ���ɫ
		FRIEND_PET = 8, // �ѷ��ĳ���
		FRIEND_NPC = 16, // �ѷ�NPC
		ENERMY_ROLE = 32, // ���˽�ɫ
		ENERMY_PET = 64, // ���˳���
		ENERMY_NPC = 128, // ����NPC
		ENERMY_MONSTER = 256, // ���˹���
		COUPLE = 512, // ����
		BROTHERS = 1024, // �ύ
		MASTER_STUDENT = 2048, // ʦͽ
		FRIEND_MONSTER = 4096, // �ѷ�����
	};

	BattleAimRelation() {
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

	bool operator<(const BattleAimRelation &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const BattleAimRelation &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
