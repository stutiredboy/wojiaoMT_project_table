
#pragma once


namespace fire { 
namespace pb { 
namespace talk { 

class TipsMsgType : public FireNet::Marshal
{
public:
	enum {
		TIPS_POPMSG = 1, // ͸������ʾ
		TIPS_NPCTALK = 2, // npc�Ի�����ʾ
		TIPS_MSG_CHANNEL = 3, // ��ϢƵ����ʾ
		TIPS_SYSBOARD = 4, // ϵͳ������ʾ
		TIPS_CONFIRM = 5, // ȷ�Ͽ���ʾ
		TIPS_CLAN = 7, // ����Ƶ����ʾ
		TIPS_CUR_CHANNEL = 8, // ��ǰƵ����ʾ
		TIPS_WORLD = 9, // ����Ƶ����ʾ
		TIPS_TEAM_CHANNEL = 13, // ����Ƶ����ʾ
		TIPS_PRO_CHANNEL = 14, // ְҵƵ����ʾ
		TIPS_SYS_CHANNEL = 15, // ϵͳƵ����ʾ
		TIPS_ROLE_CHANNEL = 18, // �������ʾ
	};

	TipsMsgType() {
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

	bool operator<(const TipsMsgType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const TipsMsgType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
