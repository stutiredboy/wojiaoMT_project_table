
#pragma once


namespace fire { 
namespace pb { 

class Item : public FireNet::Marshal
{
public:
	enum {
		BIND = 0x00000001, // ���ɽ��׸���ң���������
		FUSHI = 0x0000002, // �÷�ʯ�������
		ONSTALL = 0x0000004, // ��̯������
		ONCOFCSELL = 0x0000008, // ���̻����ϼ�
		CANNOTONSTALL = 0x10, // ��������
		LOCK = 0x0000020, // ����
		TIMEOUT = 0x0000040, // ʱЧ��Ʒ
	};

	int id; // ���
	int flags; // ��־�����ӵ�ʱ��flags Ҳ OR ���ӡ�
	int key; // �������ԣ�key
	int position; // �������ԣ�λ��
	int number; // �������ԣ�����
	int64_t timeout; // ����ʱ�䡣���Ϊ0������û��ʱ������
	int isnew; // 1Ϊ����Ʒ,0Ϊ����Ʒ
	int64_t loseeffecttime; // ʧЧʱ��
	int64_t markettime; // ��̯���߶���ʱ��

	Item() {
		id = 0;
		flags = 0;
		key = 0;
		position = 0;
		number = 0;
		timeout = 0;
		isnew = 0;
		loseeffecttime = 0;
		markettime = 0;
	}

	Item(int _id_, int _flags_, int _key_, int _position_, int _number_, int64_t _timeout_, int _isnew_, int64_t _loseeffecttime_, int64_t _markettime_)
		: id(_id_), flags(_flags_), key(_key_), position(_position_), number(_number_), timeout(_timeout_), isnew(_isnew_), loseeffecttime(_loseeffecttime_), markettime(_markettime_) {
	}

	bool _validator_() const {
		if (id < 1) return false;
		if (key < 1) return false;
		if (position < 0) return false;
		if (number < 1) return false;
		if (isnew < 0 || isnew > 1) return false;
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << id;
		_os_ << flags;
		_os_ << key;
		_os_ << position;
		_os_ << number;
		_os_ << timeout;
		_os_ << isnew;
		_os_ << loseeffecttime;
		_os_ << markettime;
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> id;
		_os_ >> flags;
		_os_ >> key;
		_os_ >> position;
		_os_ >> number;
		_os_ >> timeout;
		_os_ >> isnew;
		_os_ >> loseeffecttime;
		_os_ >> markettime;
		return _os_;
	}

	bool operator<(const Item &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const Item &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		_c_ = id - _o_.id;
		if (0 != _c_) return _c_;
		_c_ = flags - _o_.flags;
		if (0 != _c_) return _c_;
		_c_ = key - _o_.key;
		if (0 != _c_) return _c_;
		_c_ = position - _o_.position;
		if (0 != _c_) return _c_;
		_c_ = number - _o_.number;
		if (0 != _c_) return _c_;
		_c_ = FireNet::signum(timeout - _o_.timeout);
		if (0 != _c_) return _c_;
		_c_ = isnew - _o_.isnew;
		if (0 != _c_) return _c_;
		_c_ = FireNet::signum(loseeffecttime - _o_.loseeffecttime);
		if (0 != _c_) return _c_;
		_c_ = FireNet::signum(markettime - _o_.markettime);
		if (0 != _c_) return _c_;
		return _c_;
	}

};

} 
} 
