
#pragma once


namespace fire { 
namespace pb { 
namespace hook { 

class HookGetDpointResEnum : public FireNet::Marshal
{
public:
	enum {
		GETDPOINTSUCC = 0, // ��ȡ�ɹ�
		GETDPOINTLIMIT = 1, // ������ȡ���ޣ�ʧ��
		GETDPOINTFAIL = 2, // ����ʧ��ԭ��
	};

	HookGetDpointResEnum() {
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

	bool operator<(const HookGetDpointResEnum &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const HookGetDpointResEnum &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
