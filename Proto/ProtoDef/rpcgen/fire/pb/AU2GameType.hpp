
#pragma once


namespace fire { 
namespace pb { 

class AU2GameType : public FireNet::Marshal
{
public:
	enum {
		INVITE_FRIEND = 1, // ��Ϸ�ڷ��ʼ�������ѻع�
		RECOMMEND_FRIEND = 2, // �Ƽ�����
		PRESEND_CARD = 3, // ��Ʒ��
		QUICK_PAY = 4, // ���֧��
		VIP_INFO = 5, // VIP��Ϣ��ȡ
		QUICK_PAY_REQUEST = 6, // ���֧������
	};

	AU2GameType() {
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

	bool operator<(const AU2GameType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const AU2GameType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
