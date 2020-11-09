
#pragma once


namespace fire { 
namespace pb { 
namespace hook { 

class HookMsg2ClientEnum : public FireNet::Marshal
{
public:
	enum {
		GETDPOINTSUCC = 150151, // ��ȡ�ɹ�
		GETDPOINTLIMIT = 150152, // ��ȡ����
		FREEDPOINTSUCC = 150153, // ����ɹ�
		OFFLINEEXP = 150156, // ���߾���
	};

	HookMsg2ClientEnum() {
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

	bool operator<(const HookMsg2ClientEnum &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const HookMsg2ClientEnum &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
