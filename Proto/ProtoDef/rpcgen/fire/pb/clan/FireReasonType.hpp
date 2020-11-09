
#pragma once


namespace fire { 
namespace pb { 
namespace clan { 

class FireReasonType : public FireNet::Marshal
{
public:
	enum {
		CLEAN_MEMBER = 1, // ��Ա����
		LONG_TIME_OFF_LINE = 2, // ���ڲ�����
		NO_ACTIVE = 3, // ���ֲ�����
		NO_INTEREST = 4, // ־Ȥ����
	};

	FireReasonType() {
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

	bool operator<(const FireReasonType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const FireReasonType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
