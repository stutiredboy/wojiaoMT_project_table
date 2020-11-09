
#pragma once


namespace fire { 
namespace pb { 
namespace circletask { 

class SpecialQuestType : public FireNet::Marshal
{
public:
	enum {
		Mail = 801001, // ����
		Patrol = 801002, // Ѳ��
		BuyItem = 801003, // �����
		CatchPet = 801004, // ץ�ػ�
		Demonstrate = 801005, // ʾ��
		DemonstrateEye = 801006, // ʾ��
		Rescue = 801007, // Ԯ��
		Tame = 801008, // ����
		CaiJi = 801010, // �ɼ�
		CaiJiFinish = 801030, // �ɼ����
		ChuanDiXiaoXi = 801011, // ������Ϣ
		KillMonster = 801012, // ���
		KillMonsterFinish = 801032, // ������
		FindItem = 801013, // ���Ѱ��
		FindItemFinish = 801033, // ���Ѱ�����
		Answer = 801014, // ����
		AnswerFinish = 801034, // �������
		CatchIt_Normal = 1030001, // ׽��
		CatchIt_Increase = 1030002, // ����
	};

	SpecialQuestType() {
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

	bool operator<(const SpecialQuestType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const SpecialQuestType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
