
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class NpcServices : public FireNet::Marshal
{
public:
	enum {
		FORTUNE_WHEEL = 14, // 幸运大转盘
		SEND_MAIL = 69, // 送信: (动态服务)
		CHECK_CHIEF_ABILITY = 96, // 查看首席-弟子能力
		CHALLENGE_CHIEF = 97, // 挑战首席-弟子
		RUN_FOR_CHIEF = 98, // 我要竞选
		VOTING = 99, // 我要投票
		REFRESH_CHIEF_ABILITY = 100, // 我要刷新首席-弟子能力
		ATTEND_IMPEXAM = 136, // 我要参加智慧试炼
		LEARN_IMPEXAM_RULE = 137, // 我想了解智慧试炼比赛规则
		WINNER_START = 166, // 准备好了,请告诉我们第一关的挑战地点
		CHECK_PERSONAL_CREDIT = 167, // 我想查询下自己的活动积分
		ADD_PET_LIFE = 168, // 我想增加宠物寿命
		FIGHT_WINNER = 171, // 挑战冠军试炼对手
		ENTER_BINGFENG = 355, // 进入冰封王座
		BACK_COPY_SERVICE = 1469, // 回到副本副本
		CIRCTASK_SCHOOL1 = 3000, // 新循环任务-职业
		CIRCTASK_SCHOOL2 = 3001, // 新循环任务-职业
		CIRCTASK_SCHOOL3 = 3002, // 新循环任务-职业
		CIRCTASK_SCHOOL4 = 3003, // 新循环任务-职业
		CIRCTASK_SCHOOL5 = 3004, // 新循环任务-职业
		CIRCTASK_SCHOOL6 = 3005, // 新循环任务-职业
		CIRCTASK_SCHOOL_SUBMIT1 = 3010, // 新循环任务提交-职业
		CIRCTASK_SCHOOL_SUBMIT2 = 3011, // 新循环任务提交-职业
		CIRCTASK_SCHOOL_SUBMIT3 = 3012, // 新循环任务提交-职业
		CIRCTASK_SCHOOL_SUBMIT4 = 3013, // 新循环任务提交-职业
		CIRCTASK_SCHOOL_SUBMIT5 = 3014, // 新循环任务提交-职业
		CIRCTASK_SCHOOL_SUBMIT6 = 3015, // 新循环任务提交-职业
		CATCH_IT = 4000, // 循环任务-捉鬼
		CATCH_IT_SUBMIT = 4001, // 循环任务-捉鬼
		CATCH_IT_QUERY = 4002, // 循环任务-查询捉鬼
		CATCH_IT_BJ = 4003, // 循环任务-便捷捉鬼
		CATCH_IT_Battle = 4004, // 循环任务-捉鬼进入战斗
		TIMER_NPC_Battle = 4005, // 定时刷怪进入战斗
		EVENT_NPC_Battle = 4006, // 事件刷怪进入战斗
		SUBMIT_CIRCTASK = 5000, // 提交循环任务
		RENXING_CIRCTASK = 5001, // 任性一下循环任务
		BUY_MEDICINE = 30000, // 购买药品
		BUY_GOODS = 30001, // 购买物品
		BUY_EQUIP = 30002, // 购买装备
		BUY_PET = 30003, // 购买宠物
		OPEN_SHANGHUI = 30004, // 打开商会
		QUERY_LINEINST = 100049, // 查询精英副本次数
		RESET_LINEINST = 100187, // 重置副本
		ONE_LIEVEL_TITLE = 900054, // 一级称谓 by changhao
		TWO_LIEVEL_TITLE = 900055, // 二级称谓 by changhao
		THREE_LIEVEL_TITLE = 900056, // 三级称谓 by changhao
		LEADER_SEE_CAMPAIGN_LIST = 900057, // 查看竞选名单 by changhao
		LEADER_MY_CAMPAIGN = 900058, // 我的竞选 by changhao
		LEADER_CHALLENGE = 900059, // 挑战领袖 by changhao
		LEADER_CAMPAIGN = 900060, // 竞选领袖 by changhao
		PET_STORE = 100012, // 宠物仓库
		EXCHANGE_CODE = 100600, // 兑换码
		IMPEXAM_STATE = 100704, // 智慧试炼
		LOOK_YAO_QIAN = 200101, // 照顾摇钱树
		ENTER_1V1_PVP = 910000, // 送我去竞技场
		LEAVE_1V1_PVP = 910004, // 离开竞技场
		ENTER_3V3_PVP = 910010, // 送我去3v3竞技场
		LEAVE_3V3_PVP = 910014, // 离开3v3竞技场
		ENTER_5V5_PVP = 910020, // 送我去5v5竞技场
		LEAVE_5V5_PVP = 910024, // 离开5v5竞技场
		WATCH_NPC_BATTLE = 910115, // 定时表明雷怪观战
		WATCH_EVENTNPC_BATTLE = 910116, // 事件表明雷怪观战
		WATCH_INST_NPC_BATTLE = 910201, // 公会副本观战按钮服务
		END_INST_NPC_BATTLE = 910202, // 公会副本终止战斗服务
		ENTER_CLAN_FIGHT = 910030, // 进入公会战 by changhao
	};

	NpcServices() {
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

	bool operator<(const NpcServices &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const NpcServices &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
