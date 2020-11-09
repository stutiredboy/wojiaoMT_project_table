
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class TransmitTypes : public FireNet::Marshal
{
public:
	enum {
		impexamsystem = 4, // �ǻ���������ϵͳ����
		winnercall = 5, // �ھ���������
		backschoolwhile20lv = 6, // 20��ʱʦ�������ְҵ
		singlepvp = 10, // ����pvp����
		pvp3 = 15, // pvp3����
		pvp5 = 16, // pvp5����
	};

	TransmitTypes() {
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

	bool operator<(const TransmitTypes &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const TransmitTypes &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
