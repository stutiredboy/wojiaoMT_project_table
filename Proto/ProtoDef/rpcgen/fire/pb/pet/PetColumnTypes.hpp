
#pragma once


namespace fire { 
namespace pb { 
namespace pet { 

class PetColumnTypes : public FireNet::Marshal
{
public:
	enum {
		PET = 1, // �������ϵĳ�����
		DEPOT = 2, // ����Ĳֿ������
		XUNBAOSELLPET = 3, // �ұ������۳�����
		XUNBAOBUYPET = 4, // �ұ������������
		MARKETPET = 5, // ����������
		BLACKMARKETPET = 6, // ���г�����
	};

	PetColumnTypes() {
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

	bool operator<(const PetColumnTypes &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const PetColumnTypes &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
