
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class BattleEnviroment : public FireNet::Marshal
{
public:
	enum {
		DAY = 1001, // ��
		NIGHT = 1002, // ҹ
		WARM = 1003, // ů
		COLD = 1004, // ��
		ORCHID = 1005, // ��
		THUNDER = 1006, // ��
	};

	BattleEnviroment() {
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

	bool operator<(const BattleEnviroment &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const BattleEnviroment &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
