
#pragma once


namespace fire { 
namespace pb { 
namespace master { 

class DataConfig : public FireNet::Marshal
{
public:
	enum {
		REG_MONEY = 20000, // �Ǽ�ʦ���۳�����Ϸ��
		MONEY1 = 10000, // ͽ��3����7�첻���ߣ������ϵ����۳�ʦ��10000��Ϸ��
		MONEY2 = 100000, // ͽ��3�����ڲ����ߣ������ϵ����۳�ʦ��100000��Ϸ��
		REN_QI = 100, // ͽ��3�����ڲ����ߣ������ϵ����۳�ʦ��100����ֵ
		TAIXUEFUZI_ID = 10215, // ̫ѧ����id
		EVALUATER_LEVEL1 = 120, // ʦ������һ
		EVALUATER_LEVEL2 = 100, // ʦ�������
		EVALUATER_LEVEL3 = 80, // ʦ��������
		EVALUATER_LEVEL4 = 60, // ʦ��������
		EVALUATER_LEVEL5 = 40, // ʦ��������
	};

	DataConfig() {
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

	bool operator<(const DataConfig &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const DataConfig &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
