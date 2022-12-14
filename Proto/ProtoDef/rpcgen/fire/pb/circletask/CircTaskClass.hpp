
#pragma once


namespace fire { 
namespace pb { 
namespace circletask { 

class CircTaskClass : public FireNet::Marshal
{
public:
	enum {
		CircTask_Mail = 1, // 送信
		CircTask_ItemUse = 2, // 道具制造
		CircTask_ItemCollect = 3, // 道具收集
		CircTask_ItemFind = 4, // 寻找道具
		CircTask_PetCatch = 5, // 捕获宠物
		CircTask_Patrol = 6, // 巡逻
		CircTask_CatchIt = 7, // 捉鬼
		CircTask_KillMonster = 8, // 杀怪计数
		CircTask_ChallengeNpc = 9, // 挑战npc
	};

	CircTaskClass() {
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

	bool operator<(const CircTaskClass &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const CircTaskClass &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
