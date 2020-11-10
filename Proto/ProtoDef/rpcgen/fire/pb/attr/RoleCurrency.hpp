
#pragma once


namespace fire { 
namespace pb { 
namespace attr { 

class RoleCurrency : public FireNet::Marshal
{
public:
	enum {
		GUILD_DKP = 1, // ����DKP
		GUILD_DED = 2, // ���ṱ��
		TEACHER_SCORE = 3, // ʦͽֵ
		ACTIVE_SCORE = 4, // �����
		HONOR_SCORE = 5, // ����ֵ
		POP_SCORE = 6, // ����ֵ
		FRIEND_SCORE = 7, // ���ѻ���
		PROF_CONTR = 9, // ְҵ����
		EREDITPOINT_SCORE = 10, // ���õ�
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