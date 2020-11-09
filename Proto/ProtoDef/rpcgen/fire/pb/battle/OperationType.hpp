
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class OperationType : public FireNet::Marshal
{
public:
	enum {
		ACTION_ATTACK = 1, // ����
		ACTION_SKILL = 2, // ʹ�ü���
		ACTION_USEITEM = 3, // ʹ����Ʒ
		ACTION_DEFEND = 4, // ����
		ACTION_PROTECT = 5, // ����
		ACTION_SUMMON = 6, // �ٻ�����
		ACTION_WITHDRAW = 7, // �ٻ�����
		ACTION_CATHCH = 8, // ��׽
		ACTION_ESCAPE = 9, // ����
		ACTION_REST = 10, // ��Ϣ
		ACTION_SPECIAL_SKILL = 11, // ���⼼��
		ACTION_SUMMON_INSTANT = 12, // ˲ʱ�ٻ�
		ACTION_ESCAPE_INSTANT = 13, // ˲ʱ����
		ACTION_FAILURE = 14, // ����ʧ��
		ACTION_BATTLE_END = 15, // ս������,ֻ��AI�ֵ�AIָ�������Action
		ACTION_ENVIRONMENTDEMO = 16, // ����ʩ���ߵ�Demo��attackID��0
		ACTION_ENVIRONMENTCHANGE = 17, // ս�������ı� operateid��ս������id
		ACTION_ROUNDENDDEMO = 18, // �غ�ĩ����demo
		ACTION_UNIQUE_SKILL = 19, // ����
		ACTION_FAILURE_NO_WONDER = 20, // ����ʧ��_����̾�ŵģ�
	};

	OperationType() {
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

	bool operator<(const OperationType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const OperationType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
