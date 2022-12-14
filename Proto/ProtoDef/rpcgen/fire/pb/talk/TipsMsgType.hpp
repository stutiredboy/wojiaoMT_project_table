
#pragma once


namespace fire { 
namespace pb { 
namespace talk { 

class TipsMsgType : public FireNet::Marshal
{
public:
	enum {
		TIPS_POPMSG = 1, // 透明框提示
		TIPS_NPCTALK = 2, // npc对话框提示
		TIPS_MSG_CHANNEL = 3, // 消息频道提示
		TIPS_SYSBOARD = 4, // 系统公告提示
		TIPS_CONFIRM = 5, // 确认框提示
		TIPS_CLAN = 7, // 公会频道提示
		TIPS_CUR_CHANNEL = 8, // 当前频道提示
		TIPS_WORLD = 9, // 世界频道提示
		TIPS_TEAM_CHANNEL = 13, // 队伍频道提示
		TIPS_PRO_CHANNEL = 14, // 职业频道提示
		TIPS_SYS_CHANNEL = 15, // 系统频道提示
		TIPS_ROLE_CHANNEL = 18, // 跑马灯提示
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
