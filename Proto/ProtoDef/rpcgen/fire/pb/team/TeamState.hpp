
#pragma once


namespace fire { 
namespace pb { 
namespace team { 

class TeamState : public FireNet::Marshal
{
public:
	enum {
		eNormalTeam = 1, // ����״̬
		eWaitingSummonTeam = 2, // �ȴ��еĶ���״̬
		eSummonTeam = 3, // �ټ������״̬
	};

	TeamState() {
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

	bool operator<(const TeamState &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const TeamState &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
