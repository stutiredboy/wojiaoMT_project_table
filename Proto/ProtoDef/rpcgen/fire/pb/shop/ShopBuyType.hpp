
#pragma once


namespace fire { 
namespace pb { 
namespace shop { 

class ShopBuyType : public FireNet::Marshal
{
public:
	enum {
		NORMAL_SHOP = 1, // ��ͨ�̵�
		PET_SHOP = 2, // �����̵�
		MALL_SHOP = 3, // �̳�
		CHAMBER_OF_COMMERCE_SHOP_BUY = 4, // �̻���
		CHAMBER_OF_COMMERCE_SHOP_SALE = 5, // �̻���
		EXCHANGE_BUY = 6, // �һ��̵�
		SHENSHOU_SHOP = 7, // �����̵�
	};

	ShopBuyType() {
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

	bool operator<(const ShopBuyType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ShopBuyType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
