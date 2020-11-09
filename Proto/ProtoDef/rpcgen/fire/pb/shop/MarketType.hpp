
#pragma once


namespace fire { 
namespace pb { 
namespace shop { 

class MarketType : public FireNet::Marshal
{
public:
	enum {
		CARE_FOR = 1, // ��ע
		RARITY_PET = 2, // ��Ʒ����(��Ʒ)
		RARITY_EQUIP = 3, // ��Ʒװ��(��Ʒ)
		RARITY_PET_BOOK = 4, // �߼��޾�(��Ʒ)
		NORMAL_PET_BOOK = 5, // �ͼ��޾�
		NORMAL_PHARMACEUTICAL = 6, // ҩƷ
		COOKING = 7, // ���
		ZHI_ZAO_FU = 8, // �����
		LIN_SHI_FU = 9, // ��ʱ��
		TASK_ITEM = 10, // �������
		PET_SHOP = 11, // �����챦
		RARITY_EQUIP_FORGING = 12, // װ������(��Ʒ)
	};

	MarketType() {
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

	bool operator<(const MarketType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const MarketType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
