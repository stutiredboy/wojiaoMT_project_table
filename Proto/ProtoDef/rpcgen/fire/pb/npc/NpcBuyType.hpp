
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class NpcBuyType : public FireNet::Marshal
{
public:
	enum {
		COMMON_MONEY_BUY = 0,
		COMMON_SMONEY_BUY = 1,
		FAMILY_SELL = 2,
		SKILL_SELL = 3,
		BUY_AND_USE = 6, // �÷�ʯ������Ʒ�������ֱ��ʹ�ã�������������۳�һ��������ķ��뱳��
		MONEY_BUY_AND_USE = 7, // ���ֽ�����Ʒ�������ֱ��ʹ��
	};

	NpcBuyType() {
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

	bool operator<(const NpcBuyType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const NpcBuyType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
