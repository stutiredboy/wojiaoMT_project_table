
#pragma once


namespace fire { 
namespace pb { 

class ErrorCodes : public FireNet::Marshal
{
public:
	enum {
		NoError = 0, // û�д���
		AddItemToBagException = 1, // �����������Ʒ����
		NotEnoughMoney = 2, // ��Ǯ����
		EquipPosNotSuit = 3, // װ��λ�ò�����
		EquipLevelNotSuit = 4, // װ���ȼ�������
		EquipSexNotSuit = 5, // װ���Ա𲻷���
	};

	ErrorCodes() {
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

	bool operator<(const ErrorCodes &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ErrorCodes &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
