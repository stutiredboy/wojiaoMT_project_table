
#pragma once


namespace fire { 
namespace pb { 

class DataInit : public FireNet::Marshal
{
public:
	enum {
		ROLE_LEVEL_MAX = 155, // ��ɫ���ȼ�
		ROLE_UP_POINT = 5, // ��ɫ�������Ǳ����
		PET_UP_POINT = 5, // �����������Ǳ����
		ROLE_UP_PHY = 5, // ÿ��һ������5������
		ROLE_UP_ENERGY = 5, // ÿ��һ������5�����
		PET_INIT_LOY = 80, // �����ʼ�ҳ϶�
		PET_MAX_LOY = 100, // ��������ҳ϶ȡ�
		PET_MAX_LIFE = 20000, // �����������
		PET_FIGHT_LIFE_LIMIT = 50, // �����ս�������������
		FULL_PETLOY_LEVEL = 30, // �������ҳ϶ȵĳ���ȼ�����
		ROLE_PET_LEVEL_SPACE = 6, // �������ĵȼ������Ϊ6����
		ROLE_PET_LEVEL_SPACE_OFEXPITEM = 10, // ʹ�þ������ʱ,�������ĵȼ������Ϊ10��
		BASENUM = 1000, // ��ɫ���Լ�������ֵ�Ļ���
		PET_LEVEL_MAX = 160, // �������ȼ�
		PET_USELEVEL_SPACE = 10, // �����սʱ���˵����ȼ���
		AUTO_UPGRADE_LEVEL = 20, // �����Զ������ĵȼ�����
		WILD_PET_MAXGENGU = 40,
		WILD_PET_MINGENGU = 1,
		PET_UP_LEVEL_ADD_POINT = 5, // ����ÿ��һ��������Ǳ�ܵ���
		HAIR_COLOR_SCHEMES_NUM = 4, // ͷ����ɫ��������
		BODY_COLOR_SCHEMES_NUM = 4, // �·���ɫ��������
		TURNON_REFINE_NEED_ONLINE_TIME = 200, // ����װ��������Ҫ���ۻ�ʱ����
		TURNON_REFINE_NEED_FRIEND_LEVEL = 1000, // ����װ��������Ҫ���Ѻö�
		TURNON_REFINE_NEED_ANTIQUE_NUM = 1, // ����װ��������Ҫ�ĹŶ���
		COMMEN_ROLE_ADDPOINT = 100, // ��������ֶ��ӵ�ĵȼ���Ӧ���õ�ID
		EQUIP_CAN_REPAIR = 157, // װ���;ö�Ϊ80%ʱ�ſ�������
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