
#pragma once


namespace fire { 
namespace pb { 

class DataInit : public FireNet::Marshal
{
public:
	enum {
		ROLE_LEVEL_MAX = 155, // 角色最大等级
		ROLE_UP_POINT = 5, // 角色升级获得潜能数
		PET_UP_POINT = 5, // 宠物升级获得潜能数
		ROLE_UP_PHY = 5, // 每升一级增加5点体力
		ROLE_UP_ENERGY = 5, // 每升一级增加5点活力
		PET_INIT_LOY = 80, // 宠物初始忠诚度
		PET_MAX_LOY = 100, // 宠物最大忠诚度。
		PET_MAX_LIFE = 20000, // 宠物最大寿命
		PET_FIGHT_LIFE_LIMIT = 50, // 宠物参战的最低寿命限制
		FULL_PETLOY_LEVEL = 30, // 满宠物忠诚度的宠物等级上限
		ROLE_PET_LEVEL_SPACE = 6, // 人物宠物的等级差最大为6级。
		ROLE_PET_LEVEL_SPACE_OFEXPITEM = 10, // 使用经验道具时,人物宠物的等级差最大为10级
		BASENUM = 1000, // 角色属性计算配置值的基数
		PET_LEVEL_MAX = 160, // 宠物最大等级
		PET_USELEVEL_SPACE = 10, // 宠物参战时与人的最大等级差
		AUTO_UPGRADE_LEVEL = 20, // 人物自动升级的等级上限
		WILD_PET_MAXGENGU = 40,
		WILD_PET_MINGENGU = 1,
		PET_UP_LEVEL_ADD_POINT = 5, // 宠物每升一级，给的潜能点数
		HAIR_COLOR_SCHEMES_NUM = 4, // 头发配色方案数量
		BODY_COLOR_SCHEMES_NUM = 4, // 衣服配色方案数量
		TURNON_REFINE_NEED_ONLINE_TIME = 200, // 开启装备重铸需要的累积时间数
		TURNON_REFINE_NEED_FRIEND_LEVEL = 1000, // 开启装备重铸需要的友好度
		TURNON_REFINE_NEED_ANTIQUE_NUM = 1, // 开启装备重铸需要的古董数
		COMMEN_ROLE_ADDPOINT = 100, // 人物可以手动加点的等级对应配置的ID
		EQUIP_CAN_REPAIR = 157, // 装备耐久度为80%时才可以修理
	};

	DataInit() {
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

	bool operator<(const DataInit &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const DataInit &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
