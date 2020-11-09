
#pragma once


namespace fire { 
namespace pb { 
namespace attr { 

class ScoreType : public FireNet::Marshal
{
public:
	enum {
		ROLE_LEVEL_SCORE = 1, // ��ɫ�ȼ�����
		EQUIP_LEVEL_SCORE = 2, // װ��һ������
		EQUIP_EFFCT = 3, // װ����Ч
		EQUIP_SKILL = 4, // װ���ؼ�
		EQUIP_GEM = 5, // ÿ����ʯ
		SCHOOL_SKILL = 6, // ְҵ����
		GUILD_SKILL = 7, // ���Ἴ��
		GUILD_SHAVE = 8, // ��������
		PET_LEVEL_SCORE = 9, // ����һ������
		PET_LOW_SKILL = 10, // ����ͼ�����
		PET_HIGH_SKILL = 11, // ����߼�����
		PET_GROWING = 12, // ����ɳ�
	};

	ScoreType() {
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

	bool operator<(const ScoreType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ScoreType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
