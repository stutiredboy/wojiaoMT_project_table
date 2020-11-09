
#pragma once


namespace fire { 
namespace pb { 
namespace school { 

class ShouXiLimit : public FireNet::Marshal
{
public:
	enum {
		CHALLENGE_LEVEL_LIMIT = 40, // ��ս��ϯ�ĵȼ�����
		SCHOOL_CONTRIBUTE_LIMIT = 500, // ��ս��ϯ��Ҫ��ְҵ���׶�
		MONEY_LIMIT = 10000, // ��ս��ϯ��Ҫ�Ľ�Ǯ
		VOTE_LEVEL_LIMIT = 30, // ͶƱ��Ҫ�ĵȼ�
		TILI_LIMIT = 100, // ͶƱ��Ҫ������ֵ
		REFRESH_TIMES_LIMIT = 5, // ͶƱ��Ҫ������ֵ
	};

	ShouXiLimit() {
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

	bool operator<(const ShouXiLimit &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ShouXiLimit &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
