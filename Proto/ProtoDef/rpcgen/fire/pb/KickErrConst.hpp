
#pragma once


namespace fire { 
namespace pb { 

class KickErrConst : public FireNet::Marshal
{
public:
	enum {
		ERR_GM_KICKOUT = 2049, // ��GM������
		ERR_SERVER_SHUTDOWN = 2050, // �������ر�
		ERR_GACD_PUNISH = 2051, // ����Ҵ���û��ͨ��
		ERR_RUN_TOO_FAST = 2052, // ��·̫�챻��
		ERR_GACD_WAIGUA = 2053, // ʹ�����
		ERR_XUNBAO_SELLROLE = 2054, // �ұ������۽�ɫ
		ERR_FORBID_USER = 2055, // �˺ű��������
		ERR_GACD_KICKOUT = 2056, // gacd��-1���������
	};

	KickErrConst() {
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

	bool operator<(const KickErrConst &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const KickErrConst &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
