
#pragma once


namespace fire { 
namespace pb { 
namespace item { 

class BagTypes : public FireNet::Marshal
{
public:
	enum {
		EMPTY = 0,
		BAG = 1, // ����
		DEPOT = 2, // �ֿ�
		EQUIP = 3, // װ������
		TEMP = 4, // ��ʱ����
		QUEST = 5, // ���񱳰�
		MARKET = 6, // ��������
		BLACKMARKET = 7, // ���б���
	};

	BagTypes() {
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

	bool operator<(const BagTypes &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const BagTypes &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
