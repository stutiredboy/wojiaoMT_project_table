
#pragma once


namespace fire { 
namespace pb { 
namespace attr { 

class RoleCurrency : public FireNet::Marshal
{
public:
	enum {
		GUILD_DKP = 1, // 公会DKP
		GUILD_DED = 2, // 公会贡献
		TEACHER_SCORE = 3, // 师徒值
		ACTIVE_SCORE = 4, // 活动积分
		HONOR_SCORE = 5, // 荣誉值
		POP_SCORE = 6, // 声望值
		FRIEND_SCORE = 7, // 好友积分
		PROF_CONTR = 9, // 职业贡献
		EREDITPOINT_SCORE = 10, // 信用点
	};

	RoleCurrency() {
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

	bool operator<(const RoleCurrency &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const RoleCurrency &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
