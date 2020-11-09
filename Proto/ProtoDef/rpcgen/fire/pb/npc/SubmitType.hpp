
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class SubmitType : public FireNet::Marshal
{
public:
	enum {
		ITEM = 1, // ����npc��������ص���Ʒ
		PET = 2, // ����npc,������صĳ���
		MONEY = 3, // ����npc,������صĽ�Ǯ
		FACTION_MONEY_BOX = 4, // ����npc,��������
		FAMILY_MONEY_BOX = 5, // ����npc,����
		INSTANCE_ZONE_ITEM = 13, // �����淨�ڵ��ύ��Ʒ
		GUILD_ZONE_ITEM = 22, // �����淨�ڵ��ύ��Ʒ
	};

	SubmitType() {
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

	bool operator<(const SubmitType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const SubmitType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
