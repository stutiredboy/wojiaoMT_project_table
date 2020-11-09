
#pragma once


namespace fire { 
namespace pb { 
namespace attr { 

class FightAttrType : public FireNet::Marshal
{
public:
	enum {
		CONS = 10, // ����
		IQ = 20, // ����
		STR = 30, // ����
		ENDU = 40, // ����
		AGI = 50, // ����
		MAX_HP = 60, // �������
		MAX_MP = 90, // �����
		MAX_SP = 110, // ���ŭ��
		ATTACK = 130, // ����
		DEFEND = 140, // ����
		MAGIC_ATTACK = 150, // ����������
		MAGIC_DEF = 160, // ����������
		MEDICAL = 170, // ����ǿ��
		SEAL = 180, // ��������
		UNSEAL = 190, // ��ϵ�ֿ���
		SPEED = 200, // �ٶ�
		HIT_RATE = 210, // ����ֵ
		DODGE_RATE = 220, // ���ֵ
		PHY_CRITC_LEVEL = 230, // �������ȼ�
		ANTI_PHY_CRITC_LEVEL = 240, // ���������ȼ�
		PHYSIC_CRIT_PCT = 250, // �������̶ȣ���ʼΪ200%,��2����ͨ�˺���
		MAGIC_CRITC_LEVEL = 260, // ħ�������ȼ�
		ANTI_MAGIC_CRITC_LEVEL = 270, // ��ħ�������ȼ�
		MAGIC_CRIT_PCT = 280, // ħ�������̶ȣ���ʼΪ200%��
		HEAL_RATE = 290, // ���Ʊ�����
		HEAL_DEGREE = 300, // ���Ʊ����̶�
		IGNORE_PHYSIC_DEFEND_RATE = 310, // ���������������
		IGNORE_PHYSIC_DEFEND_PCT = 320, // �����������ϵ��
		IGNORE_MAGIC_DEFEND_RATE = 330, // ���ӷ�����������
		IGNORE_MAGIC_DEFEND_PCT = 340, // ���ӷ�������ϵ��
		STEAL_HP_RATE = 350, // ��Ѫ����
		STEAL_HP_PCT = 360, // ��Ѫϵ������Ѫռ����˺��İٷֱȣ�Ĭ��0%)
		FIRE_MP_RATE = 370, // ��������
		FIRE_MP_PCT = 380, // ����ϵ��
		POISON_RATE = 390, // ��ͨ����ʹ�Է��ж����ʣ�Ĭ��0%)
		PIOSON_DAMGE_HP = 400, // ����Ѫϵ��
		PIOSON_DAMGE_MP = 410, // ������ϵ��
		PIOSON_DAMGE_ROUND = 420, // ���غ���
		DIE_FORBID_RATE = 430, // ������������
		DIE_FORBID_ROUND = 440, // ���������غ���
		PHYSIC_COMBO_ATTACK_RATE = 450, // ������������
		PHYSIC_COMBO_ATTACK_PCT = 460, // ���������˺�ϵ��
		PHYSIC_COMBO_ATTACK_COUNT = 470, // ���������������ޣ�ԭ���������ĳ������������ޣ�
		MAGIC_COMBO_ATTACK_RATE = 480, // ������������
		MAGIC_COMBO_ATTACK_PCT = 490, // ���������˺�ϵ��
		MAGIC_COMBO_ATTACK_COUNT = 500, // ����������������
		EXTRA_ATTACK_RATE = 510, // ׷����
		EXTRA_ATTACK_PCT = 520, // ׷���˺�ϵ��
		EXTRA_ATTACK_COUNT = 530, // ׷������
		DIFFUSE_ATTACK_RATE = 540, // ���伸��
		DIFFUSE_ATTACK_PCT = 550, // �����˺�ϵ��
		DIFFUSE_ATTACK_COUNT = 560, // ��������
		PARRY_RATE = 570, // �мܼ��ʣ�Ĭ��0%)
		PARRY_PCT = 580, // �񵲼���ϵ��
		RETURN_HURT_RATE = 590, // ������
		RETURN_HURT_PCT = 600, // ����̶ȣ������˺�ռ����˺��İٷֱȣ�Ĭ��30%)
		ATTACK_BACK_RATE = 610, // ������
		ATTACK_BACK_PCT = 620, // �����̶ȣ����������˺��İٷֱȣ�Ĭ��100%��
		GOD_BLESS_RATE = 630, // ���Ӽ��ʣ�ԭ��������ø�Ϊ���Ӽ��ʣ�
		GOD_BLESS_PCT = 640, // ���Ӹ���Ѫ��ϵ��
		ABSORB_FIRE_ODDS = 650, // ��ϵ����������
		ABSORB_WATER_ODDS = 660, // ˮϵ����������
		ABSORB_EARTH_ODDS = 670, // ��ϵ����������
		ABSORB_THUNDER_ODDS = 680, // ��ϵ����������
		ABSORB_OTHER_ODDS = 690, // Ԥ��ϵ����������
		ABSORB_FIRE_PCT = 700, // ��ϵ��������ϵ��
		ABSORB_WATER_PCT = 710, // ˮϵ��������ϵ��
		ABSORB_EARTH_PCT = 720, // ��ϵ��������ϵ��
		ABSORB_THUNDER_PCT = 730, // ��ϵ��������ϵ��
		ABSORB_OTHER_PCT = 740, // Ԥ��ϵ��������ϵ��
		PHYSIC_DAMGE_RATE = 750, // �����˺�Ч������
		ANTI_PHYSIC_DAMGE_RATE = 760, // �������˺�Ч������
		MAGIC_DAMGE_RATE = 770, // �����˺�Ч������
		ANTI_MAGIC_DAMGE_RATE = 780, // �ܷ����˺�Ч������
		HEAL_EFFECT_RATE = 790, // ����Ч������
		ANTI_HEAL_EFFECT_RATE = 800, // ������Ч������
		SEAL_LEVEL = 810, // ��ӡ���еȼ�
		ANTI_SEAL_LEVEL = 820, // ��ӡ���Եȼ�
		PHYSIC_CRIT_RATE = 830, // ��������������
		ANTI_PHYSIC_CRIT_RATE = 840, // ����������������
		MAGIC_CRIT_RATE = 850, // ����������������
		ANTI_MAGIC_CRIT_RATE = 860, // ������������������
		HEAL_CRIT_LEVEL = 870, // ���Ʊ�����������
		ANTI_HEAL_CRIT_LEVEL = 880, // �����Ʊ�����������
		ANTI_POISON_RATE = 890, // �����ͱ�����ʱ�ж���������
		ANTI_DIE_FORBID_RATE = 900, // ������������������
		ANTI_PARRY_RATE = 910, // ����ʱ���񵲼�������
		ANTI_RETURN_HURT_RATE = 920, // ����ʱ������������
		ANTI_ATTACK_BACK_RATE = 930, // ����ʱ����������������ԭ����������
		ANTI_GOD_BLESS_RATE = 940, // ����ʱ�����Ӽ�������
		PHYSIC_DAMGE_PIERCE_RATE = 950, // ����͸
		ANTI_PHYSIC_DAMGE_PIERCE_RATE = 960, // ����ֿ�
		MAGIC_DAMGE_PIERCE_RATE = 970, // ������͸
		ANTI_MAGIC_DAMGE_PIERCE_RATE = 980, // �����ֿ�
		HEAL_DEEP_RATE = 990, // ���Ƽ���
		ANTI_HEAL_DEEP_RATE = 1000, // �����Ƽ���
		EFFECT_POINT = 1010, // ����Ч����
		TEMP_SP = 1020, // ��ʱŭ��
		ENLIMIT = 1520, // ��������
		PFLIMIT = 1530, // ��������
		AMEND_HIDDEN_WEAPON_PASSIVE = 1540, // ���ڱ����˺�����
		ATTACK_BACK_LEVEL = 1750, // �����ȼ�
		RETURN_HURT_LEVEL = 1760, // ������ȼ�
		ANTI_ATTACK_BACK_LEVEL = 1770, // �������ȼ�
		ANTI_RETURN_HURT_LEVEL = 1780, // ��������ȼ�
		MAGIC_HIT = 1840, // ��������ֵ
		HEALEDREVISE = 800, // �ؼ�����
		ANTI_CRITC_LEVEL = 2090, // �����ȼ�
		KONGZHI_JIACHENG = 2130, // ���Ƽӳ�
		KONGZHI_MIANYI = 2140, // ��������
		PHYSIC_FLOAT_VALUE = 2150, // ������
		MAGIC_FLOAT_VALUE = 2160, // ��������
		HEAL_FLOAT_VALUE = 2170, // ���Ʋ���
		DEEP_HEAL_CRITC_LEVEL = 2180, // �����Ʊ���
		SHAPE_ID = 3000, // ģ��id
	};

	FightAttrType() {
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

	bool operator<(const FightAttrType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const FightAttrType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
