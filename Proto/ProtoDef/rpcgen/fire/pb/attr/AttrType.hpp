
#pragma once


namespace fire { 
namespace pb { 
namespace attr { 

class AttrType : public FireNet::Marshal
{
public:
	enum {
		CONS = 10, // ����
		IQ = 20, // ����
		STR = 30, // ����
		ENDU = 40, // ����
		AGI = 50, // ����
		MAX_HP = 60, // �����������
		UP_LIMITED_HP = 70, // ��ǰ�������ޣ�С�ڵ�������������ޣ�
		HP = 80, // ��ǰ����
		SPIRIT = 90, // ����
		MAX_MP = 90, // �����
		MP = 100, // ��ǰ����
		MAX_SP = 110, // ���ŭ��
		SP = 120, // ŭ��
		ATTACK = 130, // ����
		DEFEND = 140, // ����
		MAGIC_ATTACK = 150, // ����������
		MAGIC_DEF = 160, // ����������
		MEDICAL = 170, // ����ǿ��
		SEAL = 180, // ��������
		UNSEAL = 190, // ���ƿ���
		SPEED = 200, // �ٶ�
		HIT_RATE = 210, // ����ֵ
		DODGE_RATE = 220, // ���ֵ
		PHY_CRIT_PCT = 250, // �������̶ȣ���ʼΪ200%,��2����ͨ�˺���
		MAGIC_CRIT_PCT = 280, // ħ�������̶ȣ���ʼΪ200%��
		PHY_CRITC_LEVEL = 230, // �������ȼ�
		ANTI_PHY_CRITC_LEVEL = 240, // �����Եȼ�
		MAGIC_CRITC_LEVEL = 260, // ħ�������ȼ�
		ANTI_MAGIC_CRITC_LEVEL = 270, // ħ�����Եȼ�
		HEAL_CRIT_LEVEL = 290, // ���Ʊ����ȼ�
		HEAL_CRIT_PCT = 300, // ���Ʊ����̶�
		PHFORCE = 450, // ��ǰ����
		EXP = 470, // ����
		NEXP = 480, // ��������
		RENQI = 610, // ����ֵ
		SCHOOLFUND = 850, // ְҵ���׶�
		WULI_CHUANTOU = 950, // ����͸
		WULI_DIKANG = 960, // ����ֿ�
		FASHU_CHUANTOU = 970, // ������͸
		FASHU_DIKANG = 980, // �����ֿ�
		ZHILIAO_JIASHEN = 990, // ���Ƽ���
		EFFECT_POINT = 1010, // ����Ч����
		TEMP_SP = 1020, // ��ʱŭ��
		MASTER_REPUTATION = 1080, // ʦͽ����
		PET_XUEMAI_MAX = 1150, // ������������
		PET_LOW_SKILL = 1170, // ����ͼ�������
		PET_HIGH_SKILL = 1180, // ����߼�������
		PET_SUPER_SKILL = 1190, // ���ﳬ��������
		LEVEL = 1230, // �ȼ�
		PET_LIFE = 1360, // ��������
		ACTIVESTAR = 1380, // ��Ծ��������
		POINT = 1400, // Ǳ��
		QILIZHI = 1410, // ����ֵ
		QILIZHI_LIMIT = 1420, // ����ֵ����
		PET_XUE_MAI_LEVEL = 1430, // �����Ǽ�
		PET_FIGHT_LEVEL = 1430, // �����ս�ȼ�
		PET_ATTACK_APT = 1440, // ���﹥������
		PET_DEFEND_APT = 1450, // �����������
		PET_PHYFORCE_APT = 1460, // ������������
		PET_MAGIC_APT = 1470, // ���﷨������
		PET_SPEED_APT = 1480, // �����ٶ�����
		PET_DODGE_APT = 1490, // �����������
		PET_GROW_RATE = 1500, // ����ɳ���
		ENLIMIT = 1520, // ��������
		PFLIMIT = 1530, // ��������
		PET_SCALE = 1810, // �����С 1-4
		ACTIVENESS = 1820, // ��Ծ��ֵ
		ANTI_CRIT_LEVEL = 2090, // �������Եȼ�
		KONGZHI_JIACHENG = 2130, // ���Ƽӳ�
		KONGZHI_MIANYI = 2140, // ��������
		ENERGY = 3010, // ��ǰ����
	};

	AttrType() {
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

	bool operator<(const AttrType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const AttrType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
