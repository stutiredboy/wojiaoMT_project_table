
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class MultiExpError : public FireNet::Marshal
{
public:
	enum {
		LevelConditionErr = -2, // �ȼ�����
		ExistOtherMultiExpBuff = -3, // ���������౶�����buff��������ȡ��ġ�
		NoOneMultiExpBuff = -4, // �����ڶ౶�����buff�������˻�
		NoHaveBuffTime = -5, // û�п�����ȡ��ʱ�䣬������ȡ
		OverMaxHours = -6, // ���϶౶ʱ���buff����4Сʱ
	};

	MultiExpError() {
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

	bool operator<(const MultiExpError &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const MultiExpError &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
