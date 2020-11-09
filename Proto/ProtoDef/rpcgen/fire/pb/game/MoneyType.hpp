
#pragma once


namespace fire { 
namespace pb { 
namespace game { 

class MoneyType : public FireNet::Marshal
{
public:
	enum {
		MoneyType_None = 0, // ��Ч����
		MoneyType_SilverCoin = 1, // ����
		MoneyType_GoldCoin = 2, // ���
		MoneyType_HearthStone = 3, // ��ʯ
		MoneyType_ProfContribute = 4, // ְҵ����
		MoneyType_RongYu = 5, // ����ֵ
		MoneyType_FactionContribute = 6, // ���ṱ��
		MoneyType_ShengWang = 7, // ����
		MoneyType_FestivalPoint = 8, // ���ջ���
		MoneyType_GoodTeacherVal = 9, // ��ʦֵ
		MoneyType_RoleExp = 10, // ��ɫ����
		MoneyType_Activity = 11, // ��Ծ��
		MoneyType_Energy = 12, // ����
		MoneyType_EreditPoint = 13, // ���õ�
		MoneyType_Item = 99, // ����
		MoneyType_Num = 15, // ��������
	};

	MoneyType() {
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

	bool operator<(const MoneyType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const MoneyType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
